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


# MDL_MUL_CONST (the same file and the same four hooks): mdl_argconst_fit answers for a multiply's constant itself,
# so the rule needs no hook of its own; MDL_IMM_REG likewise for a zero that is added or subtracted
# and for the constant of a bit-and
argconst("00407b30", 1)          # weigh_common_expression_candidates
argconst("0041b9b0", 2)          # materialize_constant_lreg
argconst("0041c190", 2)          # write_lreg_numbers
argconst("00407720", 4, False)   # collect_register_candidate

# --- MDL_CAST_CSE and MDL_ARG_CAST (src/_castrules.c, include/argconst.h; only with SHC_REBUILD_UPDATED=1)
# MDL_CAST_CSE: the rank of a cast's operand in the two common-expression rewriters, and no register-variable
# candidate for an array name under an integer cast
for a in ("00404010", "00423090"):           # cse_replace_with_temporary, common_expression_to_temp
    fix(a, [(INCLUDES, INCLUDES + '\n#include "argconst.h"'),
            ("child_rank = node_type_rank(node->child);", "child_rank = CAST_OPERAND_RANK(node->child);")])
fix("00407d70", [(INCLUDES, INCLUDES + '\n#include "argconst.h"'),     # hash_common_expression_candidate
                 ("\n  if (((node->op & IL_NON_F0) == IL_A_ADD) ||",
                  "\n  if (CAST_ADDRESS_LEAF(node)) {\n    return;\n  }\n  if (((node->op & IL_NON_F0) == IL_A_ADD) ||")])
# MDL_ARG_CAST: lreg_conflicts_with_call takes the variable an argument passes (ARG_AS_VARIABLE) and the argument
# register of the argument node itself
fix("0041a2a0", [(INCLUDES, INCLUDES + '\n#include "argconst.h"'),
                 ("\n  il_node *arg;\n", "\n  il_node *arg;\n  il_node *arg_node;\n"),
                 ("        while (op != IL_E_ARG) {\n",
                  "        while (op != IL_E_ARG) {\n          arg_node = arg;\n          arg = ARG_AS_VARIABLE(arg);\n"),
                 ("argument_register_index(arg)", "argument_register_index(arg_node)"),
                 ("          arg = arg->next;\n", "          arg = arg_node->next;\n")])

# --- MDL_IV (src/_ivrules.c, include/argconst.h; only with SHC_REBUILD_UPDATED=1): scan_derived_induction_expr keeps the
# induction variable's number across a narrowing cast
fix("00417b60", [(INCLUDES, INCLUDES + '\n#include "argconst.h"'),
                 ("    if (child_rank != rank) {\nLAB_00417c21:",
                  "    if (child_rank > rank && (IV_RULES() & 1) && ((IV_RULES() & 6) == 0 || (IV_RULES() & (rank == 1 ? 2 : 4)))) {\n"
                  "      node->ivno = node->child->ivno;\n      return;\n    }\n    if (child_rank != rank) {\nLAB_00417c21:")])

# --- MDL_IV_BASE (src/_ivrules.c, include/argconst.h; only with SHC_REBUILD_UPDATED=1): the two places where
# hoist_invariants_in_tree asks which run it is in before it calls a member reached through a pointer invariant
fix("004110c0", [(INCLUDES, INCLUDES + '\n#include "argconst.h"'),
                 ("((g_licm_pass != 0 || ((ty != 0x60 && (ty != 0x70))))))",
                  "((IV_LICM_PASS(2) != 0 || ((ty != 0x60 && (ty != 0x70))))))"),
                 ("    if ((g_licm_pass != 0) ||\n", "    if ((IV_LICM_PASS(1) != 0) ||\n")])

# --- MDL_IV_TEMP (src/_ivrules.c, include/argconst.h; only with SHC_REBUILD_UPDATED=1): where
# reduce_induction_variable takes the next expression to reduce, and where it finds the expression already assigned
# to a temporary and steps that temporary
fix("00418040", [(INCLUDES, INCLUDES + '\n#include "argconst.h"'),
                 ("    node = use->expr;\n",
                  "    node = use->expr;\n    if (IV_SKIP_USE(node)) {\n      use = use->next;\n      continue;\n    }\n"),
                 ("    if ((((*parent_link)->op == IL_ASSIGN) && (piVar3 = (*parent_link)->child, piVar3->op == IL_ID))\n"
                  "       && (piVar3->symx < 0)) {",
                  "    if (((((*parent_link)->op == IL_ASSIGN) && (piVar3 = (*parent_link)->child, piVar3->op == IL_ID))\n"
                  "       && (piVar3->symx < 0)) && IV_REUSE_TEMP(*parent_link)) {")])

