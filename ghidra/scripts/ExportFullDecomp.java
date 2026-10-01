// Full-decomp exporter: iterate every defined function, decompile via
// DecompInterface, emit one .c per function plus a per-program index, plus
// data-type and symbol dumps sufficient to rebuild headers.
//
// Usage (headless):
//   analyzeHeadless <proj_dir> <proj_name> -process <bin.exe> \
//     -noanalysis -scriptPath <scripts> \
//     -postScript ExportFullDecomp.java <out_dir>
//
// Output layout under <out_dir>:
//   decomp/<entry>_<name>.c       per-function decomp + disassembly tail
//   functions.tsv                 entry\tname\tsize\tstatus
//   globals.tsv                   addr\ttype\tname
//   datatypes.txt                 all structs/unions/typedefs (textual)
//   symbols.tsv                   every symbol ghidra knows about
//   externals.tsv                 imports (libname / thunk addr / name)
//   variables.tsv                 entry\tname\tkind\toffset\tsize\ttype\tpc\tstorage: every decompiler local and
//                                 parameter (kind stack: offset = its stack offset, as Ghidra's local_N/param_N names
//                                 count; pc: the first code address using it, which keys locals.tsv rows)

import java.io.File;
import java.io.OutputStreamWriter;
import java.io.FileOutputStream;
import java.io.Writer;
import java.nio.charset.StandardCharsets;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.Composite;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeManager;
import ghidra.program.model.data.TypeDef;
import ghidra.program.model.data.Category;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.ExternalLocation;
import ghidra.program.model.symbol.ExternalLocationIterator;
import ghidra.program.model.symbol.ExternalManager;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolTable;

public class ExportFullDecomp extends GhidraScript {

	private void ensureDir(File dir) throws Exception {
		if (!dir.isDirectory() && !dir.mkdirs()) {
			throw new Exception("Failed to create directory: " + dir.getAbsolutePath());
		}
	}

	private void writeText(File path, String text) throws Exception {
		File parent = path.getParentFile();
		if (parent != null) ensureDir(parent);
		Writer writer = new OutputStreamWriter(new FileOutputStream(path), StandardCharsets.UTF_8);
		try { writer.write(text); } finally { writer.close(); }
	}

