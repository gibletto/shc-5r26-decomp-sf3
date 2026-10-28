/* The arcade rules and the pass diagnostics of shcpep (include/pep_rules.h; tools/shcpep-fixes.py puts the calls
   into the generated functions). Each setting is read from the environment: unset = the arcade rule, 0 = Release 26. */
#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decls.h"
#include "imports.h"
#include "pep_rules.h"

static int env_int(const char *name, int dflt)
{
  char *v = getenv(name);
  return v ? (int)strtol(v, 0, 0) : dflt;
}

static int env_atoi(const char *name, int dflt)   /* decimal only */
{
  char *v = getenv(name);
  return v ? atoi(v) : dflt;
}

/* PEP_SKIP / PEP_POST_SKIP=<bits> (diagnostic builds only, SHC_REBUILD_DIAG=1): skip passes */
#if SHC_REBUILD_DIAG
int pep_skip(int k) { return (env_int("PEP_SKIP", 0) >> k) & 1; }
int pep_post_skip(int k) { return (env_int("PEP_POST_SKIP", 0) >> k) & 1; }
#else
int pep_skip(int k) { return 0; }
int pep_post_skip(int k) { return 0; }
#endif

/* SWITCH_ARCADE_BRANCH: keep "bt L; bra D; L:" instead of turning it into "bf D". 1 (unset): always; 0: Release 26.
   Value 2 (kept only when L is a switch case or default label) is retired: every C module of 3rd Strike, 2nd Impact
   and New Generation compiles to the same object with 1, so the label's kind decides nothing in the games. */
int keep_branch_over_jump(int *target)
{
  return env_atoi("SWITCH_ARCADE_BRANCH", 1) != 0;
}

/* SWITCH_ARCADE_JUMP: a "bra L" to the next block, which Release 26's flow pass deletes (simplify_flow_block).
   1: kept when L is a switch case or default label (the arcade's "bra pc+4" for a switch whose only label is
      default);
   2: always kept;
   3 (unset): kept unless everything that stood between the jump and L was a bare jump under a plain label nothing
      referred to when the function had been loaded.
   Release 26 deletes a jump to the next label in two places: where a plain label arrives while the function is
   loaded or cleaned up (delete_branch_to_next_label), and in the flow pass, which meets the jumps that came to
   stand in front of their labels only later, when the code in between was deleted as unreachable
   (build_flow_blocks). The arcade's compiler has no jump at the first kind of place and at one class of the
   second: "if (c) { ... } else break;" (or continue, goto), where the else arm is one jump whose label lost its
   only reference while the function was loaded, when the test was sent straight to the jump's destination
   (rewrite_branch_target_chains). Everywhere else it has "bra pc+4":
   - the else arm was shared with a later identical block by cross-jumping and became a jump only then
     (debug_object_edit_move, debug_object_edit_all_char_move);
   - the else arm is "return;" (effect_L2_init);
   - the blocks in between began with case labels: the end of the compare chain of a switch whose cases are all
     "goto" (set_caught_status twice, plef_at_vs_player_damage_union twice), and every place of value 1.
   The game's C routines reach the flow pass's deletion at 71 places. 57 are jumps to a case or default label, kept
   by value 1 as before. Of the 14 to a plain label, the arcade has no jump at 6, all "else break;"
   (search_effect_index twice, Att_RESURRECTION, Att_RESURRECTION2, Auto_Repeat_Sub_Wife, catch_hit_check) and
   "bra pc+4" at the 7 named above; the last, op_bg0_0008, has none where the rule keeps one, behind a case that
   only breaks in front of "default: goto out;". Written with the code after the switch inside that case the
   routine has no such jump and the same instructions as before. No place has a jump to the next plain label with
   nothing deleted in between; the rule would keep it. */
static void *bare_jump[2048];                 /* blocks that were a dead label and a JUMP when loaded */
static int bare_jump_n;
static unsigned char gap_other_labels[8192]; /* labels whose jump lost a block behind it that was not one of those */
static unsigned char gap_any_labels[8192];   /* labels whose jump lost any block behind it (log only) */
static int labbit(unsigned char *set, short l) { unsigned short u = (unsigned short)l; return l != 0 && (set[u >> 3] >> (u & 7)) & 1; }
static void labset(unsigned char *set, short l) { unsigned short u = (unsigned short)l; set[u >> 3] |= (unsigned char)(1 << (u & 7)); }

