/* The arcade's rules for global common-expression elimination, MDL_GCSE (only with SHC_REBUILD_UPDATED=1).

   count_global_expressions numbers the expressions of the whole function into classes (a variable, a memory
   reference or an operator with the same value); cse_eliminate_node gives a class with two or more members one
   temporary, assigned in the common dominator of its members that cse_find_common_block returns, so a value used in
   several blocks is computed once.

   MDL_GCSE=<bits> (unset: 1; 0: Release 26)
     1  no temporary for a global variable in a dominator that is none of the members' blocks when that block uses
        the variable itself: Release 26 appends tmp = variable at the end of such a block and the later uses read
        tmp; the arcade loads the variable again at each use (end_C00_anim, bg_fam0C00).
     4  the same for the other classes (memory references and operators), measured but off: the arcade agrees in
        some routines (sw_pick_up's &wcp[cmd_id] in both arms of an if) and not in others (zoom_ud_check keeps
        &bg_w.bgw[1] in r11), and no shape separates them yet (expressions that read memory against pure addresses
        loses plcnt_b_die and comm_rapp2).
     2  when cse_find_common_block drops the class's first member (a statement in its own block, the dominator's
        condition, or a path from the dominator kills it), the class is given up. Release 26 reinserts the remaining
        members as a new class and tries again, which moves a load that two switch cases make (before any call) up
        into the switch head (op_bg0_0016's bgw_ptr). Measured right (aligned routines +18 -1 at 100%, weighted
        +0.28) but off: it moves replays 3522.7 and 8750.7 through voice_process_primary, whose code is still far
        from the arcade's and then runs 20 instructions cheaper per frame than the arcade's.
   MDL_GCSE_LOG=<file> (a diagnostic, off unless set) lists each temporary rules 1 and 4 refuse. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>

#define GCSE_DEFAULT 1

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

/* the members left after cse_drop_class_head */
void mdl_gcse_reinsert(il_node *rest)
{
    il_node *member, *next;
    if (!(gcse_bits() & 2)) {
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
