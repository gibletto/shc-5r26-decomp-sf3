// Apply one stage's naming tables (ghidra/names/<stage>/) to the program: data types, function names and
// signatures, global names and types, local variable names. Replaces the per-stage ApplyXxxNames.java scripts; the
// tables are the version-controlled record, and tools/export-stage-now.sh applies them in every (read-only) export
// session, so the Ghidra project itself is never the only copy of a name.
//
// Usage (headless):
//   analyzeHeadless <proj_dir> <proj_name> -process <bin.exe> -noanalysis [-readOnly] -scriptPath <scripts> \
//     -postScript ApplyStageTables.java <dir>
//
// <dir> holds (each optional; see ghidra/names/README.md):
//   entries.tsv    address <tab> note                             code Ghidra's analysis left without a function (a
//                  dispatch-table target): disassembled and made a function first (an address inside a function
//                  is left alone)
//   enums.tsv      enum <tab> size <tab> member <tab> value       one row per member; created first, with that size
//   types.h        C struct/union definitions, parsed into the program after the enums. "// @size NAME 0xNN"
//                  lines are checked against the parsed sizes (a mismatch fails the script).
//   functions.tsv  address <tab> name <tab> signature <tab> note  signature: a C prototype using the name (empty =
//                  keep Ghidra's); note: free text (not applied)
//   globals.tsv    address <tab> name <tab> type <tab> note       type: a C type (struct names, pointers, [N]
//                  arrays); empty = keep the data type Ghidra has
//   locals.tsv     function <tab> old name <tab> new name <tab> type <tab> pc <tab> storage   a decompiler local
//                  renamed, optionally retyped; pc/storage (tools/key-locals.py fills them from an export) find the
//                  variable when the decompiler has renumbered its temporaries
// Lines starting with # and blank lines are skipped. Any failure is printed as "ApplyStageTables: ERROR ..." and the
// script then throws, so an export never silently runs with half the tables.

import java.io.File;
import java.nio.file.*;
import java.util.*;

import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.app.services.DataTypeManagerService;
import ghidra.app.util.cparser.C.CParser;
import ghidra.app.util.cparser.C.CParserUtils;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.symbol.*;

public class ApplyStageTables extends GhidraScript {

	private int errors = 0;
	private final CategoryPath cat = new CategoryPath("/stage");

	private void error(String msg) {
		println("ApplyStageTables: ERROR " + msg);
		errors++;
	}

	private List<String[]> rows(File f, int min) throws Exception {
		List<String[]> out = new ArrayList<>();
		if (!f.isFile()) return out;
		int n = 0;
		for (String l : Files.readAllLines(f.toPath())) {
			n++;
			if (l.trim().isEmpty() || l.startsWith("#")) continue;
			String[] p = l.split("\t", -1);
			if (p.length < min) {
				error(f.getName() + ":" + n + ": expected " + min + " columns: " + l);
				continue;
			}
			for (int i = 0; i < p.length; i++) p[i] = p[i].trim();
			out.add(p);
		}
		return out;
	}

	private DataTypeManager dtm() {
		return currentProgram.getDataTypeManager();
	}

	/** a C type spelling ("psd *", "int [4]", "unsigned char") -> a data type of this program */
	private DataType resolveType(String spec) throws Exception {
		String s = spec.trim();
		List<Integer> dims = new ArrayList<>();
		while (s.endsWith("]")) {
			int i = s.lastIndexOf('[');
			dims.add(0, Integer.decode(s.substring(i + 1, s.length() - 1).trim()));
			s = s.substring(0, i).trim();
		}
		int stars = 0;
		while (s.endsWith("*")) {
			stars++;
			s = s.substring(0, s.length() - 1).trim();
		}
		DataType base = findType(s);
		if (base == null) throw new Exception("unknown type '" + s + "' in '" + spec + "'");
		DataType t = base;
		for (int i = 0; i < stars; i++) t = new PointerDataType(t, dtm());
		for (int i = dims.size() - 1; i >= 0; i--) t = new ArrayDataType(t, dims.get(i), t.getLength(), dtm());
		return t;
	}