/* the block's only code record when that is a JUMP, else 0 (labels, line and switch markers do not count) */
static psd *block_bare_jump(code_node *b)
{
  code_node *n;
  psd *j = 0;
  int i;
  for (n = b; n; n = n->next)
    for (i = 0; i < 15; i++) {
      psd_op op = n->psd[i].op;
      if (op == OP_DUMMY || op == OP_LINE || op == OP_SWBGN || op == OP_SWEND || op == OP_LABEL || op == OP_CLABEL ||
          op == OP_DLABEL) continue;
      if (op != OP_JUMP || j) return 0;
      j = &n->psd[i];
    }
  return j;
}

/* from optimize_current_node_list, when the function has been loaded */
void pep_load_scan(void *list)
{
  code_node *b;
  symbol *y;
  int i;
  bare_jump_n = 0;
  memset(gap_other_labels, 0, sizeof gap_other_labels);
  memset(gap_any_labels, 0, sizeof gap_any_labels);
  for (b = (code_node *)list; b; b = b->next_block) {
    if (b->labno <= 0 || !block_bare_jump(b)) continue;
    for (i = 0; i < 15 && b->psd[i].op == OP_DUMMY; i++) ;
    if (i == 15 || b->psd[i].op != OP_LABEL) continue;
    for (y = g_symbol_hash[b->labno % 0x3fd]; y && y->number != b->labno; y = y->hash_next) ;
    if (y && y->ref_count == 0 && bare_jump_n < 2048) bare_jump[bare_jump_n++] = b;
  }
}

/* from build_flow_blocks, which deletes the unlabelled blocks behind an unconditional jump: jump_labno is that jump's
   label, dead the block about to be deleted */
void pep_gap_note(short jump_labno, void *dead)
{
  int i;
  if (jump_labno == 0 || !block_has_code_records((code_node *)dead)) return;   /* an empty block is nothing */
  labset(gap_any_labels, jump_labno);
  for (i = 0; i < bare_jump_n; i++)
    if (bare_jump[i] == dead && block_bare_jump((code_node *)dead)) return;
  labset(gap_other_labels, jump_labno);
}

int keep_jump_to_next(int *target)
{
  unsigned char t;
  short l;
  int k = env_atoi("SWITCH_ARCADE_JUMP", 3), r;
  char *lg;
  if (!target || !*target) return 0;
  t = *(unsigned char *)(*target + 0x10);
  l = *(short *)(*target + 4);
  r = k == 2 || ((k == 1 || k == 3) && (t == 0x19 || t == 0x1a)) ||
      (k == 3 && (labbit(gap_other_labels, l) || !labbit(gap_any_labels, l)));
  if ((lg = getenv("JNEXT_LOG")) != 0) {
    FILE *f = fopen(lg, "a");
    if (f) { fprintf(f, "%s L%d op=%x gap=%d other=%d %s\n", pep_current_function(), l, t, labbit(gap_any_labels, l),
                     labbit(gap_other_labels, l), r ? "keep" : "delete"); fclose(f); }
  }
  return r;
}

/* PEP_R0_FORGET: a constant in r0 is not carried into the successors of a conditional branch.
   1: no r0 constant crosses a conditional-branch edge, and a branch target keeps a leading mov #imm,r0 its
      conditional predecessor already executed;
   2: no r0 constant crosses any block boundary (and the leading mov #imm,r0 as 1);
   3 (unset): as 1 for the leading instructions, every one of them kept */
int pep_r0_forget(void) { return env_int("PEP_R0_FORGET", 3); }
int pep_block_is_conditional(int b) { return *(int *)(b + 8) != 0 && (*(unsigned char *)(b + 0x24) & 1) == 0; }

/* remove_target_prefix_executed_by_preds deletes a branch target's leading instructions that its only predecessor
   already executed; behind a conditional branch the arcade keeps them */
int pep_keep_target_head(int pred, unsigned char *head)
{
  int k = pep_r0_forget();
  if (k == 0 || *(int *)(pred + 8) == 0 || (*(unsigned char *)(pred + 0x24) & 1) != 0) return 0;
  if (k == 3) return 1;
  return *head == 0x2a && *(char *)(*(int *)(head + 0x14) + 1) == '\0';
}

/* PEP_NO_THREAD, bits: 1 no jump threading in simplify_flow_block (the predecessors of a block that only jumps on
   keep their target); 2 simplify_flow_block never runs; 4 no predecessor retargeting in
   remove_target_prefix_executed_by_preds; 16 no threading to a destination label the cross-jumping pass
   (make_common_code_block) made. Bit 8 (none through a jump-only block whose label that pass made) is retired:
   no game module needs it (round 50). Unset = 20 */
int pep_no_thread(void) { return env_int("PEP_NO_THREAD", 20); }

