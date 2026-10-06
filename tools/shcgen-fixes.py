#!/usr/bin/env python3
"""Source fixes to rebuild/shcgen/src that the Ghidra export can't express, applied after regen-shcgen.sh's other
steps (each asserts the text it replaces, so a changed export fails loudly instead of silently skipping).
Functions are named through N(address), from ghidra/names/shcgen/functions.tsv, so a rename there needs no change
here; parameter and local names in the anchors are the tables' (functions.tsv signatures, locals.tsv)."""
import os, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
S = ROOT / "rebuild/shcgen/src"
n = 0
NAMES = {}
for l in open(ROOT / "ghidra/names/shcgen/functions.tsv", encoding="utf-8"):
    r = l.rstrip("\n").split("\t")
    if len(r) > 1 and not l.startswith("#"):
        NAMES[r[0]] = r[1]


def N(addr):
    return NAMES.get(addr, f"FUN_{addr}")


def fix(addr, pairs, regex=False, once=False):
    """as shcpep-fixes.py: literal text where a single space matches any whitespace run (Ghidra re-wraps lines when
    names change), or a regex; every pattern must match"""
    global n
    f = next(S.glob(f"{addr}_*.c"))
    s = f.read_text(encoding="latin-1")
    for old, new in pairs:
        if regex:
            s2, k = re.subn(old, new, s)
        else:
            body = old.strip()
            lead, trail = old[:len(old) - len(old.lstrip())], old[len(old.rstrip()):]
            pat = re.escape(lead) + "".join(r"\s+" if t == " " else re.escape(t).replace(r"\)\)", r"\)\s*\)")
                                            for t in re.split(r"(\s+)", body)) + re.escape(trail)
            s2, k = re.subn(pat, lambda m: new, s)
        if k == 0:
            sys.exit(f"shcgen-fixes: {f.name}: not found: {old!r}")
        if once and k != 1:
            sys.exit(f"shcgen-fixes: {f.name}: {k} matches (want 1): {old!r}")
        s = s2
        n += k
    f.write_text(s, encoding="latin-1")


# select_transfer_template: the jump table at 0042f808 (Ghidra: "Could not recover jumptable", an indirect call)
# written out from the machine code. Entries 1..6 are the forced cases above; entry 0 (code at 0042f690..0042f7d0,
# which Ghidra split into fragments) picks the template by the operands: a push (@-R15) destination, a register
# destination, a register source, else a move; an address source (type 0x40) takes the address forms
fix("0042f500", [(r"\n( *)(\w+) = \(tmpl_header \*\)\(\*\(code \*\)\(&PTR_(?:FUN|LAB)_0042f808\)\[kind\]\)\(\);\n\s*return \2;\n",
                  rf"""
\1switch (kind) {{
\1case 0:
\1  if ((dst->type & 0x1f) == 3 && dst->base == 0x0f) {{
\1    if ((src->type & 0x40) != 0) return {N('0042e760')}(src,extra);
\1    return {N('0042d6a0')}(type,src,reg,node);
\1  }}
\1  if ((dst->type & 0x1f) == 1) {{
\1    if ((src->type & 0x40) != 0) return {N('0042e820')}(src,dst);
\1    return {N('0042ee70')}(src,dst,extra,type);
\1  }}
\1  if ((src->type & 0x1f) == 1) return {N('0042e930')}(src,dst,extra,type);
\1  if ((src->type & 0x40) != 0) return {N('0042e820')}(src,dst);
\1  return {N('0042ddd0')}(type,src,dst,node);
\1case 1: return {N('0042ee70')}(src,dst,extra,type);
\1case 2: return {N('0042e930')}(src,dst,extra,type);
\1case 3: return {N('0042e820')}(src,dst);
\1case 4: return {N('0042e760')}(src,extra);
\1case 5: return {N('0042ddd0')}(type,src,dst,node);
\1default: return {N('0042d6a0')}(type,src,reg,node);
\1}}
""")], regex=True, once=True)

# --- the arcade rules and diagnostics (settings code in src/_regknobs.c; unset = the arcade rule, 0 = Release 26)
KNOBS = "\nint shcgen_knob_tst_r0(void);\nint shcgen_knob_mul_l(void);\nvoid regtrace_site(int site, char *node);\n" \
        "char regtrace_chooser_enter(char ascending, unsigned ret);\n" \
        "void regtrace_chooser_exit(unsigned short p1, unsigned short p2, char p3, short *slots, int chosen);\n" \
        "void regtrace_function(char *rec);\n"
