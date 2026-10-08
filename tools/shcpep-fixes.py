#!/usr/bin/env python3
"""Source fixes to rebuild/shcpep/src that the Ghidra export can't express, and the hooks of the rules, applied after
regen-shcpep.sh's other steps. Each asserts the text it replaces, so a changed export fails instead of skipping.
"""
import os, re, sys
from pathlib import Path

S = Path(__file__).resolve().parent.parent / "rebuild/shcpep/src"
n = 0


def fix(addr, pairs, regex=False, once=False):
    global n
    f = next(S.glob(f"{addr}_*.c"))
    s = f.read_text(encoding="latin-1")
    for old, new in pairs:
        if regex:
            s2, k = re.subn(old, new, s)
        else:
            # literal text, but a single space inside it matches any whitespace (Ghidra re-wraps long lines at a
            # space, or between two closing parentheses, when names change); newlines, indentation and the ends stay exact
            body = old.strip()
            lead, trail = old[:len(old) - len(old.lstrip())], old[len(old.rstrip()):]
            pat = re.escape(lead) + "".join(r"\s+" if t == " " else re.escape(t).replace(r"\)\)", r"\)\s*\)")
                                            for t in re.split(r"(\s+)", body)) + re.escape(trail)
            s2, k = re.subn(pat, lambda m: new, s)
        if k == 0:
            sys.exit(f"shcpep-fixes: {f.name}: not found: {old!r}")
        if once and k != 1:
            sys.exit(f"shcpep-fixes: {f.name}: {k} matches (want 1): {old!r}")
        if k > 1 and os.environ.get("FIXES_VERBOSE"):
            print(f"  {f.name}: {k} x {old!r}")
        s = s2
        n += k
    f.write_text(s, encoding="latin-1")


# emit_branch_around_literal_pool: stock points the operand's label list (local_c.labels) at local_14 (40f594) before
# writing through it; Ghidra ("Heritage AFTER dead removal") put the assignment after the writes, so the rebuild wrote
# through the template pointer copied from DAT_0042ad38 (0)
fix("0040f4e0", [("  local_2c.ea1 = &local_c;\n", "  local_2c.ea1 = &local_c;\n  local_c.labels = &local_14;\n"),
                 ("  (local_c.labels)->next = (label_ref *)0x0;\n  local_c.labels = &local_14;\n",
                  "  (local_c.labels)->next = (label_ref *)0x0;\n")])
# exit: the stock pre-terminators (stock_flsall) flush the stock CRT's stream table, but every file shcpep opens is
# a host CRT FILE of src/_crt_shim.c; flush those at the same point, or a run that ends through exit() without closing
# its files (handle_fault_signal, the fatal message exits) loses their buffered tail (as shcasm-fixes.py)
fix("0041e5a0", [("    stock_initterm((undefined4 *)&stock_xp_a,(undefined4 *)&stock_xp_z);\n",
                  "    stock_initterm((undefined4 *)&stock_xp_a,(undefined4 *)&stock_xp_z);\n"
                  "    _flushall();\n")])
# --- literal-pool diagnostics (SHC_REBUILD_UPDATED only): PEP_LOG=<file>, a line per placement decision;
# PEP_<name>=<int>, the rule's constants and variants (defaults = Release 26). The temporaries of
# decide_literal_pool_placement they use are found in the export (they are renumbered when the function's types
# change): @SZ@ the record's literal bytes, @LIM@ the pool limit, @OP@ the record's op, @CMP@ the label-rule test
def pool_vars(pairs):
    t = next(S.glob("004179a0_*.c")).read_text(encoding="latin-1")
    v = {"@SZ@": re.search(r"(\w+) = \1 \+ 0xe;", t), "@LIM@": re.search(r"\((\w+) = 0x3fc,", t),
         "@OP@": re.search(r"\n  (\w+) = rec->op;\n  local_8 = ", t), "@CMP@": re.search(r"local_9 = !(\w+);", t)}
    for k, m in v.items():
        if not m:
            sys.exit(f"shcpep-fixes: decide_literal_pool_placement: no {k} variable")
    sub = lambda x: re.sub(r"@\w+@", lambda m: v[m.group(0)].group(1) if m.group(0) in v else m.group(0), x)
    global EXP_HEAD
    EXP_HEAD = sub(EXP_HEAD)
    return [(sub(o), sub(n).replace("@EXP_HEAD@", EXP_HEAD)) for o, n in pairs]


