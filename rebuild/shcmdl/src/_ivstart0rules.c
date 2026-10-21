/* MDL_IV_START0 (2nd Impact; only with SHC_REBUILD_UPDATED=1): a reduced induction temporary that starts at
   `0 + p` starts at p.

   Strength reduction gives a derived induction expression `p[i]` (p a pointer variable, i counting from 0) a
   temporary whose start value it assigns before the loop (an assignment flagged 0x4000) as the expression with
   i replaced by its start: `tmp = 0 + p`. Release 26 keeps the zero, so shcgen loads it and adds p
   (mov #0,r4 ... add r10,r4). The 2nd Impact compiler copies p (mov r10,r4; EffE0 effect_E0_init, the
   `cand[i] + 16` read of `cand = (s8*)EM_Candidate[Player_id]`).

   The rule runs after induction-variable optimisation and before global expression counting. It folds such a
   start, a pointer-typed sum of the constant 0 and a variable, into the variable.

   MDL_IV_START0=<n> (unset or 0: Release 26):
     1  every such start
     2  not when the variable is a parameter (sclass 7/8). With 1, EFFB6 effB6_pos_data_set changes: there the start
        is `0 + tbl` with tbl a K&R parameter (the source of a block move), and 2i keeps the zero.
     4  not when the variable is assigned more than once in the function (an outer-loop pointer such as
        sc_trans tilemap_clear_rect's `line`, set before the loops and stepped by `line += 0x80`, where 2i keeps
        the zero: mov #0,r4 ... add r12,r4). Found by the lead when sc_trans landed (2026-10-21).
   6 is the 2nd Impact setting (2 was, before sc_trans was C). Measured on the 2nd Impact build: byte-identical
   with 6; effect_E0_init's first loop and tilemap_clear_rect are exact.
   Found by si2fields (probe in tmp/si2fields_sh5); made a rule by si2core. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))

static int iv_start0_mode(void)
{
    static int mode = -1;
    if (mode < 0) {
        const char *p = getenv("MDL_IV_START0");
        mode = (p && *p) ? atoi(p) : 0;
    }
    return mode;
}

/* rule 4: how many times the function assigns symbol symx (=, += and -=) */
static int count_assigns(il_node *n, short symx)
{
    il_node *c;
    int k = 0;
    if (n == 0)
        return 0;
    if ((n->op == IL_ASSIGN || n->op == IL_A_ADD || n->op == IL_A_SUB) && n->child != 0 && n->child->op == IL_ID
        && n->child->symx == symx)
        k = 1;
    for (c = n->child; c != 0; c = c->next)
        k += count_assigns(c, symx);
    return k;
}

static void fold_walk(il_node *n, int mode)
{
    il_node *c, *next, *rhs, *a, *b, *keep;
    for (c = n->child; c != 0; c = next) {
        next = c->next;
        fold_walk(c, mode);
    }
    if (n->op != IL_ASSIGN || !(n->flag & 0x4000) || n->child == 0 || n->child->op != IL_ID || n->child->symx >= 0)
        return;
    rhs = n->child->next;
    if (rhs == 0 || rhs->op != IL_ADD || (rhs->type & 0xf8) != 0x40 || rhs->child == 0 || rhs->child->next == 0)
        return;
    a = rhs->child;
    b = a->next;
    keep = 0;
    if (a->op == IL_CONST && a->val == 0 && b->op == IL_ID)
        keep = b;
    else if (b->op == IL_CONST && b->val == 0 && a->op == IL_ID)
        keep = a;
    if (keep != 0 && (mode & 2) && keep->symx > 0
        && (g_symtab[keep->symx].sclass == 7 || g_symtab[keep->symx].sclass == 8))
        keep = 0;
    if (keep != 0 && (mode & 4) && count_assigns(g_func_node, keep->symx) > 1)
        keep = 0;
    if (keep != 0) {
        rhs->child = 0;
        keep->next = 0;
        replace_node(rhs, keep);
    }
}

void mdl_iv_start0(void)
{
    int mode = iv_start0_mode();
    if (mode != 0 && g_func_node != 0)
        fold_walk(g_func_node, mode);
}
#else
void mdl_iv_start0(void) {}
#endif
