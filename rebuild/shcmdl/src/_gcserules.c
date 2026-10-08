/* The arcade's rules for global common-expression elimination, MDL_GCSE (only with SHC_REBUILD_UPDATED=1).

   count_global_expressions numbers the expressions of the whole function into classes (a variable, a memory
   reference or an operator with the same value); cse_eliminate_node gives a class with two or more members one
   temporary, assigned in the common dominator of its members that cse_find_common_block returns, so a value used in
   several blocks is computed once.

   MDL_GCSE=<bits> (unset: 11; 0: Release 26)
     1  no temporary for a global variable in a dominator that is none of the members' blocks when that block uses
        the variable itself: Release 26 appends tmp = variable at the end of such a block and the later uses read
        tmp; the arcade loads the variable again at each use (end_C00_anim, bg_fam0C00).
     4  the same for the other classes (memory references and operators), measured but off: the arcade agrees in
        some routines (sw_pick_up's &wcp[cmd_id] in both arms of an if) and not in others (zoom_ud_check keeps
        &bg_w.bgw[1] in r11), and no shape separates them yet (expressions that read memory against pure addresses
        loses plcnt_b_die and comm_rapp2).
     2  when cse_find_common_block drops the class's first member (a statement later in its own block, the
        dominator's condition, or a path from the dominator changes the value), the class is given up. Release 26
        reinserts the remaining members as a new class and tries again, which moves a load that two switch cases
        make (before any call) up into the switch head (op_bg0_0016's bgw_ptr) and copies a global's address that
        is already in a register (settle_type_00000's pcon_rno). Evidence over the Street Fighter III build
        (10,053 C routines, with rule 8 on): the rule changes the code of 117 routines, none of them among the
        routines that match the arcade without it; 99 come closer to the arcade and 27 match it outright. Taking
        the rule back at one dropped head at a time in those routines makes 90 heads worse and 19 better, the 19
        all in routines that match under neither setting; where one of those was followed up the reinsertion was
        standing in for a source spelling (effect_F1_move, check_5). (When the rule went in, on 10,048 routines
        and sources written against Release 26's behaviour, the same counts were 152 routines, 126 closer, 34
        matching, 117 heads worse and 25 better.)
     8  the other new class Release 26 makes: as cse_find_common_block walks a class's members it takes out each
        one whose value a path from the common dominator changes (a call or a store on the way, for a memory
        reference or a global), keeps the class of those it could reach, and when it has taken out two or more
        it reinserts them as a class of their own, which is tried in turn. The arcade gives them up: only the
        members reached from the first one share a temporary, and every later one computes the expression itself
        (Name_In_Sub: &Rank_In[PL_id] is shared by the test and the argument before the first call and computed
        again at each of the six uses after it, where Release 26 shares it pair by pair; debug_lever_repeat's
        &Debug_Rep_Timer[ix]; sound_driver_tick loads snd_fade_speed in both arms of an if). Rules 2 and 8
        together say that a class is tried once: the arcade never makes a second class out of the members
        the first try left behind. Evidence over the same build: Release 26 makes 579 such classes in 324
        routines; giving them up changes the code of 52 routines, none of them among the 9,092 that match the
        arcade without the rule; 41 come closer by score (44 by the instructions they hold, order aside) and 7
        match outright (Setup_Lever_LR, grade_check_tairyokusa, debug_draw_position_delta, chase_start_check,
        EFF42_SLIDE_IN, init_app_10000, pli_3000). Keeping Release 26's class at one place at a time in those
        routines makes 62 places worse and 9 better, the 9 all in routines that match under neither setting; of
        those read against the listing, three have the arcade's instructions with the rule and lose score to
        instruction order or to a register assignment that moves as a whole (Name_In_Sub, sound_driver_tick,
        effect_F0_move), the others are in routines below 86% (debug_pattern_entry_copy_dual, stngauge_control,
        EFF69_SLIDE_IN, Setup_Command_Name, combo_window_trans, Auto_Repeat_Sub_Wife) and decide nothing.
   MDL_GCSE_LOG=<file> (a diagnostic, off unless set) lists each temporary rules 1 and 4 refuse. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GCSE_DEFAULT 11

static int gcse_bits(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_GCSE");
        k = (v && *v) ? atoi(v) : GCSE_DEFAULT;
    }
    return k;
}

static int same_tree(il_node *a, il_node *b)
{
    il_node *x, *y;
    if (a->op != b->op || a->type != b->type || a->symx != b->symx || a->val != b->val || a->val2 != b->val2)
        return 0;
    for (x = a->child, y = b->child; x && y; x = x->next, y = y->next)
        if (!same_tree(x, y))
            return 0;
    return x == 0 && y == 0;
}

/* tree holds expr: for a variable any use of it, otherwise an equal subtree */
static int tree_computes(il_node *tree, il_node *expr)
{
    il_node *c;
    if (expr->op == IL_ID ? (tree->op == IL_ID && tree->symx == expr->symx) : same_tree(tree, expr))
        return 1;
    for (c = tree->child; c; c = c->next)
        if (tree_computes(c, expr))
            return 1;
    return 0;
}

static void gcse_log(il_node *node, bblock *block)
{
    static FILE *log = (FILE *)1;
    il_node *member;
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_GCSE_LOG");
        log = (p && *p) ? fopen(p, "a") : 0;
    }
    if (!log)
        return;
    fprintf(log, "%s\t%s\tB%d\t", g_symtab[g_func_node->symx].name,
            node->op == IL_ID ? g_symtab[node->symx].name : "-", block->number);
    for (member = node; member != 0; member = member->cse_next)
        fprintf(log, "B%d/L%d ", member->cse_block ? member->cse_block->number : -1, member->line);
    fputc('\n', log);
    fflush(log);
}

