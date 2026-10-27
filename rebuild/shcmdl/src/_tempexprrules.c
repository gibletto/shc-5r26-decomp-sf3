/* The arcade's rule for a common expression that holds a temporary, MDL_TEMP_EXPR (only with
   SHC_REBUILD_UPDATED=1).

   Global common-expression elimination walks each statement tree from the leaves up (cse_global_tree) and gives a
   class of equal expressions one temporary (cse_eliminate_node). Release 26 leaves a tree alone as soon as one of
   its leaves is a temporary (tree_has_temp_id), so when an operand has just been given a temporary the expression
   above it is never shared: with table[ix] used in several blocks and ix used more often than table[ix], the
   scaled index gets the temporary and every use adds the table's address again. The arcade's compiler shares
   both: the index is computed once and the element address once more, in the common dominator of its uses
   (combo_control: cmb_calc_now[PL] stored in both arms of an if, one exts.b and one add in front of the test;
   Sel_PL_Sub_CR/CL/CU/CD: &Cursor_X[PL_id] kept across the cases of a switch beside PL_id * 2;
   combo_window_trans: &cst_read[PL] and cmst_buff[PL] in r9 and r8 beside PL and PL * 112;
   Hi_Jump_Command_Attack_Term: a mask of a converted variable shared by two calls).

   MDL_TEMP_EXPR=<bits> (unset: 1; 0: Release 26)
     1  the head of a class of two or more equal expressions is numbered also when its tree holds a temporary.
        A class one of whose other members assigns a temporary is left alone under every setting: the member's tree
        is thrown away when the class's temporary takes its place.
   (Bit 2, a guard that kept Release 26's answer where the code generator lost the copy of a global's address
   to a temporary (Flash_Please), is retired: no game module needs it once the dead reads of that routine are
   written as the call of an empty display routine, round 52.)
   Evidence over the Street Fighter III build (10,064 C routines, game tree r8-snd-rule 3e739340, the rule off
   against on): the score of 76 routines changes. 54 come closer to the arcade and 17 match it outright
   (Sel_PL_Sub_CR, _CL, _CU, _CD, scr_11_21, scr_12_21, debug_priority_swap, bbbs_com_execute2,
   Hi_Jump_Command_Attack_Term, Win_10000 by their own code; Check_Landed, plcnt_b_move, get_center_position,
   blit_16x16_tile, Sel_PL_4th, q_em_dir, q_leave_after_action through a routine in front of them that takes its
   size). 21 score lower. Eleven of those matched and have the same instructions in another order behind a routine
   that changed size (Game_Manage_5th, _5_0, _5_1, _5_2, Erase_Win_Record, Check_Disp_Winner behind Update_BI_Term,
   Disp_Win_Record and Judge_Winner in manage_2.c; pli_0000, pli_1000 behind init_app_30000; win_mark_pos_set,
   win_mark_new_check behind win_mark_write and win_mark_control; effect_B6_init behind effect_B6_move). The other
   ten did not match before: counting their instructions against the arcade's with registers and order aside,
   check_body_touch2, suzi_line_calc, suzi_line_calc_fill and attack_hit_check are nearer with the rule,
   Disp_Win_Record, win_mark_control and effect_L2_init within three instructions of where they were, Judge_Winner
   further (its source writes &judge_gals[1], which the arcade loads as a constant of its own), and scr_12_22 and
   effect_F0_init only follow a routine in front of them. The differential run (diff_exec, 32 trials a routine)
   over the whole image shows no routine that behaves differently with the rule and five that no longer differ in
   the result register (the four Sel_PL_Sub_C* and stngauge_control).
   MDL_TEMP_EXPR_LOG=<file> (a diagnostic, off unless set) lists each class of two or more members whose tree
   holds a temporary: function, operator, type, source line, members, the parent's operator. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>

#define TEMP_EXPR_DEFAULT 1

static int temp_expr_bits(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_TEMP_EXPR");
        k = (v && *v) ? atoi(v) : TEMP_EXPR_DEFAULT;
    }
    return k;
}

static void temp_expr_log(il_node *node)
{
    static FILE *log = (FILE *)1;
    il_node *member;
    int count = 0;
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_TEMP_EXPR_LOG");
        log = (p && *p) ? fopen(p, "a") : 0;
    }
    if (!log || node->cse_head != node || node->cse_next == 0)
        return;
    for (member = node; member != 0; member = member->cse_next)
        count++;
    fprintf(log, "%s\t%d\t0x%x\tL%d\t%d\t%d\n", g_symtab[g_func_node->symx].name, (int)node->op, (int)node->type,
            (int)node->line, count, node->parent ? (int)node->parent->op : -1);
    fflush(log);
}

/* the tree assigns a temporary: tmp = expr sits where the first use of the expression was */
static int assigns_temp(il_node *n)
{
    il_node *c;
    if (n->op == IL_ASSIGN && n->child != 0 && n->child->op == IL_ID && n->child->symx < 0)
        return 1;
    for (c = n->child; c != 0; c = c->next)
        if (assigns_temp(c))
            return 1;
    return 0;
}

/* cse_global_tree met a tree that holds a temporary. 1: leave it alone (Release 26); 0: number it.
   A member that would be replaced by the class's temporary must not be the place where another temporary is
   assigned (cse_replace_with_temp throws the member's tree away): such a class is left alone under every
   setting. The head keeps its tree, which becomes the right side of the new assignment. */
int mdl_temp_expr_skip(il_node *node)
{
    il_node *member;
    temp_expr_log(node);
    if (!(temp_expr_bits() & 1))
        return 1;
    if (node->cse_head != node || node->cse_next == 0)
        return 1;
    for (member = node->cse_next; member != 0; member = member->cse_next)
        if (assigns_temp(member))
            return 1;
    return 0;
}