for a in ("004289f0", "00421ea0", "0041fa30", "00415cd0"):
    fix(a, [('#include "imports.h"\n', '#include "imports.h"' + KNOBS)], once=True)

# GEN_TST_R0: the condition value (a node whose value is only tested) takes its register scanning r0..r3 upward
# (the chooser's ascending flag), as the arcade's compiler does; Release 26 scans r3 down
fix("004289f0", [(r"(\n[ \t]*\w+ = " + N("0040d690") + r"\(\w+,[^\n]*\);\n[ \t]*\w+ = \(ushort\)\(\w+ != 0\);\n([ \t]*)(\w+) = '\\0';\n)"
                  r"((?:[ \t]*\w+ = [^\n]*;\n)*?)([ \t]*\w+ = " + N("0041fa30") + r"\()",
                  r"\1\2if (shcgen_knob_tst_r0() != 0) {\n\2  \3 = '\\x01';\n\2}\n\4\2regtrace_site(372,(char *)node);\n\5")],
    regex=True, once=True)

# GEN_MUL_L: a long multiply of a narrow value by a 16-bit constant stays MUL.L (bit 1: the first operand's
# is-a-16-bit-multiplier test answers no, bit 2: the second's)
fix("00421ea0", [(r"(\n[ \t]*(\w+) = )(" + N("00421e00") + r"\((\w+),\2\);)([\s\S]*?)(\n[ \t]*\2 = )(" + N("00421e00")
                  + r"\((\w+),\2\);)",
                  r"\1(shcgen_knob_mul_l() & 1) ? 0 : \3\5\6(shcgen_knob_mul_l() & 2) ? 0 : \7")],
    regex=True, once=True)

# the register chooser: SHCGEN_REGTRACE / GEN_REG_ASC_IDX / GEN_REG_TB_IDX hooks at entry (with the caller's return
# address) and before the return
fix("0041fa30", [(r"(\n\{\n(?:[^\n]*\n)*?)(  \n)",
                  r"\1\2  { unsigned ra_; __asm { mov eax,[ebp+4] } __asm { mov ra_,eax } "
                  r"ascending = regtrace_chooser_enter(ascending,ra_); }\n"),
                 (r"\n([ \t]*)return (\w+)\[0\];",
                  r"\n\1regtrace_chooser_exit(excluded,preferred,ascending,\2,\2[0]);\n\1return \2[0];")],
    regex=True, once=True)

# the per-function loop: SHCGEN_REGTRACE's "FN <name>" line before a function's code is generated
fix("00415cd0", [(r"\n([ \t]*)(" + N("00415ec0") + r"\((\w+)\);)",
                  r"\n\1regtrace_function((char *)\3);\n\1\2")], regex=True, once=True)

# --- GEN_CHAIN_JUMP and GEN_REMAP_LOG (src/_remaprules.c, include/remaprules.h; only with SHC_REBUILD_UPDATED=1): the
# scratch register a switch's compare chain counts as used for its jumps, and the log of what
# remap_register_variables_to_scratch_registers sees
REMAP_INC = ('#include "imports.h"\n', '#include "imports.h"\n#include "remaprules.h"\n')
RANGES_ON = "  if ((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\\0')) {\n"
fix("004208f0", [REMAP_INC, ("used_regs = used_regs | 2;", "used_regs = used_regs | CHAIN_JUMP_REGS(2);")])
fix("0040b0d0", [REMAP_INC, ("  } while (scratch < 4);\n  sVar1 = *lreg;\n",
                             "  } while (scratch < 4);\n  REMAP_LOG();\n  sVar1 = *lreg;\n")])
fix("0041bc70", [REMAP_INC, (RANGES_ON, "  if (contents == g_gpr_contents) {\n"
                                        "    REMAP_MARK(\"st\",used_mask,g_stmt_serial);\n"
                                        "  }\n" + RANGES_ON)])
fix("0041bae0", [REMAP_INC, (RANGES_ON, "  REMAP_MARK(\"rm\",mask,serial);\n" + RANGES_ON)])

# --- GEN_POOL_MOVLOC (src/_poolrules.c, include/poolrules.h): the bytes a frame-slot load or store adds to the
# literal pool window of an unoptimized unit
fix("0042baa0", [('#include "imports.h"\n', '#include "imports.h"\n#include "poolrules.h"\n'),
                 ("  iVar2 = compute_record_code_size(rec);\n  code_bytes =",
                  "  iVar2 = POOL_RECORD_SIZE(rec,compute_record_code_size(rec));\n  code_bytes =")], once=True)

print(f"shcgen-fixes: {n} replacements")