static unsigned char xj_labels[8192];      /* the labels make_common_code_block made in this function, a bit each */
static unsigned char dead_ref_labels[8192]; /* the labels unreachable code still refers to (PEP_RET_R0 bit 8) */
static int pep_ret_merged;
static void pep_swend_clear(void);
void pep_xj_labels_clear(void) { pep_swend_clear(); memset(xj_labels, 0, sizeof xj_labels); memset(dead_ref_labels, 0, sizeof dead_ref_labels); pep_ret_merged = 0; }
void pep_xj_label_mark(short l) { unsigned short u = (unsigned short)l; xj_labels[u >> 3] |= (unsigned char)(1 << (u & 7)); }
static int pep_xj_label_made(short l) { unsigned short u = (unsigned short)l; return l != 0 && (xj_labels[u >> 3] >> (u & 7)) & 1; }
int pep_xj_label_was_made(short l) { return pep_xj_label_made(l); }

/* blk: the jump-only block, dest: the block it jumps to (their code's labno is at code + 4) */
int pep_no_thread_here(int *blk, int *dest)
{
  int k = pep_no_thread();
  if (k & 1) return 1;
  if ((k & 16) && dest && *dest && pep_xj_label_made(*(short *)(*dest + 4))) return 1;
  /* PEP_SWITCH_END: no threading past a kept switch break label */
  if (blk && *blk && PEP_SWEND_KEPT(*(short *)(*blk + 4))) return 1;
  return 0;
}

/* PEP_RET_R0: returns that end in the same instructions. Bits (unset: 15; 0: Release 26):
   1  the jump temporary of a RETURN record (the register a far jump to the function's exit may use) is r0.
      shcgen writes none for a RETURN; shcpep gives the record one when it loads it (read_sua_pseudo_instruction):
      r1 in Release 26. The temporary is what the later passes ask about:
      - cross-jumping stops a common tail at the first record, counted back from the jump, that uses the temporary
        of the earlier block's final record (count_common_tail_records). With r0 two returns share a tail only as
        far back as it leaves r0 alone: "return 0;" and "return x;" tails (mov #K,r0) are never shared, a store or
        a call with its arguments in front of "return;" is (effect_59_move, comm_sajp, effect_A9_move). Two
        RETURNs are held to r0 whatever temporary the earlier one carries: a JUMP that the load-time chain rewrite
        turned into a RETURN (rewrite_branch_target_chains) keeps Release 26's r1 for a JUMP that meets it
        (sa_gauge_color_set shares mov.w r0,@(12,r5) with such a block), but two of them do not share mov #2,r0
        (defense_ground);
      - a record that uses the temporary cannot fill the delay slot of that jump, so a jump made from a RETURN
        keeps a nop behind an r0 record (mov.w r3,@(r0,r14) / bra / nop in effect_59_move,
        get_damage_reaction_data, Setup_Win_Mark) where the jump of a "break" takes it (effect_L2_move).
   2  inside a switch a RETURN's tail is not shared when it is the whole of the later block and that block
      starts at a label: seven such blocks stay apart in the arcade (effect_D0_move three times, effH5_0004,
      Win_07000, effect_I2_move, effect_G6_move) and none is shared; outside a switch they are shared
      (get_damage_reaction_data). An observed class: the stage's reason for it is not known.
   4  when two RETURN tails were shared in a function its exit block stays although no branch reaches it any
      more: every path now ends in a tail call, and the arcade still has the unreached epilogue and rts behind
      the last jump (comm_rljmp, comm_ifcom, comm_ifrlf, comm_ayjmp, comm_rngc, comm_pjmp). Release 26's flow
      pass (simplify_flow_block) drops a block that follows an unconditional transfer and has no predecessor;
      a tail shared with the fall-through into the exit label (mode 1) leaves none behind (sa_gauge_trans).
   8  code that cannot be reached keeps the reference of its jump. build_flow_blocks deletes the unlabelled blocks
      behind an unconditional jump, and Release 26 then takes the block's jump off the count of its target label
      (decrement_label_ref_count), so a label only such code referred to dies with it. The arcade's compiler leaves
      the count: when the target is the function's exit label the exit block stays, as it does after shared
      returns (bit 4), although nothing reaches it. The case in the arcade program is the "break" behind an
      if/else whose arms both end in a tail call ("if (c) f(); else g(); break;" at the end of a function).
      expand_tail_calls_into_epilogue_jumps deletes the record behind a tail call only when it is a RETURN, EXIT
      or JUMP; behind the else arm's call it is the label that ends the if, so the break's jump to the exit
      label stays. That label then loses its references (the first arm's jump over the else went with its own
      tail call, or to the arms' shared tail), is deleted, and the jump is unreachable code behind a tail call.
      Six routines of the arcade program have the epilogue there (Win_06000, Win_15000, op_101_move,
      op_102_move, effect_21_move, effect_24_move); a switch whose arms each end in one call has none
      (effect_46_move), with either setting. With the rule four of the six match as their source stood and the
      other two as an if/else; no other routine of the game changes.
      Left open: hit_combo_check keeps its exit behind a tail merged with the fall-through (mode 1) and one
      "f(); return;". Not releasing the RETURN a tail call's expansion deletes gives it (and comm_if_l's) but
      costs five matched routines (Small_Jump_Measure, player_face_char_set, player_grade_char_set,
      effect_D3_move, effect_D8_move), so that is not the reason. */
