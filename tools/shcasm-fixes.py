#!/usr/bin/env python3
"""Source fixes to rebuild/shcasm/src that the Ghidra export can't express, applied after regen-shcasm.sh's other
steps (each asserts the text it replaces, so a changed export fails loudly instead of silently skipping)."""
import re, sys
from pathlib import Path

S = Path(__file__).resolve().parent.parent / "rebuild/shcasm/src"
n = 0


def fix(addr, pairs, regex=False):
    global n
    f = next(S.glob(f"{addr}_*.c"))
    s = f.read_text(encoding="latin-1")
    for old, new in pairs:
        if regex:
            s2, k = re.subn(old, new, s)
        else:
            # literal text, but a single space inside it matches any whitespace (Ghidra re-wraps long lines at a
            # space, or between two closing parentheses, when names change); newlines, indentation and the ends
            # stay exact (as tools/shcpep-fixes.py)
            body = old.strip()
            lead, trail = old[:len(old) - len(old.lstrip())], old[len(old.rstrip()):]
            pat = re.escape(lead) + "".join(r"\s+" if t == " " else re.escape(t).replace(r"\)\)", r"\)\s*\)")
                                            for t in re.split(r"(\s+)", body)) + re.escape(trail)
            s2, k = re.subn(pat, lambda m: new, s)
        if k == 0:
            sys.exit(f"shcasm-fixes: {f.name}: not found: {old!r}")
        s = s2
        n += k
    f.write_text(s, encoding="latin-1")


# exit: the stock pre-terminators (stock_flsall) flush the stock CRT's stream table, but every file shcasm opens is
# a host CRT FILE of src/_crt_shim.c; flush those at the same point, or a run that ends through exit() without closing
# its files (handle_fault_signal: the SH-4 scheduler's faults) loses their buffered tail
fix("00435320", [("    stock_initterm((undefined4 *)&stock_xp_a,(undefined4 *)&stock_xp_z);\n",
                  "    stock_initterm((undefined4 *)&stock_xp_a,(undefined4 *)&stock_xp_z);\n"
                  "    _flushall();\n")])

# --- the rule (SHC_REBUILD_UPDATED only; otherwise Release 26)
# ASM_SPECREG (unset or 1 = the fix, 0 = Release 26): the list scheduler loses every dependency through a special
# register. Release 26 inserted the SH-4 XF/XD registers at 0x40..0x5f, moving SR, GBR, VBR, MACH, MACL, PR, ...
# TBIT from 0x41.. to 0x61.., but accumulate_operand_register_mask still looks an operand register's high-word mask
# up as 0x43ccfc + reg*4, a table built for the specials at 0x41..0x60; for 0x61+ it reads unrelated globals, so
# build_pipeline_dependency_graph finds no common bit and STS MACL can be scheduled above the MUL feeding it.
# The fix maps 0x61..0x7f down by 0x20 before the lookup (the operand's own register; the index register of an
# @(r0,Rn) operand is looked up as before).
SPECREG_HEAD = r'''
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
static int asm_specreg(void) {
    static int v = -1;
    if (v < 0) { char *p = getenv("ASM_SPECREG"); v = (p && *p) ? atoi(p) : 1; }   /* unset = the fix (1); 0 = Release 26 */
    return v;
}
static unsigned int specreg_index(unsigned int reg) {
    return (asm_specreg() && reg >= 0x61 && reg <= 0x7f) ? reg - 0x20 : reg;
}
#endif
'''
fix("004156e9", [('#include "imports.h"\n', '#include "imports.h"\n' + SPECREG_HEAD),
                 ("      mask[1] = mask[1] | (uint)(&PTR_s__sta_sftrl12_0043ccfc)[operand->base];\n",
                  "#if SHC_REBUILD_UPDATED\n"
                  "      mask[1] = mask[1] | (uint)(&PTR_s__sta_sftrl12_0043ccfc)[specreg_index(operand->base)];\n"
                  "#else\n"
                  "      mask[1] = mask[1] | (uint)(&PTR_s__sta_sftrl12_0043ccfc)[operand->base];\n"
                  "#endif\n")])

