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

int pep_skip(int k) { return (env_int("PEP_SKIP", 0) >> k) & 1; }
int pep_post_skip(int k) { return (env_int("PEP_POST_SKIP", 0) >> k) & 1; }

/* SWITCH_ARCADE_BRANCH: keep "bt L; bra D; L:" instead of turning it into "bf D". 1: always; 2 (unset): when L is
   a switch case or default label (CLABEL 0x19, DLABEL 0x1a) */
int keep_branch_over_jump(int *target)
{
  int k = env_atoi("SWITCH_ARCADE_BRANCH", 2);
  unsigned char t;
  if (k == 1) return 1;
  if (k == 2 && target && *target) {
    t = *(unsigned char *)(*target + 0x10);
    return t == 0x19 || t == 0x1a;
  }
  return 0;
}

/* SWITCH_ARCADE_JUMP: keep a "bra L" to the next block. 1 (unset): when L is a switch case or default label (the
   arcade's "bra pc+4" for a switch whose only label is default); 2: always */
int keep_jump_to_next(int *target)
{
  unsigned char t;
  int k = env_atoi("SWITCH_ARCADE_JUMP", 1);
  if (k == 2) return 1;
  if (k != 1 || !target || !*target) return 0;
  t = *(unsigned char *)(*target + 0x10);
  return t == 0x19 || t == 0x1a;
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
   remove_target_prefix_executed_by_preds; 8 no threading through a jump-only block whose label the cross-jumping
   pass (make_common_code_block) made; 16 none to a destination label it made. Unset = 28 */
int pep_no_thread(void) { return env_int("PEP_NO_THREAD", 28); }

static unsigned char xj_labels[8192];      /* the labels make_common_code_block made in this function, a bit each */
static unsigned char dead_ref_labels[8192]; /* the labels unreachable code still refers to (PEP_RET_R0 bit 8) */
static int pep_ret_merged;
void pep_xj_labels_clear(void) { memset(xj_labels, 0, sizeof xj_labels); memset(dead_ref_labels, 0, sizeof dead_ref_labels); pep_ret_merged = 0; }
void pep_xj_label_mark(short l) { unsigned short u = (unsigned short)l; xj_labels[u >> 3] |= (unsigned char)(1 << (u & 7)); }
static int pep_xj_label_made(short l) { unsigned short u = (unsigned short)l; return l != 0 && (xj_labels[u >> 3] >> (u & 7)) & 1; }
int pep_xj_label_was_made(short l) { return pep_xj_label_made(l); }

/* blk: the jump-only block, dest: the block it jumps to (their code's labno is at code + 4) */
int pep_no_thread_here(int *blk, int *dest)
{
  int k = pep_no_thread();
  if (k & 1) return 1;
  if ((k & 8) && pep_xj_label_made(*(short *)(*blk + 4))) return 1;
  if ((k & 16) && dest && *dest && pep_xj_label_made(*(short *)(*dest + 4))) return 1;
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
   XJUMP_MIN=n: tails of n records or more still merge. XJUMP_LOG=<file>: a line per match (the function, kind,
   mode, count, verdict, the tail's records last first as op:source>destination, jt= the jump temporaries of the
   two final records, pv= the record in front of the tail in each block (0: the tail is the whole block), sw= the
   switches open, # the match's number in the function). XJUMP_FLIP=<function>:<n>[,...] turns the verdict of that
   match round. */
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

/* XJUMP_FLIP=<function>:<n>[,...] (diagnostic): the verdict of the function's n-th match (from 0) is turned round */
static int xjump_flip(const char *fn, int n)
{
  char *v = getenv("XJUMP_FLIP"), key[160];
  size_t k;
  if (!v) return 0;
  sprintf(key, "%.140s:%d", fn, n);
  k = strlen(key);
  for (; v && *v; v = strchr(v, ','), v = v ? v + 1 : v)
    if (strncmp(v, key, k) == 0 && (v[k] == ',' || v[k] == 0)) return 1;
  return 0;
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
  if (r && env_int("XJUMP_MIN", 0) > 0 && count >= env_int("XJUMP_MIN", 0)) r = 0;
  if (r && (v & 0x40) && strstr(xjump_tail, "23:")) r = 0;
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
#endif