int pep_ret_r0(void) { return env_int("PEP_RET_R0", 15); }

/* bit 8, from build_flow_blocks: 1 = the deleted block's reference to labno is left counted */
int pep_dead_ref_kept(short labno)
{
  unsigned short u = (unsigned short)labno;
  if ((pep_ret_r0() & 8) == 0) return 0;
  dead_ref_labels[u >> 3] |= (unsigned char)(1 << (u & 7));
  return 1;
}

/* the exit block (PEP_RET_R0 bits 4 and 8), from simplify_flow_block: 1 = keep a block no branch reaches. pep_ret_merged
   is set when two RETURN tails are shared (mode 2) and cleared at the start of a function. */
int pep_exit_kept(void *fb)
{
  flow_block *b = (flow_block *)fb;
  code_node *node = b->code;
  symbol *sym;
  short labno;
  if ((b->flags & 2) == 0 || node == 0 || (labno = node->labno) < 0xb7)
    return 0;
  if (!((pep_ret_r0() & 4) && pep_ret_merged) &&
      !((pep_ret_r0() & 8) && ((dead_ref_labels[(unsigned short)labno >> 3] >> (labno & 7)) & 1)))
    return 0;
  for (sym = g_symbol_hash[labno % 0x3fd]; sym && sym->number != labno; sym = sym->hash_next) ;
  return sym != 0 && sym->ref_count > 0;
}

/* XJUMP_OFF: cross-jumping (merge_common_block_tails, the stage's "comcd"). When a block ends in a JUMP or RETURN
   ('$' / '"') or a LABEL arrives (0x18), find_block_with_common_tail looks for an earlier block with the same tail
   going to the same place (mode 2: both end in it; mode 1: one falls through into it) and the matching tail is
   shared. A value rejects a match: 1 on its own = every match; otherwise bits 1-3 pick the kind (2 RETURN, 4 JUMP,
   8 LABEL; none = all) and bits 4-5 the mode (16 mode 1, 32 mode 2; none = both); 64 leaves tails with a call
   merged. Unset: 0 with PEP_RET_R0 (the tails the arcade does not merge fall out of the return's temporary), 2
   without it (no RETURN tail merges, the rule PEP_RET_R0 replaces).
   XJUMP_MIN=n (diagnostic builds only): tails of n records or more still merge. XJUMP_LOG=<file>: a line per match (the function, kind,
   mode, count, verdict, the tail's records last first as op:source>destination, jt= the jump temporaries of the
   two final records, pv= the record in front of the tail in each block (0: the tail is the whole block), sw= the
   switches open, # the match's number in the function). XJUMP_FLIP=<function>:<n>[,...] (diagnostic builds only)
   turns the verdict of that match round. */
char xjump_tail[1024];
int xjump_jt_a, xjump_jt_b;

static void xj_ea(char *d, unsigned char *o)
{
  if (!o) { strcpy(d, "-"); return; }
  if ((o[0] & 0x1f) == 7) sprintf(d, "#%d", *(int *)(o + 4));
  else if ((o[0] & 0x1f) == 9) sprintf(d, "%x.%d.%d", o[0] & 0x1f, (signed char)o[1], (signed char)o[2]);
  else sprintf(d, "%x.%d", o[0] & 0x1f, (signed char)o[1]);
}

void xjump_tail_add(unsigned char *rec)
{
  size_t n = strlen(xjump_tail);
  char a[32], b[32];
  if (n < sizeof xjump_tail - 80) {
    if (*rec >= 0x20) {
      xj_ea(a, *(unsigned char **)(rec + 0x10)); xj_ea(b, *(unsigned char **)(rec + 0x14));
      sprintf(xjump_tail + n, "%02x:%s>%s;", *rec, a, b);
    }
    else sprintf(xjump_tail + n, "%02x;", *rec);
  }
}