/* may the class headed by node take its temporary in block? */
int mdl_gcse_block_ok(il_node *node, bblock *block)
{
    il_node *member;
    node_list *item;
    if (!(gcse_bits() & (node->op == IL_ID ? 1 : 4)))
        return 1;
    for (member = node; member != 0; member = member->cse_next)
        if (member->cse_block == block)
            return 1;
    for (item = block->ilnode; item != 0; item = item->next)
        if (tree_computes(item->node, node)) {
            gcse_log(node, block);
            return 0;
        }
    return 1;
}

/* diagnostics for rule 2: MDL_GCSE2_LOG=<file> lists each dropped class head (function, event number in the
   function, whether Release 26's reinsertion was kept, operator, type, symbol, the head's block and line, the
   members left);
   MDL_GCSE2_EXC=<file> holds "function event" lines at which Release 26's reinsertion is kept. */
static int gcse2_event(il_node *rest, il_node *head)
{
    static FILE *log = (FILE *)1;
    static char *exc = (char *)1;
    static il_node *func;
    static int count;
    const char *name = g_symtab[g_func_node->symx].name;
    il_node *member;
    int keep = 0;
    if (func != g_func_node) {
        func = g_func_node;
        count = 0;
    }
    count++;
    if (exc == (char *)1) {
        const char *p = getenv("MDL_GCSE2_EXC");
        FILE *f = (p && *p) ? fopen(p, "r") : 0;
        exc = 0;
        if (f) {
            long n;
            exc = malloc(1 << 20);
            n = (long)fread(exc + 1, 1, (1 << 20) - 3, f);
            exc[0] = '\n';
            exc[n + 1] = '\n';
            exc[n + 2] = 0;
            fclose(f);
        }
    }
    if (exc) {
        char key[300];
        sprintf(key, "\n%.200s %d\n", name, count);
        keep = strstr(exc, key) != 0;
    }
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_GCSE2_LOG");
        log = (p && *p) ? fopen(p, "a") : 0;
    }
    if (log) {
        fprintf(log, "%s\t%d\t%d\t%d\t0x%x\t%s\tB%d/L%d\t%d\t", name, count, keep, (int)head->op, (unsigned)head->type,
                head->op == IL_ID && head->symx > 0 ? g_symtab[head->symx].name : "-",
                head->cse_block ? head->cse_block->number : -1, head->line, rest ? rest->refcnt : 0);
        for (member = rest; member != 0; member = member->cse_next)
            fprintf(log, "B%d/L%d ", member->cse_block ? member->cse_block->number : -1, member->line);
        fputc('\n', log);
        fflush(log);
    }
    return keep;
}

/* the members left after cse_drop_class_head */
void mdl_gcse_reinsert(il_node *rest, il_node *head)
{
    il_node *member, *next;
    if (!(gcse_bits() & 2) || gcse2_event(rest, head)) {
        cse_reinsert_class(rest);
        return;
    }
    for (member = rest; member != 0; member = next) {
        next = member->cse_next;
        member->cse_next = 0;
        member->cse_head = 0;
        member->refcnt = 0;
    }
}

/* diagnostics for rule 8, as for rule 2: MDL_GCSE8_LOG=<file> lists each set of members taken out of a class
   (function, event number in the function, whether Release 26's new class was kept, operator, type, symbol, the
   members); MDL_GCSE8_EXC=<file> holds "function event" lines at which Release 26's new class is kept. */
static int gcse8_event(il_node *head)
{
    static FILE *log = (FILE *)1;
    static char *exc = (char *)1;
    static il_node *func;
    static int count;
    const char *name = g_symtab[g_func_node->symx].name;
    il_node *member;
    int keep = 0;
    if (func != g_func_node) {
        func = g_func_node;
        count = 0;
    }
    count++;
    if (exc == (char *)1) {
        const char *p = getenv("MDL_GCSE8_EXC");
        FILE *f = (p && *p) ? fopen(p, "r") : 0;
        exc = 0;
        if (f) {
            long n;
            exc = malloc(1 << 20);
            n = (long)fread(exc + 1, 1, (1 << 20) - 3, f);
            exc[0] = '\n';
            exc[n + 1] = '\n';
            exc[n + 2] = 0;
            fclose(f);
        }
    }
    if (exc) {
        char key[300];
        sprintf(key, "\n%.200s %d\n", name, count);
        keep = strstr(exc, key) != 0;
    }
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_GCSE8_LOG");
        log = (p && *p) ? fopen(p, "a") : 0;
    }
    if (log) {
        fprintf(log, "%s\t%d\t%d\t%d\t0x%x\t%s\t%d\t", name, count, keep, (int)head->op, (unsigned)head->type,
                head->op == IL_ID && head->symx > 0 ? g_symtab[head->symx].name : "-", head->refcnt);
        for (member = head; member != 0; member = member->cse_next)
            fprintf(log, "B%d/L%d ", member->cse_block ? member->cse_block->number : -1, member->line);
        fputc('\n', log);
        fflush(log);
    }
    return keep;
}

/* the members cse_find_common_block took out of a class because a path from the dominator changes their value (two
   or more of them, chained from head) */
void mdl_gcse_split(il_node *head)
{
    il_node *member, *next;
    if (!(gcse_bits() & 8) || gcse8_event(head)) {
        cse_reinsert_class(head);
        return;
    }
    for (member = head; member != 0; member = next) {
        next = member->cse_next;
        member->cse_next = 0;
        member->cse_head = 0;
        member->refcnt = 0;
    }
}
