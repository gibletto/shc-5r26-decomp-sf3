/* GEN_STORE_RHS_INDEX (2nd Impact; only with SHC_REBUILD_UPDATED=1): a store through a sum of two registers is
   left to the add template when its right side reads through an indexed sum that has to be computed.

   fold_address_add turns the store address `*(a + b)` (a and b in registers other than r0) into @(r0,Rn) at once
   (case 7), copying b into r0 before the right side is generated. When the right side reads memory through a sum
   one of whose operands is an expression still to be computed (a table row from a lookup), that expression can no
   longer be made in r0, so Release 26 gives the read an add template and keeps the store indexed:

       mov r1,r0 / ... (row in r3) / add r1,r3 / mov.b @r3,r2 / mov.b r2,@(r0,r7)

   The 2nd Impact compiler has the read indexed and the store address computed before it (EM_Cand
   Initialize_EM_Candidate, EM_Candidate[PL_id][ix] = EM_Candidate_Data[My_char[PL_id]][set][ix]):

       mov r7,r3 / add r1,r3 / mov.b @r13,r0 ... (row in r0) / mov.b @(r0,r1),r2 / mov.b r2,@r3

   With the rule the store's case 7 returns to the add template when the right side has such a read, the sum shares
   a variable (or a cast of one) with the store's address, and one of the read's operands is not a plain variable.
   Where both operands of the read are variables already in registers, the read takes r0 by case 7 as well and
   resolve_operand_register_conflicts moves the store address afterwards, as Release 26 does (EFFECT
   write_my_shell_ix: mov r1,r3 / add r6,r3 ... mov r1,r0 / mov.w @(r0,r7),r2 / mov.w r2,@r3); the rule leaves those
   alone. Measured on the 2nd Impact build (private full tree): byte-identical with the rule on; without the
   shared-variable and computed-operand conditions it changes write_my_shell_ix.

   Only reads count: the target of a store nested in the right side is written, so the search looks at a nested
   assignment's value alone (aboutspr init_char_gfx_tables, `hitmark_gfx_ofs[0][i] = hitmark_gfx_ofs[1][i] = 0;`,
   keeps the indexed store, as 2nd Impact does; si2core).

   GEN_STORE_RHS_INDEX=<n> (unset or 0: Release 26; 1: the rule). */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "imports.h"
#include "gen_rules.h"

static int store_rhs_index_mode(void)
{
    static int mode = -1;
    if (mode < 0) {
        const char *p = getenv("GEN_STORE_RHS_INDEX");
        mode = (p && *p) ? atoi(p) : 0;
    }
    return mode;
}

static int has_id(gen_node *n, short symx)
{
    gen_node *c;
    if (!n)
        return 0;
    if (n->op == IL_ID && n->symx == symx)
        return 1;
    for (c = n->child; c; c = c->next)
        if (has_id(c, symx))
            return 1;
    return 0;
}

/* a variable of tree a occurs in tree b */
static int shares_id(gen_node *a, gen_node *b)
{
    gen_node *c;
    if (!a)
        return 0;
    if (a->op == IL_ID && has_id(b, a->symx))
        return 1;
    for (c = a->child; c; c = c->next)
        if (shares_id(c, b))
            return 1;
    return 0;
}

/* a variable, or a cast of one: a value already in a register when the sum is folded */
static int is_leaf(gen_node *x)
{
    return x->op == IL_ID || (x->op == IL_CAST && x->child && x->child->op == IL_ID);
}

/* the right side reads through a sum of two non-constant operands, not both of them variables, which shares a
   variable with the store's address */
static int computed_indexed_read(gen_node *n, gen_node *addr)
{
    gen_node *c, *a, *b;
    if (!n)
        return 0;
    if (n->op == IL_ASTER && (a = n->child) != 0 && a->op == IL_ADD && (b = a->child) != 0 && b->next != 0 &&
        b->op != IL_CONST && b->next->op != IL_CONST && !(is_leaf(b) && is_leaf(b->next)) && shares_id(a, addr))
        return 1;
    if (n->op == IL_ASSIGN && n->child)  /* a nested store: its target is written, not read */
        return computed_indexed_read(n->child->next, addr);
    for (c = n->child; c; c = c->next)
        if (computed_indexed_read(c, addr))
            return 1;
    return 0;
}

/* fold_address_add case 7 under a store: 1 leaves the store address to the add template */
int gen_store_rhs_index(gen_node *node, gen_node *assign)
{
    if (!store_rhs_index_mode() || assign->op != IL_ASSIGN || !assign->child)
        return 0;
    return computed_indexed_read(assign->child->next, node);
}
#endif