/* the record in front of the common tail in each block (0: the tail is the whole block) */
int xjump_prev_a, xjump_prev_b;
void xjump_prev(void *ba, void *ta, void *bb, void *tb)
{
  unsigned char *p;
  xjump_prev_a = xjump_prev_b = -1;
  if (ta) { p = (unsigned char *)find_previous_psd_record(ba, ta); xjump_prev_a = p ? *p : 0; }
  if (tb) { p = (unsigned char *)find_previous_psd_record(bb, tb); xjump_prev_b = p ? *p : 0; }
}

/* diagnostics for the log: switches open at this point of the function being loaded, and whether the current
   block starts at a case or default label */
static int xj_switch_depth(void)
{
  code_node *b, *n; int i, d = 0;
  for (b = g_current_node_list; b; b = b->next_block)
    for (n = b; n; n = n->next)
      for (i = 0; i < 15; i++) {
        if (n->psd[i].op == OP_SWBGN) d++;
        else if (n->psd[i].op == OP_SWEND) d--;
      }
  for (n = g_current_block; n; n = n->next)
    for (i = 0; i < 15; i++) {
      if (n->psd[i].op == OP_SWBGN) d++;
      else if (n->psd[i].op == OP_SWEND) d--;
    }
  return d;
}

/* XJUMP_FLIP=<function>:<n>[,...] (diagnostic builds only, SHC_REBUILD_DIAG=1): the verdict of the function's
   n-th match (from 0) is turned round */
static int xjump_flip(const char *fn, int n)
{
#if !SHC_REBUILD_DIAG
  return 0;
#else
  char *v = getenv("XJUMP_FLIP"), key[160];
  size_t k;
  if (!v) return 0;
  sprintf(key, "%.140s:%d", fn, n);
  k = strlen(key);
  for (; v && *v; v = strchr(v, ','), v = v ? v + 1 : v)
    if (strncmp(v, key, k) == 0 && (v[k] == ',' || v[k] == 0)) return 1;
  return 0;
#endif
}

/* the common tail holds a mov between two registers (a "40:1.n>1.m;" record in xjump_tail) */
static int xj_reg_move(void)
{
  const char *p;
  int a, b;
  int any = 0;
  for (p = xjump_tail; *p; p = strchr(p, ';') ? strchr(p, ';') + 1 : p + strlen(p)) {
    if (strncmp(p, "40:", 3) != 0) return 0;          /* every record of the tail is a mov */
    if (sscanf(p, "40:1.%d>1.%d;", &a, &b) == 2) any = 1;
  }
  return any;
}

int xjump_reject(char kind, int mode, int count)
{
  static char last_fn[160];
  static int seq;
  int v = env_int("XJUMP_OFF", (pep_ret_r0() & 1) ? 0 : 2), kinds, modes, r = 0;
  char *lg = getenv("XJUMP_LOG");
  const char *fn = pep_current_function();
  if (strncmp(last_fn, fn, sizeof last_fn - 1) != 0) { strncpy(last_fn, fn, sizeof last_fn - 1); seq = 0; }
  else seq++;
  if (v != 0) {
    kinds = v & 0xe; modes = v & 0x30;
    r = (v == 1) || ((kinds == 0 || (kind == '"' && (kinds & 2)) || (kind == '$' && (kinds & 4)) ||
                      (kind == 0x18 && (kinds & 8))) &&
                     (modes == 0 || (mode == 1 && (modes & 16)) || (mode == 2 && (modes & 32))));
  }
#if SHC_REBUILD_DIAG
  if (r && env_int("XJUMP_MIN", 0) > 0 && count >= env_int("XJUMP_MIN", 0)) r = 0;
#endif
  if (r && (v & 0x40) && strstr(xjump_tail, "23:")) r = 0;
  /* XJUMP_2I (2nd Impact's compiler revision, default off): tails the 2nd Impact pep does not merge.
     bit 2: a label tail (mode 1, jt=2,-1, no switch open) holding a register-to-register move (entry_2
            Entry_01_Sub: `Ignore_Entry[0] = 0; Ignore_Entry[1] = 0;` in both arms of an if/else), two or more
            records long (sc_trans sa_stock_trans merges its one-record `mov r4,r14` tail);
     bit 16: a jump tail (mode 2) outside switches, two or more records of moves holding a register-to-register
            move, both behind a label (pv=18,18; EFFB8 effect_B8_init's Super_Arts cases `mov r6,r4; bra end;
            mov.w r4,@r5`, jt=2,3); bgst100 bg090_demo_check's pv=0,0 tail of the same shape is merged.
     Bits 4 (one-call tails outside switches), 8 (a dead block's jump gives its label reference back) and 32
     (call-plus-slot label tails) are retired: every C module of 2nd Impact and New Generation compiles to the same
     object without them (their sc_trans and VITAL routines no longer reach them).
     Bit 1 (every jt=2,-1 label tail outside switches) is a diagnostic: it moves 448 objects. */
  if (!r) {
    int x2 = env_int("XJUMP_2I", 0), sw = xj_switch_depth();
    if ((x2 & 1) && kind == 0x18 && mode == 1 && xjump_jt_a == 2 && xjump_jt_b == -1 && sw == 0) r = 1;
    if ((x2 & 2) && kind == 0x18 && mode == 1 && count >= 2 && xjump_jt_a == 2 && xjump_jt_b == -1 && sw == 0 &&
        xj_reg_move())
      r = 1;
    if ((x2 & 16) && kind == '$' && mode == 2 && count >= 2 && sw == 0 && xjump_prev_a == 0x18 &&
        xjump_prev_b == 0x18 && xj_reg_move())
      r = 1;
  }
  if (!r && kind == '"' && mode == 2 && (pep_ret_r0() & 2) && xjump_prev_a >= 0x18 && xjump_prev_a <= 0x1a &&
      xj_switch_depth() > 0) r = 1;
  if (xjump_flip(fn, seq)) r = !r;
  if (!r && kind == '"' && mode == 2) pep_ret_merged = 1;
  if (lg) {
    FILE *f = fopen(lg, "a");
    if (f) { fprintf(f, "%s %s %d %d %s %s jt=%d,%d pv=%x,%x sw=%d #%d\n", fn, kind == '"' ? "RET" : kind == '$' ? "JMP" : "LBL", mode, count,
                     r ? "keep" : "merge", xjump_tail[0] ? xjump_tail : "-", xjump_jt_a, xjump_jt_b, xjump_prev_a, xjump_prev_b, xj_switch_depth(), seq); fclose(f); }
  }
  return r;
}