	private DataType findType(String name) {
		String n = name.replaceFirst("^(struct|union|enum)\\s+", "");
		Map<String, String> c = Map.of("unsigned char", "uchar", "unsigned short", "ushort", "unsigned int", "uint",
		                               "signed char", "char", "unsigned long", "ulong");
		n = c.getOrDefault(n, n);
		List<DataType> found = new ArrayList<>();
		dtm().findDataTypes(n, found);
		for (DataType d : found) if (d.getCategoryPath().equals(cat)) return d;
		if (!found.isEmpty()) return found.get(0);
		DataType b = BuiltInDataTypeManager.getDataTypeManager().getDataType(new CategoryPath("/"), n);
		return b == null ? null : dtm().resolve(b, null);
	}

	private void applyEnums(File f) throws Exception {
		Map<String, EnumDataType> enums = new LinkedHashMap<>();
		for (String[] r : rows(f, 4)) {
			EnumDataType e = enums.get(r[0]);
			if (e == null) {
				e = new EnumDataType(cat, r[0], Integer.decode(r[1]), dtm());
				enums.put(r[0], e);
			}
			e.add(r[2], Long.decode(r[3]));
		}
		for (EnumDataType e : enums.values()) dtm().addDataType(e, DataTypeConflictHandler.REPLACE_HANDLER);
		println("ApplyStageTables: " + enums.size() + " enums");
	}

	private void applyTypes(File f) throws Exception {
		if (!f.isFile()) return;
		String text = new String(Files.readAllBytes(f.toPath()));
		CParser p = new CParser(dtm(), true, new DataTypeManager[] { dtm() });
		p.setParseFileName("stage");
		p.parse(text);
		// the parser files types under a category named after the parse file; keep them all in /stage
		int moved = 0;
		Category from = dtm().getCategory(new CategoryPath("/stage"));
		Map<String, Long> want = new LinkedHashMap<>();
		for (String l : text.split("\n")) {
			l = l.trim();
			if (l.startsWith("// @size ")) {
				String[] q = l.substring(9).trim().split("\\s+");
				want.put(q[0], Long.decode(q[1]));
			}
		}
		for (Map.Entry<String, Long> w : want.entrySet()) {
			DataType d = findType(w.getKey());
			if (d == null) error("types.h: @size of unknown type " + w.getKey());
			else if (d.getLength() != w.getValue())
				error("types.h: " + w.getKey() + " is 0x" + Integer.toHexString(d.getLength()) + " bytes, @size says 0x" + Long.toHexString(w.getValue()));
		}
		println("ApplyStageTables: types parsed, " + want.size() + " sizes checked");
	}

	private void applyEntries(File f) throws Exception {
		FunctionManager fm = currentProgram.getFunctionManager();
		int n = 0;
		for (String[] r : rows(f, 1)) {
			Address a = toAddr(r[0]);
			if (fm.getFunctionAt(a) != null) continue;
			if (fm.getFunctionContaining(a) != null) {
				// a label inside a function (a switch case, a shared tail): left as it is
				println("ApplyStageTables: entries.tsv: " + r[0] + " is inside " + fm.getFunctionContaining(a).getName());
				continue;
			}
			disassemble(a);
			Function fn = createFunction(a, null);
			if (fn == null) error("entries.tsv: cannot create a function at " + r[0]);
			else {
				fn.setCallingConvention("__cdecl");   // as the analysis gives the stage's own functions
				n++;
			}
		}
		println("ApplyStageTables: " + n + " functions created");
	}