EXP_HEAD = r'''
#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
static int pepk(const char *name, int dflt) {
    char *v = getenv(name);
    return v ? (int)strtol(v, 0, 0) : dflt;
}
static void peplog(const char *kind, int op, int c68, int c64, int l4, int i11, int c70, int c6c, int lim, int dec) {
    static FILE *lf; static int opened;
    if (!opened) { char *p = getenv("PEP_LOG"); opened = 1; if (p) lf = fopen(p, "a"); }
    if (lf) { fprintf(lf, "%s %x %d %d %d %d %d %d %d %d\n", kind, op, c68, c64, l4, i11, c70, c6c, lim, dec); fflush(lf); }
}
/* PEP_WFROM / PEP_LFROM: measure the word (long) literal window from the first instruction that references a pending
   word (long) literal instead of from the last pool. pep_segw/l: offset in the current branch segment of the first
   such reference (-1 none); pep_w/l: its offset from the window start once the segment is behind a kept branch */
static int pep_w = -1, pep_l = -1, pep_segw = -1, pep_segl = -1;
#define PEPK(n, d) pepk("PEP_" #n, d)
#define PEPLOG(k, dec) peplog(k, rec->op, g_pool_code_bytes, _g_pool_pending_literal_bytes, local_4, @SZ@, g_pool_carried_code_bytes, _g_pool_carried_literal_bytes, @LIM@, dec)
static int pepadj(int word, int c70) {
    int f;
    if (word) {
        if (!PEPK(WFROM, 0)) return 0;
        f = pep_w >= 0 ? pep_w : (pep_segw >= 0 ? c70 + pep_segw : -1);
    } else {
        if (!PEPK(LFROM, 0)) return 0;
        f = pep_l >= 0 ? pep_l : (pep_segl >= 0 ? c70 + pep_segl : -1);
    }
    return f > 0 ? f : 0;
}
#define PEPADJ() pepadj(g_pool_carried_has_word == 1 || g_pool_segment_has_word == 1, (int)g_pool_carried_code_bytes)
#define PEPTRACK() do { if (@SZ@ == 2 && pep_segw < 0) pep_segw = g_pool_code_bytes; \
                        if (@SZ@ == 4 && pep_segl < 0) pep_segl = g_pool_code_bytes; } while (0)
#define PEPKEEP() do { if (pep_w < 0 && pep_segw >= 0) pep_w = (int)g_pool_carried_code_bytes + pep_segw; \
                       if (pep_l < 0 && pep_segl >= 0) pep_l = (int)g_pool_carried_code_bytes + pep_segl; \
                       pep_segw = pep_segl = -1; } while (0)
#define PEPFLUSH() do { pep_w = pep_segw; pep_l = pep_segl; pep_segw = pep_segl = -1; } while (0)
#define PEPRESET() do { pep_w = pep_l = pep_segw = pep_segl = -1; } while (0)
#else
#define PEPK(n, d) (d)
#define PEPLOG(k, dec) ((void)0)
#define PEPADJ() 0
#define PEPTRACK() ((void)0)
#define PEPKEEP() ((void)0)
#define PEPFLUSH() ((void)0)
#define PEPRESET() ((void)0)
#endif
'''
fix("004179a0", pool_vars([
    ("\nuint __cdecl decide_literal_pool_placement(", "@EXP_HEAD@" + "\nuint __cdecl decide_literal_pool_placement("),
    # branch records: knobs for the flag additions, limits and margin; log before the decision
    ("        @SZ@ = @SZ@ + 0xe;", "        @SZ@ = @SZ@ + PEPK(ADD_E, 0xe);"),
    ("      @SZ@ = @SZ@ + 0x3c;", "      @SZ@ = @SZ@ + PEPK(ADD_3C, 0x3c);"),
    ("@LIM@ = 0x3fc, g_pool_segment_has_word", "@LIM@ = PEPK(LIM_L, 0x3fc), g_pool_segment_has_word"),
    ("      @LIM@ = 0x1fe;", "      @LIM@ = PEPK(LIM_W, 0x1fe);"),
    ("    if ((@LIM@ + -0x30 <", "    PEPLOG(\"B\", -1);\n    if ((@LIM@ - PEPK(MARGIN, 0x30) <"),
    ("(int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + @SZ@ + g_pool_carried_code_bytes + _g_pool_carried_literal_bytes)) ||",
     "(int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + @SZ@ + PEPK(CARRY, 1) * (int)(g_pool_carried_code_bytes + _g_pool_carried_literal_bytes)) - PEPADJ()) ||"),
    ("      local_9 = true;\n      _g_pool_carried_literal_bytes", "      local_9 = true;\n      PEPLOG(\"D\", 1);\n      PEPFLUSH();\n      _g_pool_carried_literal_bytes"),
    ("      local_9 = false;", "      local_9 = false;\n      PEPLOG(\"D\", 0);\n      PEPKEEP();"),
    ("LAB_00418c0c:\n  _g_pool_pending_literal_bytes = _g_pool_pending_literal_bytes + @SZ@;", "LAB_00418c0c:\n  PEPTRACK();\n  _g_pool_pending_literal_bytes = _g_pool_pending_literal_bytes + @SZ@;"),
    # forced flushes (a BRA over the pool) in straight-line code
    ("if (0x3cc < (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + @SZ@))",
     "if (PEPK(FORCE_L, 0x3cc) < (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + @SZ@))"),
    ("else if (0x1ce < (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + @SZ@))",
     "else if (PEPK(FORCE_W, 0x1ce) < (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + @SZ@))"),
    ("        local_9 = true;\n        g_pool_carried_has_word = '\\0';", "        local_9 = true;\n        PEPLOG(\"F\", 1);\n        PEPRESET();\n        g_pool_carried_has_word = '\\0';"),
    ("      local_9 = true;\n      g_pool_carried_has_word = '\\x01';", "      local_9 = true;\n      PEPLOG(\"F\", 2);\n      PEPRESET();\n      g_pool_carried_has_word = '\\x01';"),
    # labels / function ends
    ("        local_9 = !@CMP@;", "        local_9 = !@CMP@;\n        PEPLOG(\"L\", local_9);"),
    ("  @OP@ = rec->op;\n  local_8 = (ea *)0x0;", "  @OP@ = rec->op;\n  @LIM@ = 0;\n  PEPLOG(\"R\", 0);\n  local_8 = (ea *)0x0;"),
    # PEP_LCARRY=1: the label rule also when only carried literals are pending
    ("      if (g_pool_code_bytes + _g_pool_pending_literal_bytes != 0) {",
     "      if (g_pool_code_bytes + _g_pool_pending_literal_bytes + (PEPK(LCARRY, 0) ? _g_pool_carried_literal_bytes : 0) != 0) {"),
    # PEP_LAT11=1: the label rule at a function boundary (0x11) too
    ("LAB_00418aea:\n    if (@OP@ == OP_NON_10) {", "LAB_00418aea:\n    PEPLOG(\"E\", @OP@);\n    if (@OP@ == OP_NON_10 || (@OP@ == OP_CASEJMP && PEPK(LAT11, 0))) {"),
]))
# --- the arcade rules and the pass diagnostics (include/pep_rules.h, src/_pep_rules.c): calls into the settings;
# without SHC_REBUILD_UPDATED the hooks compile to the plain Release 26 code. The anchors are regular expressions over the
# names the tables give (functions, parameters) and capture the decompiler's temporaries, so a re-export that only
# renumbers temporaries still applies; each must match exactly once.
def hooks(addr, pairs):
    # the include once per file (a file may take hooks for two rules)
    if '#include "pep_rules.h"' in next(S.glob(f"{addr}_*.c")).read_text(encoding="latin-1"):
        return fix(addr, pairs, regex=True, once=True)
    fix(addr, [(r'#include "imports.h"\n', '#include "imports.h"\n#include "pep_rules.h"\n')] + pairs, regex=True, once=True)