/* SLOT_NO_STACK: no stack-frame load or store (@(d,r15), @r15) in a branch delay slot. 1 (unset): such a record is
   not a candidate and the backward scan goes on to earlier records (one copied from the branch target stays out
   too); 2: it ends the scan (the slot keeps its nop); 3: as 1, but a local's address (mov r15,rN) may fill the slot.
   Pushes (@-r15) and pops (@r15+) are left alone: the arcade fills slots with them. */
int slot_no_stack(void) { return env_int("SLOT_NO_STACK", 1); }

static int slot_operand_is_frame(unsigned char *op)
{
  int k;
  if (op == 0) return 0;
  k = op[0] & 0x1f;
  return (k == 2 || k == 8) && (op[1] == 0xf || op[1] == 0x6c);
}

int slot_record_is_frame_access(unsigned char *rec)
{
  if (rec[0] == 0x28) return slot_no_stack() != 3;  /* the address of a local (mov r15,rN) */
  return rec[0] == 0x27 || slot_operand_is_frame(*(unsigned char **)(rec + 0x10)) ||
         slot_operand_is_frame(*(unsigned char **)(rec + 0x14));
}

/* PEP_AUTOINC: form_predecrement_postincrement_addressing turns "mov.x @rN,rM ... add #n,rN" into a post-increment load
   and "add #-n,rN ... mov.x rM,@rN" into a pre-decrement store, across any records that leave rN alone. The arcade's
   compiler does neither: its auto-increment and auto-decrement operands are the ones shcgen made.
   Bits (unset: 3; 0: Release 26):
   1  no post-increment loads. The arcade's loads take @rN+ only for *p++ in the source: a separate p++ after *p
      stays an add (fifo_get's dat = *rd; q->rd = ++rd, effect_21_init, sound_system_init, effect_14_move,
      dbg_disasm_rows).
   2  no pre-decrement stores. shcgen makes @-rN for *--p = x only while p is used afterwards; when it is not,
      shcmdl drops the dead decrement and leaves *(p - n) = x, which shcgen emits as add #-n,rN and a plain store.
      The arcade keeps that pair: all six such pairs in its optimized C routines (the second *--dst = *--src of
      set_char_move_init, set_char_move_init2, char_move_cmms2, char_move_cmms3, comm_gets and comm_retmj) are
      apart, and each of its eight pre-decrement stores through a register other than r15 is followed by another
      use of the register, so none needs this pass. */
int pep_autoinc(void) { return env_int("PEP_AUTOINC", 3); }