	private void applyFunctions(File f) throws Exception {
		FunctionManager fm = currentProgram.getFunctionManager();
		int named = 0, sigs = 0;
		List<String[]> withSig = new ArrayList<>();
		for (String[] r : rows(f, 2)) {
			Function fn = fm.getFunctionAt(toAddr(r[0]));
			if (fn == null && r.length > 3 && r[3].contains("CREATE:")) {
				// code the analysis never made a function (reached only through a pointer constant): the row asks
				// for one, disassembled from its entry
				disassemble(toAddr(r[0]));
				fn = createFunction(toAddr(r[0]), r[1]);
			}
			if (fn == null) {
				error("functions.tsv: no function at " + r[0]);
				continue;
			}
			if (!fn.getName().equals(r[1])) {
				// a secondary label of that name already there (Ghidra's function ID leaves "FID_conflict" alternatives
				// as labels): remove it, then rename the function
				Symbol other = currentProgram.getSymbolTable().getSymbol(r[1], fn.getEntryPoint(), null);
				if (other != null) other.delete();
				fn.setName(r[1], SourceType.USER_DEFINED);
			}
			named++;
			if (r.length > 2 && !r[2].isEmpty()) withSig.add(r);
		}
		// signatures after all names, so a prototype may name any type; each is checked to name its own function
		for (String[] r : withSig) {
			Function fn = fm.getFunctionAt(toAddr(r[0]));
			// the parser takes the name to be everything after the last space: "psd *f(" would name "*f"
			String text = r[2].replaceAll("\\*\\s*(\\w+)\\s*\\(", "* $1(");
			FunctionDefinitionDataType sig = CParserUtils.parseSignature((DataTypeManagerService) null, currentProgram, text, false);
			if (sig == null) {
				error("functions.tsv: cannot parse " + r[2]);
				continue;
			}
			if (!sig.getName().equals(r[1])) {
				error("functions.tsv: " + r[0] + " signature names " + sig.getName() + ", not " + r[1]);
				continue;
			}
			sig.setCallingConvention(fn.getCallingConventionName());
			ApplyFunctionSignatureCmd cmd = new ApplyFunctionSignatureCmd(fn.getEntryPoint(), sig, SourceType.USER_DEFINED);
			if (!cmd.applyTo(currentProgram, monitor)) error("functions.tsv: " + r[2] + ": " + cmd.getStatusMsg());
			else sigs++;
		}
		println("ApplyStageTables: " + named + " functions named, " + sigs + " signatures");
	}

	private void applyGlobals(File f) throws Exception {
		SymbolTable st = currentProgram.getSymbolTable();
		Listing listing = currentProgram.getListing();
		int n = 0, typed = 0;
		for (String[] r : rows(f, 2)) {
			Address a = toAddr(r[0]);
			if (r.length > 2 && !r[2].isEmpty()) {
				DataType t;
				try {
					t = resolveType(r[2]);
				}
				catch (Exception e) {
					error("globals.tsv: " + r[0] + ": " + e.getMessage());
					continue;
				}
				Data d = listing.getDataAt(a);
				if (d == null || !d.getDataType().isEquivalent(t)) {
					listing.clearCodeUnits(a, a.add(t.getLength() - 1), false);
					listing.createData(a, t);
				}
				typed++;
			}
			Symbol s = st.getPrimarySymbol(a);
			if (s != null && s.getSource() != SourceType.DEFAULT) {
				if (!s.getName().equals(r[1])) s.setName(r[1], SourceType.USER_DEFINED);
			}
			else {
				createLabel(a, r[1], true, SourceType.USER_DEFINED);
			}
			n++;
		}
		println("ApplyStageTables: " + n + " globals named, " + typed + " typed");
	}

	private HighFunction decompile(DecompInterface iface, Function fn) {
		DecompileResults res = iface.decompileFunction(fn, 120, monitor);
		return res == null ? null : res.getHighFunction();
	}

	private Map<String, HighSymbol> localSymbols(HighFunction hf) {
		Map<String, HighSymbol> m = new HashMap<>();
		Iterator<HighSymbol> it = hf.getLocalSymbolMap().getSymbols();
		while (it.hasNext()) {
			HighSymbol s = it.next();
			m.put(s.getName(), s);
		}
		return m;
	}