hooks("0040b860", [(r"\n    (%s)\(\);\n" % c, r"\n    PEPPOST(%d, \1());\n" % k) for k, c in enumerate([
    "rewrite_branch_targets_for_node_list", "clean_records_and_merge_common_code",
    "expand_tail_calls_into_epilogue_jumps", "delete_dead_labels_from_node_list",
    "merge_fallthrough_blocks_and_drop_unused_labels", "optimize_flow_graph"])])
hooks("0040bb90", [(r"\n  (%s)\((\w+)\);\n" % c, r"\n  PEPPASS(%d, \1(\2));\n" % k) for k, c in enumerate([
    "form_predecrement_postincrement_addressing", "merge_repeated_and_or_immediates", "load_compare_operand_into_r0",
    "fold_register_move_into_unary_op", "rewrite_repeated_movi_per_register", "fold_address_add_into_following_load",
    "retarget_result_to_copy_destination", "reuse_loaded_constants_and_copies", "delete_redundant_loads",
    "delete_redundant_memory_loads", "delete_store_load_pairs", "delete_dead_stores", "fold_add_immediates",
    "derive_constant_loads_from_previous"])])
hooks("00401000", [
    (r"(\w+) = simplify_flow_block\((\w+)\);(\n\s+\w+ = \2->next;)", r"\1 = pep_post_skip(8) ? 0 : simplify_flow_block(\2);\3"),
    (r"if \((\w+)->preds != \(flow_edge \*\)0x0\) \{", r"if (\1->preds != (flow_edge *)0x0 && !pep_post_skip(6)) {"),
    (r"if \((\w+)\) \{(\n\s+delete_repeated_r0_constant_loads)", r"if (\1 && !pep_post_skip(7)) {\2")])