/* PEP_CASE_WORD: decide_literal_pool_placement measures the distance to the next literal pool against the long
   reach (1020 bytes), or the word reach (510) while the code since the last branch holds a word literal. At a switch
   jump table Release 26 starts over: it clears that flag along with the counts. The arcade's compiler leaves the
   flag alone, so a word literal loaded just before the table still shortens the reach when the pool after the table
   is placed (the flag is next cleared at the first branch record behind the table, which copies it to the carried
   state). Unset: 1; 0: Release 26.
   op_bg0_0001 (end_main.c) loads a word constant before its 50-way table; with the flag kept its third pool lands
   after the tenth case as in the arcade instead of after the thirteenth, and the pools of the ten routines behind
   it, which share one run of pending literals, land where the arcade has them. Ten of the 28 jump tables in the SF3
   program follow a word literal; no routine's pools move away from the arcade's with the flag kept. */
int pep_case_word(void) { return env_int("PEP_CASE_WORD", 1); }

/* PEP_RET_MAC: a RETURN in a function that saves two or more registers is a jump to the exit, and
   decide_literal_pool_placement counts four bytes for the exit label a far jump would load; with fewer than two the
   epilogue is copied in place and no literal is counted. Release 26 counts MACH and MACL among the saved registers
   for that test. The arcade's compiler does not: in a function that saves one register and MACL its returns add
   nothing to the estimate, though they are still emitted as jumps to the exit. Unset: 1; 0: Release 26.
   check_combo_end (r14 and MACL, six returns) is the case in the arcade program: PLCNTDAT.c's last pool sits behind
   its fourth return, where the Release 26 estimate (476 against the limit 462) asks for it behind the third; without
   the four exit literals it is 460. No other routine's pools move with the rule. */
int pep_ret_mac(void) { return env_int("PEP_RET_MAC", 1); }
/* PEP_SWITCH_END=1 (si2fx2's probe, 2nd Impact end_2's two end_200_3000-like routines): the break label of a switch
   nested in another switch, with two case bodies or more, that ends the arm of an if whose end label heads a block
   starting with the outer break's JUMP, stays a label of its own for threading: the load-time walk's savelab is put
   back, the walk over predecessor label-only blocks in rewrite_branch_target_chains stops at it, and
   simplify_flow_block does not thread its predecessors past it. 2i keeps the inner breaks on the label and the
   literal pool goes behind the last but one case. Our Release 26 threads them to the outer break target.
   The switch shape: the block in front of the label holds only the SWEND marker; a case body is a run of case
   labels at the switch's own depth.
   Bit 2 keeps the label between adjacent nested switch ends, even when the marker-only
   block carries another plain label. No executable record may intervene. Off by default. */
int pep_switch_end(void) { return env_int("PEP_SWITCH_END", 0); }
static unsigned char swend_noted[8192], swend_kept[8192], swend_ctarget[8192];
static symbol *swend_pend_sym; static short swend_pend_old, swend_pend_next;
/* Bit 2 preserves a label between consecutive switch-end markers. The load-time branch
   walk stops at these structured boundaries; the later flow pass must not thread through
   the empty block left when its markers are removed. */
static short swend_pair_label;
#define SWEND_BIT(t, l) (((t)[(unsigned short)(l) >> 3] >> ((unsigned short)(l) & 7)) & 1)
#define SWEND_SET(t, l) ((t)[(unsigned short)(l) >> 3] |= (unsigned char)(1 << ((unsigned short)(l) & 7)))
static void pep_swend_clear(void)
{
  memset(swend_noted, 0, sizeof swend_noted); memset(swend_kept, 0, sizeof swend_kept);
  memset(swend_ctarget, 0, sizeof swend_ctarget); swend_pend_sym = 0; swend_pair_label = 0;
}
int pep_swend_kept(short l) { return l != 0 && SWEND_BIT(swend_kept, l); }

/* the number of case bodies of the switch closed last in the function being loaded */
static int swend_last_bodies(void)
{
  code_node *b, *n; int i, d = 0, last = 0; unsigned char runs[64]; psd_op prev = OP_DUMMY;
  for (b = g_current_node_list; ; b = b->next_block) {
    for (n = b ? b : g_current_block; n; n = n->next)
      for (i = 0; i < 15; i++) {
        psd_op op = n->psd[i].op;
        if (op == OP_DUMMY || op == OP_LINE) continue;
        if (op == OP_SWBGN) { if (d < 64) runs[d] = 0; d++; }
        else if (op == OP_SWEND) { if (d > 0) d--; last = d < 64 ? runs[d] : 0; }
        else if (op == OP_CLABEL && prev != OP_CLABEL && d > 0 && d <= 64 && runs[d - 1] < 100) runs[d - 1]++;
        prev = op;
      }
    if (!b) break;
  }
  return last;
}