	private String sanitize(String name) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < name.length(); i++) {
			char ch = name.charAt(i);
			if (Character.isLetterOrDigit(ch) || ch == '_' || ch == '.' || ch == '-') sb.append(ch);
			else sb.append('_');
		}
		String out = sb.toString();
		if (out.length() > 120) out = out.substring(0, 120);
		return out;
	}

	private void dumpFunctions(File outDir) throws Exception {
		File decompDir = new File(outDir, "decomp");
		ensureDir(decompDir);

		DecompInterface iface = new DecompInterface();
		DecompileOptions opts = new DecompileOptions();
		iface.setOptions(opts);
		iface.toggleCCode(true);
		iface.toggleSyntaxTree(false);
		iface.setSimplificationStyle("decompile");
		iface.openProgram(currentProgram);

		Listing listing = currentProgram.getListing();
		StringBuilder index = new StringBuilder();
		index.append("entry\tname\tsize\tstatus\n");
		StringBuilder vars = new StringBuilder();
		vars.append("entry\tname\tkind\toffset\tsize\ttype\tpc\tstorage\n");

		int total = 0, ok = 0, fail = 0;
		FunctionIterator funcs = currentProgram.getFunctionManager().getFunctions(true);
		while (funcs.hasNext()) {
			Function func = funcs.next();
			total++;
			Address entry = func.getEntryPoint();
			String name = func.getName();
			long size = func.getBody().getNumAddresses();

			File out = new File(decompDir, entry.toString() + "_" + sanitize(name) + ".c");

			DecompileResults result = null;
			String status = "ok";
			try {
				result = iface.decompileFunction(func, 300, monitor);
			}
			catch (Exception e) {
				status = "exception:" + e.getMessage();
			}

			StringBuilder sb = new StringBuilder();
			sb.append("// entry: ").append(entry).append('\n');
			sb.append("// name : ").append(name).append('\n');
			sb.append("// size : ").append(size).append('\n');
			sb.append("// sig  : ").append(func.getSignature().getPrototypeString()).append("\n\n");

			if (result != null && result.decompileCompleted() && result.getDecompiledFunction() != null) {
				sb.append(result.getDecompiledFunction().getC()).append('\n');
				ok++;
				if (result.getHighFunction() != null) {
					java.util.Iterator<ghidra.program.model.pcode.HighSymbol> hs =
						result.getHighFunction().getLocalSymbolMap().getSymbols();
					while (hs.hasNext()) {
						ghidra.program.model.pcode.HighSymbol h = hs.next();
						ghidra.program.model.listing.VariableStorage st = h.getStorage();
						String kind = st.isStackStorage() ? "stack" : st.isRegisterStorage() ? "register" : "other";
						String off = st.isStackStorage() ? Integer.toString(st.getStackOffset()) : "";
						Address pc = h.getPCAddress();
						vars.append(entry).append('\t').append(h.getName()).append('\t').append(kind).append('\t')
						    .append(off).append('\t').append(h.getSize()).append('\t')
						    .append(h.getDataType() == null ? "" : h.getDataType().getDisplayName()).append('\t')
						    .append(pc == null ? "" : pc.toString()).append('\t').append(st.toString()).append('\n');
					}
				}
			}
			else {
				status = "decomp_fail";
				if (result != null) sb.append("// error: ").append(result.getErrorMessage()).append('\n');
				sb.append("// (decompilation failed)\n");
				fail++;
			}

			sb.append("\n// --- disassembly ---\n");
			InstructionIterator it = listing.getInstructions(func.getBody(), true);
			while (it.hasNext()) {
				Instruction inst = it.next();
				sb.append(inst.getAddress()).append('\t').append(inst).append('\n');
			}

			writeText(out, sb.toString());
			index.append(entry).append('\t')
			     .append(name).append('\t')
			     .append(size).append('\t')
			     .append(status).append('\n');

			if (total % 25 == 0) {
				println("  decomped " + total + " functions (" + ok + " ok, " + fail + " fail)");
			}
			if (monitor.isCancelled()) break;
		}

		writeText(new File(outDir, "functions.tsv"), index.toString());
		writeText(new File(outDir, "variables.tsv"), vars.toString());
		iface.dispose();
		println("Total functions: " + total + " (" + ok + " ok, " + fail + " fail)");
	}

	private void dumpGlobals(File outDir) throws Exception {
		StringBuilder sb = new StringBuilder();
		sb.append("addr\ttype\tname\tlen\n");
		DataIterator data = currentProgram.getListing().getDefinedData(true);
		int n = 0;
		while (data.hasNext()) {
			Data d = data.next();
			DataType dt = d.getDataType();
			String typeName = (dt == null) ? "?" : dt.getDisplayName();
			String label = d.getLabel();
			if (label == null) label = "";
			sb.append(d.getAddress()).append('\t')
			  .append(typeName.replace('\t',' ')).append('\t')
			  .append(label).append('\t')
			  .append(d.getLength()).append('\n');
			n++;
			if (n % 2000 == 0 && monitor.isCancelled()) break;
		}
		writeText(new File(outDir, "globals.tsv"), sb.toString());
		println("Globals dumped: " + n);
	}

	private void dumpSymbols(File outDir) throws Exception {
		StringBuilder sb = new StringBuilder();
		sb.append("addr\tname\ttype\tnamespace\n");
		SymbolTable table = currentProgram.getSymbolTable();
		SymbolIterator it = table.getAllSymbols(true);
		int n = 0;
		while (it.hasNext()) {
			Symbol s = it.next();
			sb.append(s.getAddress()).append('\t')
			  .append(s.getName()).append('\t')
			  .append(s.getSymbolType().toString()).append('\t')
			  .append(s.getParentNamespace().getName()).append('\n');
			n++;
		}
		writeText(new File(outDir, "symbols.tsv"), sb.toString());
		println("Symbols dumped: " + n);
	}

	private void dumpExternals(File outDir) throws Exception {
		StringBuilder sb = new StringBuilder();
		sb.append("lib\taddr\tname\tmem_addr\n");
		ExternalManager em = currentProgram.getExternalManager();
		String[] libs = em.getExternalLibraryNames();
		for (String lib : libs) {
			ExternalLocationIterator it = em.getExternalLocations(lib);
			while (it.hasNext()) {
				ExternalLocation loc = it.next();
				Address maddr = loc.getAddress();
				sb.append(lib).append('\t')
				  .append(maddr == null ? "" : maddr.toString()).append('\t')
				  .append(loc.getLabel()).append('\t')
				  .append(loc.getSymbol() != null ? loc.getSymbol().getAddress() : "").append('\n');
			}
		}
		writeText(new File(outDir, "externals.tsv"), sb.toString());
	}

	private void dumpDataTypes(File outDir) throws Exception {
		StringBuilder sb = new StringBuilder();
		DataTypeManager dtm = currentProgram.getDataTypeManager();
		java.util.Iterator<Composite> comps = dtm.getAllComposites();
		while (comps.hasNext()) {
			Composite c = comps.next();
			sb.append("// composite: ").append(c.getPathName()).append('\n');
			sb.append(c.toString()).append("\n\n");
		}
		java.util.Iterator<DataType> allDt = dtm.getAllDataTypes();
		while (allDt.hasNext()) {
			DataType dt = allDt.next();
			if (dt instanceof TypeDef) {
				TypeDef td = (TypeDef) dt;
				sb.append("typedef ").append(td.getDataType().getName()).append(' ').append(td.getName()).append(";\n");
			}
		}
		writeText(new File(outDir, "datatypes.txt"), sb.toString());
	}

	@Override
	protected void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length < 1) {
			throw new IllegalArgumentException("Usage: ExportFullDecomp.java <out_dir>");
		}
		File outDir = new File(args[0]);
		ensureDir(outDir);

		println("=== ExportFullDecomp :: " + currentProgram.getName() + " -> " + outDir + " ===");
		dumpSymbols(outDir);
		dumpGlobals(outDir);
		dumpExternals(outDir);
		dumpDataTypes(outDir);
		dumpFunctions(outDir);
		println("=== done ===");
	}
}
