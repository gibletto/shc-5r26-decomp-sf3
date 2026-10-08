/* GEN_R0VAR (only with SHC_REBUILD_UPDATED=1): the statement's "r0 variable".

   For each statement, count_indexed_address_operands counts the variables used as either side of an indexed address
   (@(r0,Rn): the sum of two identifiers) and count_deref_use keeps the most used one; when it covers enough of the
   statement's indexed addresses, move_r0_variable_operand_into_r0 copies it into r0 once and the statement's
   indexed addresses all use it there (mov r14,r0 ... @(r0,r9) ... @(r0,r12)). The arcade's compiler does not: it
   puts the other operand, the array's address, in r0 for each access and keeps the index where it is
   (Flash_Please, clear_bs2_floor's two arrays in one loop, Ck_Win_Record's
   Stock_Win_Record[Winner_id] = Win_Record[Winner_id]; Com_Random_Select's xx[zz], paring_check).

   Measured on the game (Street Fighter III 3rd Strike, every C routine), counting the mechanism's signature, a
   register copied into r0 and then used as the index of accesses with two or more different bases: the arcade has
   1 such place in its whole code (plcnt_b_die), Release 26 on our source 70, and with no r0 variable 1, the
   arcade's. The
   instructions of 115 routines change; counted as instructions the arcade has and ours has not, 98 come closer to
   the arcade, 7 stay level and 10 move away, all 10 routines that already differ elsewhere (Additinal_Score_DM,
   Sel_PL_Sub_CU, Update_BI_Term, debug_held_pad_repeat, debug_parts_copy_overlap, effect_work_init,
   setup_bonus_car_parts, win_mark_write, wipe_mask_set_cols, wipe_pattern_restore_cols); in none of them does the
   arcade share r0 between two bases. Where the arcade keeps an index in a register and puts each array's address
   in r0, this stage still copies the index into a callee-saved home first (wipe_pattern_restore_cols: mov r7,r14;
   mov r5,r0; @(r0,r14); mov r9,r0; @(r0,r14), against the arcade's mov r7,r0; @(r0,r5); mov r11,r0; @(r0,r5)):
   that is a different decision, taken before this one, and is not changed here.

   GEN_R0VAR=<n> (unset: 2, the arcade rule; 0: Release 26)
     2  no r0 variable
     1  measured, worse: on a tie the operand counted later becomes the r0 variable (Release 26 keeps the first)
     3, 4, ...  measured, worse: an r0 variable only when it is used in at least 2, 3, ... indexed addresses of the
        statement (3 gives back OBJ_Control, Com_Before_Follow and the wipe_* routines, and loses Ck_Win_Record,
        Select_CPU_1st, Exit_2nd and debug_memcmp_u32)
   Also measured worse: counting only a cast operand ((s32)x + table) as an r0 variable candidate.
     5  no r0 variable, r0 still avoided by the chooser as if held (loses the cast index exts.w r4,r0 of src[x])
     6  no r0 variable, chooser scans down as if held but keeps r0 preferences
     7  no r0 variable, chooser held as in 6, and a template slot (assign_template_slot_registers adds r0 to every
        temp's preference) keeps r0 only as the left operand of an ID+ID / cast+ID indexed address or outside an
        address under a dereference: without -extra=m=8 this gives wipe_pattern_restore_cols's inner loop exactly
        (exts.w r4,r0; mov.b @(r0,r14),r5; ... mov r5,r3; shll r3; add r6,r3; mov r7,r0; @(r0,r5) ...). With the
        tree's -extra=m=8 (shcmdl g_debug_flags 8: simplify_mul keeps x*1) the byte-array index (u32)t*1 is a second
        common-expression temporary with a callee-saved home (one mov more than the arcade). 6 and 7 leave eight
        routines short of the arcade's instructions that 2 gives (Command_Type_00, Check_Limited_Attack,
        Check_After_Attack, Game_Manage_1st, Check_Break_Into_CPU, Check_EM_Speech, effect_work_kill, work_init_zero)
     8, 9  drop only a source variable / only a temporary: 8 is Release 26 and 9 is 2 on every routine of the game */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "imports.h"
int gen_r0var_reserved;

int gen_r0var(void)
{
  static int v = -1;
  if (v < 0) {
    const char *p = getenv("GEN_R0VAR");
    v = (p && *p) ? atoi(p) : 2;
  }
  return v;
}

/* at the start of each statement, after the indexed addresses are counted: 1 to drop the r0 variable */
int gen_r0var_statement(int count, int symx)
{
  int k = gen_r0var(), drop;
  gen_r0var_reserved = 0;
  if (count < 0)
    return 0;
  drop = k == 2 || k == 5 || k == 6 || k == 7 || (k == 8 && symx > 0) || (k == 9 && symx < 0) || ((k == 3 || k == 4) && count < k - 1);
  if (drop && k == 5)
    gen_r0var_reserved = 2;
  if (drop && k == 6)
    gen_r0var_reserved = 1;
  if (drop && k == 7)
    gen_r0var_reserved = 3;
  return drop;
}

/* with r0 held for the statement's indexed addresses (7), a template slot prefers r0 only for the left operand of
   an indexed address (the cast index of src[x], the array of map[t]) */
unsigned short gen_r0var_slot_pref(gen_node *node, unsigned short pref)
{
  gen_node *parent;
  if (gen_r0var_reserved != 3 || !(pref & 1))
    return pref;
  parent = node->parent;
  if (!parent || parent->op != IL_ADD)
    return pref;
  if (parent->child == node && node->next && classify_indexed_address_operands(node, node->next) != 0)
    return pref;
  if (gen_r0var() == 7 && !(parent->parent && parent->parent->op == IL_ASTER))
    return pref;
  return (unsigned short)(pref & ~1);
}
#endif
