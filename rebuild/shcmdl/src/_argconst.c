/* The arcade's argument-constant rule, MDL_ARG_CONST (only with SHC_REBUILD_UPDATED=1).

   The register-variable weight of a common expression (weigh_common_expression_candidates) counts each occurrence of a constant but skips
   one the operator can take as an immediate (is_immediate_operand(parent, operand position, value) != 0). For a call
   argument (parent IL_ARG) an imm8 constant bound for r4..r7 counts as an immediate, so `f(w, -1, 7, 1, -1)` gives the
   -1 weight 1: never >= 3, never hoisted into a callee-saved register. The arcade's compiler hoists such constants,
   as if register-bound arguments counted.

   MDL_ARG_CONST=<hex digit>, a bit mask over the callers of is_immediate_operand (ARGCONST_FIT's group):
     1  the weight counter (weigh_common_expression_candidates)
     2  the rewriters that make the occurrences read the register (materialize_constant_lreg, write_lreg_numbers)
     4  collect_register_candidate
     8  with 1 or 2: keep the stock answer for an occurrence inside a loop (its block has an lptbl)
   A set bit answers 0 ("not an immediate") for a constant whose parent is a call argument. Unset: b (weight and
   rewriters, not in loops: the arcade behaviour); 0: Release 26.
   MDL_ARG_CALL=<hex digit>, the same groups (unset: 0), a diagnostic: narrows the 0 answer to a constant whose call
   also passes the same value in an argument is_immediate_operand does not take as an immediate (a stack argument). */
#include "decls.h"
#include <stdlib.h>

#define ARG_CONST_DEFAULT 0xb

/* the variable's first character as a hex digit ('0'-'9', 'a'-'f'); dflt when unset */
static int knob(const char *name, int dflt)
{
    const char *v = getenv(name);
    unsigned int c;
    if (!v)
        return dflt;
    c = (unsigned char)*v - 0x30;
    if (c > 9)
        c -= 0x27;
    return (int)c;
}

/* the stock answer, or 0 if a sibling argument of the same constant value is not an immediate */
static int call_rule(il_node *parent, int pos, unsigned int value)
{
    int r = is_immediate_operand(parent, pos, value), i = 1;
    il_node *arg;
    if (r == 0)
        return 0;
    for (arg = parent->child; arg != 0; arg = arg->next, i++) {
        if (i != pos && arg->op == IL_CONST && (unsigned int)arg->val == value && is_immediate_operand(parent, i, value) == 0)
            return 0;
    }
    return r;
}

/* occ: the occurrence record ({next, block, node}) of the node being weighed or rewritten, 0 for group 4 */
int mdl_argconst_fit(int group, il_node *parent, int pos, unsigned int value, const_use *occ)
{
    int bits = knob("MDL_ARG_CONST", ARG_CONST_DEFAULT);
    if (!(bits & group) || parent->op != IL_ARG)
        return is_immediate_operand(parent, pos, value);
    if ((bits & 8) && occ && occ->block->lptbl != 0)
        return is_immediate_operand(parent, pos, value);
    if (knob("MDL_ARG_CALL", 0) & group)
        return call_rule(parent, pos, value);
    return 0;
}