	/** a row's variable: by its first-use address (column 5) when the row has one, since the decompiler's temporary
	    names (iVar3) are renumbered by changes elsewhere; several first used there: the one with the row's storage
	    (column 6) or old name; no address: by the old name */
	private HighSymbol find(Map<String, HighSymbol> syms, String[] r) {
		String pc = r.length > 4 ? r[4] : "";
		if (pc.isEmpty()) return syms.get(r[1]);
		List<HighSymbol> at = new ArrayList<>();
		for (HighSymbol s : syms.values()) {
			Address a = s.getPCAddress();
			if (a != null && a.toString().equals(pc)) at.add(s);
		}
		if (at.size() == 1) return at.get(0);
		for (HighSymbol s : at) if (r.length > 5 && s.getStorage().toString().equals(r[5])) return s;
		for (HighSymbol s : at) if (s.getName().equals(r[1])) return s;
		return at.isEmpty() ? syms.get(r[1]) : null;
	}

	private void applyLocals(File f) throws Exception {
		List<String[]> rs = rows(f, 3);
		if (rs.isEmpty()) return;
		DecompInterface iface = new DecompInterface();
		iface.setOptions(new DecompileOptions());
		iface.toggleCCode(true);
		iface.setSimplificationStyle("decompile");
		iface.openProgram(currentProgram);
		FunctionManager fm = currentProgram.getFunctionManager();
		Map<String, List<String[]>> byFn = new LinkedHashMap<>();
		for (String[] r : rs) byFn.computeIfAbsent(r[0], k -> new ArrayList<>()).add(r);
		int n = 0;
		for (Map.Entry<String, List<String[]>> e : byFn.entrySet()) {
			Function fn = fm.getFunctionAt(toAddr(e.getKey()));
			if (fn == null) {
				error("locals.tsv: no function at " + e.getKey());
				continue;
			}
			// every rename of a function from one decompilation: the old names are the export's, and committing one
			// variable renumbers the decompiler's remaining temporaries
			HighFunction hf = decompile(iface, fn);
			if (hf == null) {
				error("locals.tsv: cannot decompile " + e.getKey());
				continue;
			}
			Map<String, HighSymbol> syms = localSymbols(hf);
			for (String[] r : e.getValue()) {
				HighSymbol sym = find(syms, r);
				if (sym == null) {
					error("locals.tsv: " + r[0] + " has no variable " + r[1] +
					      (r.length > 4 && !r[4].isEmpty() ? " (first used at " + r[4] + ")" : ""));
					continue;
				}
				DataType t = null;
				if (r.length > 3 && !r[3].isEmpty()) {
					try {
						t = resolveType(r[3]);
					}
					catch (Exception x) {
						error("locals.tsv: " + r[0] + " " + r[1] + ": " + x.getMessage());
						continue;
					}
				}
				HighFunctionDBUtil.updateDBVariable(sym, r[2], t, SourceType.USER_DEFINED);
				n++;
			}
			// the new names must all be there afterwards
			HighFunction after = decompile(iface, fn);
			Map<String, HighSymbol> now = after == null ? new HashMap<>() : localSymbols(after);
			for (String[] r : e.getValue())
				if (!now.containsKey(r[2])) error("locals.tsv: " + r[0] + " " + r[1] + " -> " + r[2] + " is not in the decompilation afterwards");
		}
		iface.dispose();
		println("ApplyStageTables: " + n + " locals renamed");
	}

	@Override
	protected void run() throws Exception {
		File dir = new File(getScriptArgs()[0]);
		if (!dir.isDirectory()) throw new Exception("no tables directory " + dir);
		applyEntries(new File(dir, "entries.tsv"));
		applyEnums(new File(dir, "enums.tsv"));
		applyTypes(new File(dir, "types.h"));
		applyFunctions(new File(dir, "functions.tsv"));
		applyGlobals(new File(dir, "globals.tsv"));
		applyLocals(new File(dir, "locals.tsv"));
		if (errors > 0) throw new Exception("ApplyStageTables: " + errors + " errors");
		println("ApplyStageTables: done");
	}
}
