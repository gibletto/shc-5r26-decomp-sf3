/* The arcade rules and the pass diagnostics of shcpep (include/pep_rules.h; tools/shcpep-fixes.py puts the calls
   into the generated functions). Each setting is read from the environment: unset = the arcade rule, 0 = Release 26. */
#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void pep_xj_labels_clear(void) { memset(xj_labels, 0, sizeof xj_labels); }
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

/* XJUMP_OFF: cross-jumping (merge_common_block_tails, the stage's "comcd"). When a block ends in a JUMP or RETURN
   ('$' / '"') or a LABEL arrives (0x18), find_block_with_common_tail looks for an earlier block with the same tail
   going to the same place (mode 2: both end in it; mode 1: one falls through into it) and the matching tail is
   shared. The arcade merges JUMP and LABEL tails but not RETURN tails: XJUMP_OFF=2 (unset).
   A value rejects a match: 1 on its own = every match; otherwise bits 1-3 pick the kind (2 RETURN, 4 JUMP,
   8 LABEL; none = all) and bits 4-5 the mode (16 mode 1, 32 mode 2; none = both); 64 leaves tails with a call
   merged. XJUMP_MIN=n: tails of n records or more still merge. XJUMP_LOG=<file>: a line per match (the function, kind, mode,
   count, verdict, the tail's opcodes last first). */
char xjump_tail[256];

void xjump_tail_add(unsigned char *rec)
{
  size_t n = strlen(xjump_tail);
  unsigned char *o = *(unsigned char **)(rec + 0x10);
  if (n < sizeof xjump_tail - 24) {
    if (*rec == 0x2a && o) sprintf(xjump_tail + n, "%02x#%d.", *rec, *(int *)(o + 4));
    else sprintf(xjump_tail + n, "%02x.", *rec);
  }
}

int xjump_reject(char kind, int mode, int count)
{
  int v = env_int("XJUMP_OFF", 2), kinds, modes, r = 0;
  char *lg = getenv("XJUMP_LOG");
  if (v != 0) {
    kinds = v & 0xe; modes = v & 0x30;
    r = (v == 1) || ((kinds == 0 || (kind == '"' && (kinds & 2)) || (kind == '$' && (kinds & 4)) ||
                      (kind == 0x18 && (kinds & 8))) &&
                     (modes == 0 || (mode == 1 && (modes & 16)) || (mode == 2 && (modes & 32))));
  }
  if (r && env_int("XJUMP_MIN", 0) > 0 && count >= env_int("XJUMP_MIN", 0)) r = 0;
  if (r && (v & 0x40) && strstr(xjump_tail, "23.")) r = 0;
  if (lg) {
    FILE *f = fopen(lg, "a");
    if (f) { fprintf(f, "%s %s %d %d %s %s\n", pep_current_function(), kind == '"' ? "RET" : kind == '$' ? "JMP" : "LBL", mode, count, r ? "keep" : "merge",
                      xjump_tail); fclose(f); }
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
#endif
