/* GEN_OR_LEFT_KEEP (only with SHC_REBUILD_UPDATED=1; unset or 0: Release 26 and the 3rd Strike build): a compiler
   revision's behaviour seen in Street Fighter III 2nd Impact, not in 3rd Strike.

   prepare_comparison_node, for a comparison used as a condition, asks the register chooser for a register even when
   the comparison emits none of its own: `x == K` with K fitting cmp/eq #imm works in r0, so the register it gets
   (r3 when r2/r3 are free, the chooser scanning down) is never used. The chooser still records it as the last
   chosen register, and the next choice ranks that register one worse. In
   `if (ewk->wu.dead_f == 1 || Suicide[0] != 0)` the address of Suicide then goes to r2 and the byte to r3
   (`mov.l =_Suicide,r2; mov.b @r2,r3; tst r3,r3`), as 3rd Strike has it in every such routine. 2nd Impact has the
   same routines with r3 and r2 (`mov.l =_Suicide,r3; mov.b @r3,r2; tst r2,r2`): its compiler did not record that
   pick.

   With the setting, the pick does not become the last chosen register when the comparison is `==` or `!=` against
   a constant of -128..127, it is the left operand of `||`, and the right operand of the `||` is a truth test
   `y != 0` (which the front end gives as NOT of NOT).

   Measured (2026-10-19, si2cc2): in 2nd Impact the eight routines whose only difference was this pick become
   exact (effect_03_move, effect_33_move, effect_D5_move, effect_D6_move, effect_D7_move, effect_E2_move,
   effect_H7_move, effect_H8_move; effect_B1_move and effect_I8_move keep only a source constant), and no other
   function of the 4,769 already matched changes. In 3rd Strike it changes 25 routines of that shape (the arcade
   has Release 26's pick in all of them), so the setting is on for the 2nd Impact build only. Without the right
   operand condition `routine_no[3] == 3 || !hos_fi_flag` (Damage_30000) and `pat_status == 1 || ... == 21`
   (effect_at_vs_player_dm) would change, which 2nd Impact has as Release 26 does.

   GEN_OR_LEFT_KEEP=2 adds the same for the left `==/!= imm8` compare of an `&&` whose right operand is a plain
   read (`if (ewk->wu.routine_no[7] == 7 && Suicide[0])` in 2nd Impact's effect_80_move: =Suicide in r3).
   Measured 2026-10-19: no other function of the 5,939 matched in 2nd Impact changes; a right operand that is a
   compare, a call, another && / || or arithmetic (`routine_no[3] != 4 && (hos_fi_flag | hos_em_flag)` in
   Att_TENSHINSENKYUUTAI) keeps the Release 26 pick. A struct member read keeps it too (`E_Number[0][0] == 2 &&
   name_wk[0].dmm` in 2nd Impact's commit_name_entry_row_both_players, 2026-10-19).

   GEN_OR_LEFT_KEEP=3 adds the `&&` whose right operand is a truth test `y != 0` (written `!= 0`, or NOT of NOT):
   2nd Impact's effect_38_move `if (ewk->wu.direction == 2 && Suicide[0] != 0)` has =Suicide in r3 and the byte in
   r2. Measured 2026-10-20: the 2nd Impact build stays byte-identical (C 6414, no matched function changes). Only
   when the left operand is a member read: sel_pl's Sel_PL_Sub `Cursor_X[PL_id] == 6 && Sel_Command_Off != 0` (an
   array element on the left) keeps the Release 26 pick in 2nd Impact. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "imports.h"
#include "orleftkeep.h"

static int gen_or_left_keep_setting(void)
{
    static int mode = -1;
    if (mode < 0) {
        const char *p = getenv("GEN_OR_LEFT_KEEP");
        mode = (p && *p) ? (int)strtol(p, 0, 0) : 0;
    }
    return mode;
}

/* prepare_comparison_node, a comparison used as a condition, after the chooser picked its register: 1 when the pick
   must not stay the last chosen register */
int gen_or_left_keep(gen_node *node)
{
    gen_node *rhs, *right, *left;
    if (!gen_or_left_keep_setting() || node == 0)
        return 0;
    if (node->op != IL_EQ && node->op != IL_NE)
        return 0;
    rhs = node->child ? node->child->next : 0;
    if (rhs == 0 || rhs->op != IL_CONST || rhs->val < -128 || rhs->val > 127)
        return 0;
    if (node->parent == 0 || node->parent->child != node)
        return 0;
    right = node->next;
    if (node->parent->op == IL_AND) {
        /* setting 2: the same pick in `x == K && y` when y is a plain read (no compare, call, arithmetic or member) */
        if (gen_or_left_keep_setting() >= 2 && right != 0
            && (right->op < IL_CAST || right->op == IL_ASTER || right->op == IL_PRI))
            return 1;
        /* setting 3: also `s->m == K && y != 0` (the left operand a member read; an array element keeps the pick) */
        left = node->child;
        while (left != 0 && left->op == IL_CAST)
            left = left->child;
        return gen_or_left_keep_setting() >= 3 && right != 0 && left != 0
            && (left->op == IL_QUALIFY || left->op == IL_B_QUALIFY)
            && ((right->op == IL_NOT && right->child != 0 && right->child->op == IL_NOT)
                || (right->op == IL_NE && right->child != 0 && right->child->next != 0
                    && right->child->next->op == IL_CONST && right->child->next->val == 0));
    }
    if (node->parent->op != IL_OR)
        return 0;
    return right != 0 && right->op == IL_NOT && right->child != 0 && right->child->op == IL_NOT;
}
#endif
