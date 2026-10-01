#!/usr/bin/env python3
"""Source fixes to rebuild/shcmdl/src that the Ghidra export can't express, applied after regen-shcmdl.sh's other
steps (each asserts the text it replaces, so a changed export fails loudly instead of silently skipping).

Anchors use the names of ghidra/names/shcmdl; where a fix needs a decompiler temporary, it is found by a pattern
(the temporaries are renumbered when types change)."""
import re, sys
from pathlib import Path

S = Path(__file__).resolve().parent.parent / "rebuild/shcmdl/src"
n = 0


def fix(addr, pairs, regex=False):
    global n
    f = next(S.glob(f"{addr}_*.c"))
    s = f.read_text(encoding="latin-1")
    for old, new in pairs:
        if regex:
            s2, k = re.subn(old, new, s, flags=re.S)
        else:
            # literal text, but a single space inside it matches any whitespace (Ghidra re-wraps long lines at a
            # space when names change); newlines, indentation and the ends stay exact
            body = old.strip()
            lead, trail = old[:len(old) - len(old.lstrip())], old[len(old.rstrip()):]
            pat = re.escape(lead) + "".join(r"\s+" if t == " " else re.escape(t)
                                            for t in re.split(r"(\s+)", body)) + re.escape(trail)
            s2, k = re.subn(pat, lambda m: new, s)
        if k == 0:
            sys.exit(f"shcmdl-fixes: {f.name}: not found: {old!r}")
        s = s2
        n += k
    f.write_text(s, encoding="latin-1")


INCLUDES = '#include "imports.h"'

# the error-recovery jmp_buf (g_error_jmp_buf): the host CRT's setjmp/longjmp (same jmp_buf layout as the stock CRT)
fix("004010f0", [(INCLUDES, INCLUDES + "\n#include <setjmp.h>"),
                 ("__setjmp3((undefined4 *)&g_error_jmp_buf,0,unaff_EDI,unaff_ESI)", "setjmp(*(jmp_buf *)&g_error_jmp_buf)")])
fix("004015e0", [(INCLUDES, INCLUDES + "\n#include <setjmp.h>"),
                 ("_longjmp((int *)&g_error_jmp_buf,1)", "longjmp(*(jmp_buf *)&g_error_jmp_buf,1)")])
# the pool growth factor: stock converts count * 1.5 (the double at 00432000) with _ftol; Ghidra lost the x87 operand
fix("00404f60", [(r"(\w+) = __ftol\(\);", r"\1 = (longlong)(int)((double)count * *(double *)SD(0x00432000));")],
    regex=True)
# the constant folder's binary operators take (a, b, result): stock pushes the result pointer (EBX) once before the
# branch between the unary and binary call, and Ghidra left it out of the binary one
fix("004065d0", [(r"(\(&(\w+)->val,(\w+)\)\s*;.*?\(&\2->val,&\2->next->val)\)", r"\1,\3)")], regex=True)
# the .reg writer counts the ranges in its address-taken slot (MOV word [esp+2],0; INC word [esp+0x12]) and writes
# the slot; Ghidra dropped both stores (tools/dropped-stores.py)
fix("00414030", [(r"\n  (\w+) = 0;\n", r"\n  \1 = 0;  local_2 = 0;\n"),
                 (r"\n    (\w+) = \(uint\)\(ushort\)\(local_2 \+ 1\);",
                  r"\n    local_2 = local_2 + 1;  \1 = (uint)(ushort)local_2;")], regex=True)
# the folder's 16-bit range case sign-extends the word (MOVSX EAX, word [004587bc]); Ghidra printed it as (int)
fix("00411630", [("_g_loop_limit = (int)_g_loop_limit;", "_g_loop_limit = (int)*(short *)&_g_loop_limit;")])

# --- MDL_ARG_CONST (src/_argconst.c, only with /DSHC_REBUILD_UPDATED=1; the stock build is unchanged): the callers
# of is_immediate_operand the knob's groups route, with the occurrence record ({next, block, node}) whose node the
# constant is (its block marks a loop): the variable the node was taken from
def argconst(addr, group, with_occ=True):
    f = next(S.glob(f"{addr}_*.c"))
    t = f.read_text(encoding="latin-1")
    # the parent operand: node->parent, or *(char **)(node + 0x10) while the callee has no signature
    m = list(re.finditer(r"\bis_immediate_operand\((?:(\w+)->parent|\*\(\w+ \*\*\)\((\w+) \+ 0x10\)),", t))
    if len(m) != 1:
        sys.exit(f"shcmdl-fixes: {f.name}: {len(m)} is_immediate_operand calls")
    node = m[0].group(1) or m[0].group(2)
    occ = "0"
    if with_occ:
        o = list(re.finditer(r"\b%s = (?:\([\w ]+\*\))?(\w+)(?:\[2\]|->node);" % node, t[:m[0].start()]))
        if not o:
            sys.exit(f"shcmdl-fixes: {f.name}: no occurrence record for {node}")
        occ = o[-1].group(1)
    fix(addr, [(INCLUDES, INCLUDES + '\n#include "argconst.h"')])
    fix(addr, [(r"\bis_immediate_operand\(((?:%s->parent|\*\(\w+ \*\*\)\(%s \+ 0x10\)),[^;]*?)\)" % (node, node),
                 r"ARGCONST_FIT(%d,\1,%s)" % (group, occ))],
        regex=True)


argconst("00407b30", 1)          # weigh_common_expression_candidates
argconst("0041b9b0", 2)          # materialize_constant_lreg
argconst("0041c190", 2)          # write_lreg_numbers
argconst("00407720", 4, False)   # collect_register_candidate

print(n, "fixes")
