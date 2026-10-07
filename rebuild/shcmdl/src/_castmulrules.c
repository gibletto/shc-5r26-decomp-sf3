/* The arcade's rule for the index of a char array that is a char or short variable, MDL_CAST_MUL (only with
   SHC_REBUILD_UPDATED=1).

   An index is scaled by the element size in the tree, also when the size is 1: table[ix] with a short ix is
   *(table + (long)ix * 1), and shcmdl never folds the product. Global common-expression elimination
   (count_global_expressions) numbers the expressions of the function into classes and cse_eliminate_node gives a
   class with two or more members a temporary. cse_replace_with_temp makes an exception for (long)ix: a member
   that is the operand of a multiplication takes no temporary (muls.w extends its operands itself), and when the
   class's first member is such an operand the whole class is left alone. Every index cast is the operand of a
   multiplication, so the cast's class never gets a temporary - but the products by 1 are a class of their own,
   and Release 26 gives that one a temporary: tmp = (long)ix * 1, which is the extension it has just refused to
   keep. The arcade does not, when the cast's class was refused because its first member is scaled by more than 1:
   it extends ix again at each use (game_config_lever_repeat: Config_Rep_Timer[ix], a short array, then
   Config_Rep_Count[ix], a char array, in three blocks).

   MDL_CAST_MUL=<bits> (unset: 1; 0: Release 26)
     1  no temporary for the class of (long)v * 1, v a char or short variable, when the first member of the class
        of (long)v is the operand of a multiplication by something other than 1.
     2  the same when the first member is not, but another member is. Measured and off.
     4  the same when no member is (v only indexes char arrays, or is also used outside an index). Measured and
        off: here the arcade keeps the temporary as Release 26 does (Select_Combo_Speed, Sel_CPU_Sub,
        Request_Break_Sub, effl2_dir_check match with it).
     8  the same for a product by 1 of anything else (an int index: tmp = i * 1 is a copy of i). Measured and
        off: the arcade makes the copy (appear_data_init_set).
   Evidence over the Street Fighter III build (10,048 C routines), counting the routines in which the class
   arises and the number of sign and zero extensions in the arcade's code against ours with the bit off and on:
     1  11 routines; in 7 the arcade's count is nearer with the bit on, in none nearer with it off, in 4 the code
        does not change (the class's parent has as many members and takes the temporary itself);
     2  7 routines; 2 nearer on, 3 nearer off, 2 unchanged;
     4  39 routines; 3 nearer on, 15 nearer off, 21 unchanged;
     8  10 routines by match percentage: 1 better, 4 worse (one of them a routine that matches), 5 unchanged.
   What the arcade compiler does inside is not known; the rule is the condition that separates its decisions.
   MDL_CAST_MUL_LOG=<file> (a diagnostic, off unless set) lists each such class with the bit it falls under. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>

#define CAST_MUL_DEFAULT 1

static int castmul_bits(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_CAST_MUL");
        k = (v && *v) ? atoi(v) : CAST_MUL_DEFAULT;
    }
    return k;
}

/* an integer cast of a char or short variable: the casts cse_replace_with_temp leaves alone under a multiplication */
static int narrow_cast(il_node *n)
{
    return n != 0 && n->op == IL_CAST && (n->type & 0xe0) == 0 && n->child != 0 && n->child->op == IL_ID &&
           ((n->child->type & 0xf8) == 8 || (n->child->type & 0xf8) == 0);
}

static int const_one(il_node *n)
{
    return n != 0 && n->op == IL_CONST && n->val == 1;
}

/* the operand of a multiplication by something other than 1 */
static int scaled(il_node *n)
{
    il_node *p = n->parent;
    return p != 0 && (p->op == IL_MUL || p->op == IL_A_MUL) && !const_one(n->next);
}

/* The heads of the classes of such casts, noted as the elimination walk reaches them: the walk takes the blocks
   in the order the numbering did, so a class's head comes before its other members and before any product that
   holds one of them, while its own tree is still as numbered (later the tree may have been replaced). */
static struct seen_head {
    il_node *head;
    int head_scaled;     /* the head is the operand of a multiplication by something other than 1 */
    int others_scaled;   /* how many other members are */
} *seen;
static int seen_count, seen_size;

void mdl_castmul_begin(void)
{
    seen_count = 0;
}

void mdl_castmul_visit(il_node *node)
{
    il_node *member;
    if (!narrow_cast(node) || node->cse_head != node)
        return;
    if (seen_count == seen_size) {
        seen_size = seen_size ? seen_size * 2 : 64;
        seen = realloc(seen, seen_size * sizeof *seen);
        if (seen == 0)
            exit(1);
    }
    seen[seen_count].head = node;
    seen[seen_count].head_scaled = scaled(node);
    seen[seen_count].others_scaled = 0;
    for (member = node->cse_next; member != 0; member = member->cse_next)
        if (narrow_cast(member) && scaled(member))
            seen[seen_count].others_scaled++;
    seen_count++;
}

static void castmul_log(il_node *node, bblock *block, int bit)
{
    static FILE *log = (FILE *)1;
    il_node *member, *v = node->child->op == IL_CAST ? node->child->child : node->child;
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_CAST_MUL_LOG");
        log = (p && *p) ? fopen(p, "a") : 0;
    }
    if (!log)
        return;
    fprintf(log, "%s\t%d\t%s\t%d\tB%d\t", g_symtab[g_func_node->symx].name, bit,
            v != 0 && v->op == IL_ID && v->symx > 0 ? g_symtab[v->symx].name : "-", (int)node->refcnt,
            block ? block->number : -1);
    for (member = node; member != 0; member = member->cse_next)
        fprintf(log, "B%d/L%d ", member->cse_block ? member->cse_block->number : -1, member->line);
    fputc('\n', log);
    fflush(log);
}

/* may the class headed by node take its temporary (in block)? */
int mdl_castmul_ok(il_node *node, bblock *block)
{
    il_node *operand, *head;
    int i, bit;
    if (node->op != IL_MUL || (operand = node->child) == 0 || !const_one(operand->next))
        return 1;
    if (!narrow_cast(operand))
        bit = 8;
    else {
        head = operand->cse_head;
        bit = 4;
        for (i = 0; i < seen_count; i++)
            if (seen[i].head == head) {
                bit = seen[i].head_scaled ? 1 : seen[i].others_scaled ? 2 : 4;
                break;
            }
    }
    castmul_log(node, block, bit);
    return !(castmul_bits() & bit);
}