# --- MDL_LOOP_INV (src/_looprules.c, include/argconst.h; only with SHC_REBUILD_UPDATED=1): the five places where
# select_loops_to_invert asks for -speed before it makes a loop a guarded do-loop
fix("0040b5a0", [(INCLUDES, INCLUDES + '\n#include "argconst.h"'),
                 ("(select_loops_to_invert(lp->child), g_options->unknown_20 != 0)) &&",
                  "(select_loops_to_invert(lp->child), LOOP_SPEED(1))) &&"),
                 ("          if (g_options->unknown_20 != 0) {\n            invert_loop_to_guarded_do(lp);\n          }\n",
                  "          if (LOOP_SPEED(2)) {\n            invert_loop_to_guarded_do(lp);\n          }\n"),
                 ("((expr->type & 0xf8) == 0x30)) {\n            if (g_options->unknown_20 != 0) {",
                  "((expr->type & 0xf8) == 0x30)) {\n            if (LOOP_SPEED(4)) {"),
                 ("              return;\n            }\n            if (g_options->unknown_20 != 0) {",
                  "              return;\n            }\n            if (LOOP_SPEED(8)) {"),
                 ("          else if (g_options->unknown_20 != 0) {", "          else if (LOOP_SPEED(16)) {"),
                 # MDL_LOOP_LOG: the loop, and whether it was inverted
                 ("      select_loops_to_invert(lp->next);\n    }\n", "      select_loops_to_invert(lp->next);\n    }\n    LOOP_LOG(lp);\n"),
                 ("invert_loop_to_guarded_do(lp);", "LOOP_INVERT(lp);")])

# --- MDL_GCSE (src/_gcserules.c, include/gcserules.h; only with SHC_REBUILD_UPDATED=1): where global common-expression
# elimination may put a class's temporary (cse_eliminate_node), and what becomes of a class whose first member
# cse_find_common_block drops (Release 26 reinserts the rest as a new class)
fix("0041dcc0", [(INCLUDES, INCLUDES + '\n#include "gcserules.h"'),
                 ("blk = cse_find_common_block(node,memory_kind), blk != (bblock *)0x0)",
                  "blk = cse_find_common_block(node,memory_kind), blk != (bblock *)0x0) && GCSE_BLOCK_OK(node,blk)")])
fix("0041dcc0", [(r"(blk = cse_find_common_block\(node,\(uint\)\(\(node->flag2 & 8\) != 0\)\), blk != \(bblock \*\)0x0\))",
                  r"\1 && GCSE_BLOCK_OK(node,blk)")], regex=True)
fix("0041de40", [(INCLUDES, INCLUDES + '\n#include "gcserules.h"')])
fix("0041de40", [(r"(= cse_drop_class_head\(node\);\s*)cse_reinsert_class\((\w+)\);", r"\1GCSE_REINSERT(\2,node);")],
    regex=True)
# ... and of the members it takes out of a class because a path from the dominator changes their value (Release 26
# makes a new class of them as well)
fix("0041de40", [("    cse_reinsert_class(g_cse_split_head);", "    GCSE_SPLIT(g_cse_split_head);")])

# --- MDL_CAST_MUL (src/_castmulrules.c, include/castmul.h; only with SHC_REBUILD_UPDATED=1): global
# common-expression elimination notes the heads of the classes of (long)short_variable as it walks the blocks
# (count_global_expressions, cse_eliminate_node), and asks before a class of arithmetic expressions takes a temporary
fix("0041d060", [(INCLUDES, INCLUDES + '\n#include "castmul.h"'),
                 ("  for (blk = g_f_chain->f_next; blk != (bblock *)0x0; blk = blk->f_next) {\n    cse_global_block(blk);",
                  "  CASTMUL_BEGIN();\n  for (blk = g_f_chain->f_next; blk != (bblock *)0x0; blk = blk->f_next) {\n"
                  "    cse_global_block(blk);")])
fix("0041dcc0", [(INCLUDES, INCLUDES + '\n#include "castmul.h"'),
                 ("\n  op = node->op;\n", "\n  CASTMUL_VISIT(node);\n  op = node->op;\n")])
fix("0041dcc0", [(r"(\(\(node->flag2 & 8\) != 0\)\), blk != \(bblock \*\)0x0\) && GCSE_BLOCK_OK\(node,blk\))",
                  r"\1 && CASTMUL_OK(node,blk)")], regex=True)

# --- MDL_MASK_AND (src/_maskrules.c, include/maskrules.h; only with SHC_REBUILD_UPDATED=1): the simplifier asks before
# it turns a mask by 0xff into casts, for `x & 0xff` (simplify_bitand_bitor) and `v &= 0xff` (simplify_and_or_assign)
fix("0040f190", [(INCLUDES, INCLUDES + '\n#include "maskrules.h"'),
                 (r"(uVar6 = is_const_value\((\w+),0xff,node->type\), uVar6 == 0\)\) \{\s*return node;\s*\}\n)",
                  r"\1      if (MASK_TO_CAST(node,\2,1) == 0) {\n        return node;\n      }\n")], regex=True)
fix("0040e780", [(INCLUDES, INCLUDES + '\n#include "maskrules.h"'),
                 (r"if \(\(node->child->flag & 2\) == 0\) \{(\s*\w+ = is_const_value\((\w+),0xffff,node->type\);)",
                  r"if (((node->child->flag & 2) == 0) && (MASK_TO_CAST(node,\2,2) != 0)) {\1")], regex=True)

# --- MDL_REGVAR_LOG (src/_regvarlog.c, include/regvarlog.h; only with SHC_REBUILD_UPDATED=1): the register variables
# assign_physical_registers chose
fix("0041af70", [(INCLUDES, INCLUDES + '\n#include "regvarlog.h"'),
                 ("  add_memory_lregs((short)iVar1);", "  REGVAR_LOG();\n  add_memory_lregs((short)iVar1);")])

print(n, "fixes")