/* each record loaded: conditional branch targets; the first code record of the block after a pending label */
void pep_swend_record(void *rec, int op, short labno)
{
  psd *r = (psd *)rec;
  if (!pep_switch_end()) return;
  if ((pep_switch_end() & 2) && swend_pair_label && op != OP_LABEL && op != OP_CLABEL && op != OP_DLABEL &&
      op != OP_FLABEL && op != OP_LINE && op != OP_DUMMY) {
    if (op == OP_SWEND) SWEND_SET(swend_kept, swend_pair_label);
    swend_pair_label = 0;
  }
  if ((op == OP_JUMPT || op == OP_JUMPF) && r->ea1 != 0 && r->ea1->labels != 0 && r->ea1->labels->labno1 != 0)
    SWEND_SET(swend_ctarget, r->ea1->labels->labno1);
  if (swend_pend_sym != 0 && op != OP_LABEL && op != OP_CLABEL && op != OP_DLABEL && op != OP_FLABEL &&
      op != OP_LINE && op != OP_DUMMY) {
    if (op == OP_JUMP && labno == swend_pend_next) {
      SWEND_SET(swend_kept, swend_pend_sym->number);
      swend_pend_sym->savelab = swend_pend_old;
    }
    swend_pend_sym = 0;
  }
}

/* a label loaded: is it the break label of a nested switch with two case bodies or more */
void pep_swend_label(void *prev_block, short l)
{
  code_node *n; int i, sw = 0, only_marker = 1;
  if (!pep_switch_end() || !prev_block || l == 0) return;
  if (pep_switch_end() & 2) {
    for (n = (code_node *)prev_block; n; n = n->next)
      for (i = 0; i < 15; i++) {
        psd_op op = n->psd[i].op;
        if (op == OP_SWEND) sw = 1;
        else if (op != OP_DUMMY && op != OP_LINE && op != OP_LABEL) only_marker = 0;
      }
    swend_pair_label = sw && only_marker ? l : 0;
    sw = 0;
  }
  if (!(pep_switch_end() & 1)) return;
  for (n = (code_node *)prev_block; n; n = n->next)
    for (i = 0; i < 15; i++) {
      psd_op op = n->psd[i].op;
      if (op == OP_SWEND) sw = 1;
      else if (op != OP_DUMMY && op != OP_LINE) return;
    }
  if (sw && xj_switch_depth() > 0 && swend_last_bodies() >= 2) SWEND_SET(swend_noted, l);
}

/* the load-time walk gives a noted label the savelab l: pending when l ends an if (a conditional branch goes to it) */
void pep_swend_walk(void *sym, short l)
{
  symbol *s = (symbol *)sym;
  if (!pep_switch_end() || s == 0 || s->number == 0 || !SWEND_BIT(swend_noted, s->number) || !SWEND_BIT(swend_ctarget, l))
    return;
  swend_pend_sym = s; swend_pend_old = s->savelab; swend_pend_next = l;
}

/* PEP_RETURN_EXIT: deleting a return to the adjacent epilogue leaves its literal
   as the last real record of a separate block. Treat a bare adjacent exit as
   its continuation for candidate eligibility; all motion and dependency checks
   remain in fill_cond_branch_slot_from_target. Unset preserves Release 26. */
int pep_terminal_literal_exit(void *block_ptr, void *rec_ptr)
{
  code_node *block = (code_node *)block_ptr;
  psd *rec = (psd *)rec_ptr;
  code_node *node;
  psd *part;
  int i, saw_exit = 0, saw_label = 0;
  if (!env_int("PEP_RETURN_EXIT", 0)) return 0;
  if (!block || !rec || block->target_labno || (block->flags & 1)) return 0;
  if (rec->op != OP_MOVI || !rec->ea1 || !rec->ea2) return 0;
  if ((rec->ea1->type & 31) != 7 || rec->ea1->labels) return 0;
  if ((rec->ea2->type & 31) != 1 || rec->ea2->base < 0 || rec->ea2->base > 15) return 0;
  if (find_next_psd_record(block, rec)) return 0;
  node = block->next_block;
  if (!node || node->target_labno) return 0;
  for (; node; node = node->next) {
    for (i = 0, part = node->psd; i < 15; ++i, ++part) {
      switch (part->op) {
      case OP_DUMMY: case OP_LINE: case OP_BBGN: case OP_BEND:
        break;
      case OP_LABEL:
        if (saw_exit || saw_label) return 0;
        saw_label = 1;
        break;
      case OP_EXIT:
        if (saw_exit) return 0;
        saw_exit = 1;
        break;
      default:
        return 0;
      }
    }
  }
  return saw_exit;
}

#endif