# SHC_ALIGN_FILE (a diagnostic, unset = no change): move named functions' entry labels as if earlier code were
# longer, to tell alignment knock-on from content. The first layout pass (run_layout_passes) is where shcpep's
# estimated positions become final; the bytes are taken off its running shrink just before the label is corrected.
ALIGN_HEAD = r'''
#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* SHC_ALIGN_FILE (unset = Release 26 layout): a text file of "<function> <bytes>" lines. The named
   function's entry label is moved <bytes> (even, 2..30) further on, as if the code before it were that much longer:
   the first layout pass takes the bytes off its running shrink (g_layout_shrink_pass0) just before the label's position is
   corrected, so the label, everything after it in the section and the section size move together, the second pass
   aligns pools at the moved positions, the scheduler seeds its phase from the moved label, and the emitter fills
   the gap before the label with nops (the fill path emit_label_record already takes when a label lies past the location
   counter; the listing shows it as .ALIGN). */
static struct align_pad { char name[128]; int bytes; } *align_pads;
static int align_npads = -1;
static int align_pad_for(const char *name) {
    int i;
    if (align_npads < 0) {
        char *p = getenv("SHC_ALIGN_FILE"), line[256];
        FILE *fp;
        align_npads = 0;
        if (p && *p && (fp = fopen(p, "r")) != 0) {
            int cap = 0;
            while (fgets(line, sizeof line, fp)) {
                char nm[128]; int b;
                if (line[0] == '#' || sscanf(line, "%127s %i", nm, &b) != 2 || b <= 0 || b > 30 || (b & 1)) continue;
                if (align_npads == cap) {
                    cap = cap ? cap * 2 : 64;
                    align_pads = (struct align_pad *)realloc(align_pads, cap * sizeof *align_pads);
                }
                strcpy(align_pads[align_npads].name, nm);
                align_pads[align_npads++].bytes = b;
            }
            fclose(fp);
        }
    }
    if (!name) return 0;
    if (*name == '_') name++;
    for (i = 0; i < align_npads; i++)
        if (strcmp(align_pads[i].name, name) == 0 || (align_pads[i].name[0] == '_' && strcmp(align_pads[i].name + 1, name) == 0))
            return align_pads[i].bytes;
    return 0;
}
#define ALIGN_PAD(sym) ((((sym)->kind & 0x1f) == 1) ? align_pad_for((sym)->name) : 0)
#else
#define ALIGN_PAD(sym) 0
#endif
'''
fix("00429060", [('#include "imports.h"\n', '#include "imports.h"\n' + ALIGN_HEAD),
                 ("        g_layout_symbol_pass0->value = g_layout_symbol_pass0->value - g_layout_shrink_pass0;\n",
                  "        g_layout_shrink_pass0 = g_layout_shrink_pass0 - ALIGN_PAD(g_layout_symbol_pass0);\n"
                  "        g_layout_symbol_pass0->value = g_layout_symbol_pass0->value - g_layout_shrink_pass0;\n")])

# --- ASM_MULWAIT (src/_mulrules.c, include/mulrules.h; only with SHC_REBUILD_UPDATED=1): how long the multiplier
# holds back STS/LDS MACH/MACL, and which entry the scheduler issues when every ready one is held back
fix("00416754", [('#include "imports.h"\n', '#include "imports.h"\n#include "mulrules.h"\n'),
                 ("    g_pipeline_mac_busy = '\\x02';\n", "    g_pipeline_mac_busy = (char)MUL_BUSY_COUNT;\n")])
fix("00415edd", [('#include "imports.h"\n', '#include "imports.h"\n#include "mulrules.h"\n'),
                 ("  if (g_pipeline_last_scheduled == -1) {\n",
                  "  if (g_pipeline_last_scheduled == -1 && MUL_FORCE_PICK(last_index)) {\n"
                  "    return;\n"
                  "  }\n"
                  "  if (g_pipeline_last_scheduled == -1) {\n")])

print(f"shcasm-fixes: {n} replacements")