# SWITCH_ARCADE_JUMP / SWITCH_ARCADE_BRANCH; PEP_NO_THREAD 2 (no simplification), 1/8/16 (no threading)
hooks("00401a10", [
    (r"(\n  \w+ = '\\0';\n)(  if \(\(\(block == )", r"\1  if (pep_no_thread() & 2) return 0;\n\2"),
    (r"(\((\w+) = (\w+)->code->labno, \2 != 0\)\) &&)", r"\1 !pep_no_thread_here((int *)block, (int *)\3) &&"),
    (r"(\n      if \(\(\w+ == \(flow_edge \*\)0x0\) \|\|)\n", r"\1 keep_jump_to_next((int *)block) ||\n"),
    (r"(\(\(\w+->flags & 1\) != 0\)\)\)\) &&\n)", r"\1        !keep_branch_over_jump((int *)block) &&\n")])
# PEP_R0_FORGET: block_00 is the predecessor (an edge's block), local_14 the target's first record
hooks("00401fb0", [(r"(\(edges->next == \(flow_edge \*\)0x0\)\s*\)\s*&&)",
                    r"\1 !pep_keep_target_head((int)block_00, (unsigned char *)local_14) &&"),
                   # PEP_NO_THREAD 4: no predecessor retargeting here
                   (r"(if \(\(\w+ != '\\x02'\) \|\|)", r"\1 (pep_no_thread() & 4) ||"),
                   (r"(LAB_0040213b:\n\s+if \()", r"\1!(pep_no_thread() & 4) && ")])
hooks("004028f0", [
    (r"(\n  if \(\(\(origin != \(flow_block \*\)0x0\) && \(block != \(flow_block \*\)0x0\)\) && \(movi != \(psd \*\)0x0\)\) \{\n)",
     r"\1#if SHC_REBUILD_UPDATED\n    if (pep_r0_forget() >= 2 || (pep_r0_forget() == 1 && pep_block_is_conditional((int)block))) {\n"
     r"      return;\n    }\n#endif\n"),
    (r"(\n(\s+)(\w+) = \*local_44;\n\s+if \(\(\3->flags2 & 2\) != 0\) \{\n\s+(\w+) = true;\n\s+break;\n\s+\}\n)",
     r"\1#if SHC_REBUILD_UPDATED\n\2if (pep_r0_forget() == 1 && pep_block_is_conditional((int)\3)) {\n"
     r"\2  \4 = true;\n\2  break;\n\2}\n#endif\n")])
# PEP_NO_THREAD 8/16: the labels the cross-jumping pass makes, per function
hooks("0040b860", [(r"(\n)(  g_section_end = 0;\n)", r"\1#if SHC_REBUILD_UPDATED\n  pep_xj_labels_clear();\n#endif\n\2")])
hooks("00413ce0", [(r"(\n  \*\w+ = \(short\)(\w+);\n)", r"\1#if SHC_REBUILD_UPDATED\n  pep_xj_label_mark((short)\2);\n#endif\n")])
# XJUMP_OFF
hooks("004131d0", [(r"((\w+) = find_block_with_common_tail\([^()]*\),)", r"\1 XJUMP_FILTER(\2, rec->op),")])
hooks("00413850", [(r"(\n  \w+ = 0;\n)(  local_8 = )", r"\1#if SHC_REBUILD_UPDATED\n  xjump_tail[0] = 0;\n#endif\n\2"),
                   (r"(LAB_00413ae9:\n(\s+)\w+ = \w+ \+ 1;\n)(\s+local_c = \w+;\n\s+local_8 = (\w+);)",
                    r"\1\2XJ_TAIL((unsigned char *)\4);\n\3")])
# XJUMP_LOG: jt= (the jump temporaries of the two final records) and pv= (the record in front of the tail)
hooks("00413850", [(r"(\n    jump_tmp_reg = rec->tmp;\n)", r"\1    XJ_JT(rec->tmp, -1);\n"),
                   (r"(\n    jump_tmp_reg = rec_b->tmp;\n)", r"\1    XJ_JT(rec->tmp, rec_b->tmp);\n"),
                   (r"(\n)(  \*tail_a = local_c;\n)", r"\1  XJ_PREV(block_a, local_c, block_b, local_8);\n\2")])
