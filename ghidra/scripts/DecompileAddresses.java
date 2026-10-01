// Create functions at a list of addresses (where no function covers them yet) and decompile each.
//
// Usage (headless):
//   analyzeHeadless <proj_dir> <proj_name> -process <bin.exe> -noanalysis -scriptPath <scripts> \
//     -postScript DecompileAddresses.java <address list file> <out dir>
//
// The list has one hex address per line. For each: an address already inside another function is a label of
// that function (a switch case, a shared tail) and is reported as "inside <function>" without creating anything;
// otherwise the code is disassembled, a function created, and <out dir>/<addr>_FUN_<addr>.c written in the
// ExportFullDecomp format (// entry / name / size / sig header, then the C). A summary goes to <out dir>/_summary.tsv.
// A third argument "ret4" first locks each function's return type to undefined4 (for functions Ghidra left with an
// unlocked 'undefined' return whose callers use EAX; run with -readOnly so the project is not changed).

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;

import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.Undefined4DataType;
import ghidra.program.model.symbol.SourceType;

public class DecompileAddresses extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        List<String> lines = Files.readAllLines(Paths.get(args[0]));
        File out = new File(args[1]);
        out.mkdirs();
        FunctionManager fm = currentProgram.getFunctionManager();
        DecompInterface iface = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        iface.setOptions(opts);
        iface.toggleCCode(true);
        iface.setSimplificationStyle("decompile");
        iface.openProgram(currentProgram);
        StringBuilder summary = new StringBuilder("addr\tstatus\tdetail\n");
        // create every function first, so decompiling one sees the others as calls, not fall-through code
        List<Function> made = new ArrayList<>();
        for (String l : lines) {
            l = l.trim();
            if (l.isEmpty()) continue;
            Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(l);
            Function f = fm.getFunctionAt(a);
            if (f == null) {
                Function c = fm.getFunctionContaining(a);
                if (c != null) {
                    summary.append(l).append("\tinside\t").append(c.getName()).append("+")
                           .append(Long.toHexString(a.subtract(c.getEntryPoint()))).append("\n");
                    continue;
                }
                new DisassembleCommand(a, null, true).applyTo(currentProgram, monitor);
                try {
                    f = createFunction(a, "FUN_" + l.toLowerCase());
                } catch (Exception e) {
                    f = null;
                }
            }
            if (f == null) {
                summary.append(l).append("\tfailed\tno function\n");
                continue;
            }
            made.add(f);
        }
        boolean ret4 = args.length > 2 && args[2].equals("ret4");
        for (Function f : made) {
            // only an unlocked 'undefined' return: a return type the naming tables set is kept
            if (ret4 && f.getReturnType().getName().equals("undefined"))
                f.setReturnType(Undefined4DataType.dataType, SourceType.USER_DEFINED);
            String hex = f.getEntryPoint().toString();
            DecompileResults r = iface.decompileFunction(f, 300, monitor);
            if (r == null || !r.decompileCompleted()) {
                summary.append(hex).append("\tfailed\tdecompile\n");
                continue;
            }
            String c = r.getDecompiledFunction().getC();
            String sig = r.getDecompiledFunction().getSignature();
            String text = "// entry: " + hex + "\n// name : " + f.getName() + "\n// size : " +
                          f.getBody().getNumAddresses() + "\n// sig  : " + sig.replace(";", "") + "\n\n" + c;
            File o = new File(out, hex + "_" + f.getName() + ".c");
            try (Writer w = new OutputStreamWriter(new FileOutputStream(o), StandardCharsets.UTF_8)) {
                w.write(text);
            }
            summary.append(hex).append("\tok\t").append(f.getName()).append(" ").append(f.getBody().getNumAddresses()).append("\n");
        }
        try (Writer w = new OutputStreamWriter(new FileOutputStream(new File(out, "_summary.tsv")), StandardCharsets.UTF_8)) {
            w.write(summary.toString());
        }
        println("DecompileAddresses: " + made.size() + " functions written to " + out);
    }
}
