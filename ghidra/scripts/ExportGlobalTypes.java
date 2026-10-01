// For every function: decompile it and list each global the decompiler shows, with the data type it used for that
// global in that function (for an untyped global the decompiler infers one from the function's use of it, so the
// same global can be an int in one function and a short * in another).
//
// Usage (headless):
//   analyzeHeadless <proj_dir> <proj_name> -process <bin.exe> -noanalysis -readOnly -scriptPath <scripts> \
//     -postScript ExportGlobalTypes.java <out.tsv>
// Output: function_addr <tab> global_addr <tab> name <tab> type <tab> size

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.address.Address;

public class ExportGlobalTypes extends GhidraScript {
    @Override
    protected void run() throws Exception {
        File out = new File(getScriptArgs()[0]);
        DecompInterface iface = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        iface.setOptions(opts);
        iface.toggleCCode(true);
        iface.setSimplificationStyle("decompile");
        iface.openProgram(currentProgram);
        int n = 0;
        try (Writer w = new OutputStreamWriter(new FileOutputStream(out), StandardCharsets.UTF_8)) {
            w.write("function\tglobal\tname\ttype\tsize\thtype\n");
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                if (monitor.isCancelled()) break;
                DecompileResults r = iface.decompileFunction(f, 120, monitor);
                if (r == null || !r.decompileCompleted()) continue;
                HighFunction hf = r.getHighFunction();
                if (hf == null) continue;
                Iterator<HighSymbol> it = hf.getGlobalSymbolMap().getSymbols();
                while (it.hasNext()) {
                    HighSymbol s = it.next();
                    Address a = null;
                    try {
                        a = s.getStorage().getMinAddress();
                    } catch (Exception e) {
                        continue;
                    }
                    if (a == null || !a.isMemoryAddress()) continue;
                    // htype: the type the decompiler inferred for the global in this function (what the printed C
                    // follows; for an undefinedN global it is not the stored type)
                    String ht = "";
                    HighVariable hv = s.getHighVariable();
                    if (hv != null && hv.getDataType() != null) ht = hv.getDataType().getDisplayName();
                    w.write(f.getEntryPoint() + "\t" + a + "\t" + s.getName() + "\t" + s.getDataType().getDisplayName() +
                            "\t" + s.getSize() + "\t" + ht + "\n");
                }
                n++;
            }
        }
        println("ExportGlobalTypes: " + n + " functions -> " + out);
    }
}
