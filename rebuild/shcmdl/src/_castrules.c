/* Two arcade rules for casts and call arguments (only with SHC_REBUILD_UPDATED=1).

   MDL_CAST_CSE=<bits> (unset: 7, the arcade rule; 0: Release 26). A cast of an array name to an integer
   ((u32)table) is handled as the arcade compiler handles the same cast of an address ((u32)&x): the address is
   loaded at each use.
     1  the common-expression rewriters (cse_replace_with_temporary, common_expression_to_temp) give no temporary
        to a cast that does not widen its operand (node_type_rank of the cast <= the operand's). An array has no
        rank there (0), so Release 26 takes (u32)table as widening and keeps tmp = (u32)table across calls in a
        stack slot or a callee-saved register. Here the array ranks as a pointer (3).
     2  the array name under such a cast is no register-variable candidate (hash_common_expression_candidate).
     4  only casts to an integer type. A pointer cast ((u8 *)table) stays an address, and the arcade keeps it in
        a register as Release 26 does.
   MDL_ARG_CAST=<bits> (unset: 6, the arcade rule; 0: Release 26). lreg_conflicts_with_call lets a variable keep its
   argument register across a call only when the call takes the variable itself as that argument.
     2  an argument written &p->m, m at offset 0 (which is p), counts as p: f(&p->first) no longer sends p to a
        callee-saved register;
     4  with 2, only for a declared variable, not a compiler temporary. */
#include "decls.h"
#include <stdlib.h>

#define CAST_CSE_DEFAULT 7
#define ARG_CAST_DEFAULT 6

static int setting(const char *name, int dflt)
{
    const char *v = getenv(name);
    return v ? atoi(v) : dflt;
}

static int cast_cse(void)
{
    static int k = -1;
    if (k < 0)
        k = setting("MDL_CAST_CSE", CAST_CSE_DEFAULT);
    return k;
}

/* the rank of a cast's operand: an array ranks as a pointer when the cast makes an integer of it */
int mdl_cast_operand_rank(il_node *operand)
{
    int k = cast_cse();
    if ((k & 1) && (operand->type & 0xe0) == 0x80 && (!(k & 4) || (operand->parent->type & 0xe0) == 0))
        return 3;
    return node_type_rank(operand);
}

/* an array name made an integer by a cast is no register-variable candidate */
int mdl_cast_address_leaf(il_node *node)
{
    int k = cast_cse();
    il_node *p = node->parent;
    return (k & 2) && node->op == IL_ID && p != 0 && p->op == IL_CAST && (node->type & 0xe0) == 0x80 &&
           (!(k & 4) || (p->type & 0xe0) == 0);
}

/* the variable a call argument passes: &p->m with m at offset 0 is p */
il_node *mdl_arg_as_variable(il_node *arg)
{
    static int k = -1;
    il_node *q, *a, *v;
    if (k < 0)
        k = setting("MDL_ARG_CAST", ARG_CAST_DEFAULT);
    if ((k & 2) && arg->op == IL_AMPER && (q = arg->child) != 0 && q->op == IL_QUALIFY && q->val2 == 0 &&
        (a = q->child) != 0 && a->op == IL_ASTER && (v = a->child) != 0 && v->op == IL_ID && (!(k & 4) || v->symx > 0))
        return v;
    return arg;
}
