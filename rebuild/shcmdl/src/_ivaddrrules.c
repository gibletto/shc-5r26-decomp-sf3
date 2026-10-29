/* MDL_IV_ADDR (2nd Impact; only with SHC_REBUILD_UPDATED=1): a reduced induction value keeps an array's address
   out of its temporary.

   scan_derived_induction_expr extends a derived induction expression through every sum of an induction operand
   and a loop invariant, so in `(u8*)((u32)sc_chr_data + (16 * 4 + i * 68 + 0x408) * 32)` the whole sum, the
   table's address included, becomes the stepped temporary: the use is a plain load of the temporary.

   The 2nd Impact compiler steps only the offset (0x8900 + i * 0x880 in a frame slot) and adds the table's address
   at each use, the address first (sc_trans player_name_trans, the two `== 14 || == 15` arms):

       mov.l @(8,r15),r3 / mov.l #sc_chr_data,r2 / add r3,r2 / mov.l r2,@r13

   With the rule, (1) an integer sum whose invariant operand is a cast of an array's address does not extend the derived expression, and (2) after reduce_induction_variable puts the
   temporary in place, a sum of the temporary (or its cast) and such a cast is rebuilt with the address first,
   which is the order the 2i code evaluates. Pointer sums (`My_char[i]`, a dereferenced &table + i) are not
   integer sums and keep Release 26's reduction.

   Measured on the 2nd Impact build (private full tree): byte-identical with the rule on (also with (2) alone);
   sc_trans player_name_trans becomes exact. An address taken with & counted as such a cast too before; the full
   3rd Strike, 2nd Impact and New Generation builds with the rule on are byte-identical without that case
   (2026-10-29).

   MDL_IV_ADDR=<n> (unset or 0: Release 26; 1: the rule). */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "imports.h"
#include "argconst.h"

int mdl_iv_addr(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_IV_ADDR");
        k = (v && *v) ? atoi(v) : 0;
    }
    return k;
}

/* a cast of an array's address */
static int cast_of_address(il_node *n)
{
    return n != 0 && n->op == IL_CAST && n->child != 0 && n->child->op == IL_ID && (n->child->type & 0xe0) == 0x80;
}

/* scan_derived_induction_expr, a sum of an induction operand and the invariant inv: 1 stops the derived expression */
int mdl_iv_addr_stop(il_node *node, il_node *inv)
{
    return mdl_iv_addr() && (node->type & 0xe0) == 0 && cast_of_address(inv);
}

/* reduce_induction_variable after the temporary replaced the derived expression: the address goes first */
void mdl_iv_addr_order(il_node *temp)
{
    il_node *up = temp->parent, *sum, *a, *b;
    if (!mdl_iv_addr())
        return;
    if (up != 0 && up->op == IL_CAST)
        sum = up->parent;
    else {
        sum = up;
        up = temp;
    }
    if (sum != 0 && sum->op == IL_ADD && (a = sum->child) == up && (b = a->next) != 0 && cast_of_address(b)) {
        a->next = b->next;
        b->next = a;
        sum->child = b;
    }
}
#endif