# PEP_RET_R0: the jump temporary a RETURN record is given when it is loaded
hooks("00406760", [(r"(\n      rec->flg = '\\0';\n      rec->tmp = )('\\x01');", r"\1PEP_RET_TMP(\2);")])
# PEP_RET_R0: two RETURNs share a tail only as far back as it leaves r0 alone
hooks("00413850", [(r"(\n    jump_tmp_reg = rec_b->tmp;\n    XJ_JT\(rec->tmp, rec_b->tmp\);\n)", r"\1    PEP_RET_PAIR(rec, rec_b, jump_tmp_reg);\n")])
# PEP_RET_R0 bit 4: the exit block of a function whose return tails were shared is not dropped as unreachable
hooks("00401a10", [(r"(\n  if \(edge == \(flow_edge \*\)0x0\) \{\n)(    if \(\(block->prev->flags & 1\) != 0\) \{\n)",
                    r"\1    if (PEP_EXIT_KEPT(block)) {\n      return 0;\n    }\n\2")])
# PEP_AUTOINC: no @rN+ load from "mov.x @rN,rM ... add #n,rN" (bit 1), no @-rN store from "add #-n,rN ... mov.x rM,@rN"
# (bit 2)
hooks("004120d0", [(r"(if \(\(\(\(load_rec != \(psd \*\)0x0\) && \(rec->op == OP_ADD\)\) &&)",
                    r"if ((((load_rec != (psd *)0x0) && !(pep_autoinc() & 1) && (rec->op == OP_ADD)) &&"),
                   (r"(\n(\s+)rec->ea2->type = rec->ea2->type & 0xf0;\n)",
                    r"\n\2if (pep_autoinc() & 2) goto LAB_004123f5;\1")])
# SLOT_NO_STACK
hooks("004162f0", [(r"(\n    (\w+) = delay_slot_masks_disjoint\(\);\n)",
                    r"\1#if SHC_REBUILD_UPDATED\n    if (\2 == 1 && slot_no_stack() != 0 && slot_record_is_frame_access((unsigned char *)cand)) {\n"
                    r"      if (slot_no_stack() == 2) {\n        return 0;\n      }\n      \2 = 0;\n    }\n#endif\n")])
hooks("00417080", [(r"(\n        (\w+) = compute_record_register_masks\((\w+)\);\n        if \(\2 == '\\0'\) \{\n"
                    r"          (\w+) = delay_slot_masks_disjoint\(\);\n        \}\n)",
                    r"\1#if SHC_REBUILD_UPDATED\n        if (slot_no_stack() != 0 && slot_record_is_frame_access((unsigned char *)\3)) {\n"
                    r"          \4 = 0;\n        }\n#endif\n")])
# --- diagnostics (src/_pep_dump.c): XJUMP_LOG TAIL lines (the record after an expanded tail call) and NEXT lines
# (a jump of a block cross-jumping made, deleted as a jump to the next label)
hooks("0040a860", [(r"(\n(\s+)if \(\(\(rec != \(psd \*\)0x0\) && \(op = rec->op, op != OP_LABEL\)\) &&)",
                    r"\n#if SHC_REBUILD_UPDATED\n\2pep_log_tail(rec ? rec->op : 0);\n#endif\1")])
hooks("00414f40", [(r"(\n(\s+)release_label_refs_of_record\(rec,release_mode\);\n)",
                    r"\n#if SHC_REBUILD_UPDATED\n\2pep_log_xj_next((int *)prev_block, rec->op);\n#endif\1")])
# --- PEP_DUMP: the records after loading, after each pass of optimize_current_node_list (PEPPOST) and after the
# flow-graph and delay-slot passes (src/_pep_dump.c)
hooks("0040b860", [(r"(\n  if \(\(g_stage_flags & 0x800\) == 0\) \{\n)(    PEPPOST\(0,)",
                    r'\1#if SHC_REBUILD_UPDATED\n    pep_dump("load", g_current_node_list);\n#endif\n\2'),
                   (r"(\n  fill_branch_delay_slots\(g_current_node_list\);\n)",
                    r'\n#if SHC_REBUILD_UPDATED\n  pep_dump("flow", g_current_node_list);\n#endif\1'
                    r'#if SHC_REBUILD_UPDATED\n  pep_dump("slots", g_current_node_list);\n#endif\n')])
print(n, "fixes")
