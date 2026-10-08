/* Induction-variable rules (only with SHC_REBUILD_UPDATED=1).

   MDL_IV=<bits> (unset: 3, the arcade rule; 0: Release 26).
     1  scan_derived_induction_expr: a cast that narrows an induction variable keeps the variable's number, so
        (char)(i * 6) derives from i like i * 6 does (Release 26 drops the number at any narrowing cast).
        With 2 only a cast to char, with 4 only a cast to short (both: both).

   MDL_IV_BASE=<bits> (unset: 3, the arcade rule; 0: Release 26). hoist_invariants_in_tree marks what does not
   change in a loop. It runs twice: before the induction variables are found (g_licm_pass 0, marking only) and
   later to move invariant expressions in front of the loop (g_licm_pass 1). Release 26 lets the address of a
   member reached through a pointer (p->a: IL_QUALIFY over IL_ASTER of a struct) count as invariant in the
   first run only, so p->a[i] is a derived induction variable (p + offset + i * size, a pointer that steps by
   the size) although the second run would not move p->a out of the loop. The arcade's compiler answers in the
   first run as in the second: p->a is not invariant, only i * size is reduced, and p + offset is added to it on
   each pass. A static array's address (a[i], a[i][j]) is invariant in both.
     1  IL_QUALIFY and IL_B_QUALIFY: the first run answers as the second
     2  IL_ASTER of a struct: the same

   MDL_IV_TEMP=<bits> (unset: 21, the arcade rule; 0: Release 26). An expression used more than once in a loop
   body is computed into a temporary at its first use (t = expr). When expr is derived from an induction
   variable, Release 26's reduce_induction_variable makes t itself the stepping variable: t is set before the
   loop and stepped with the variable, and the assignment in the body goes away. The arcade's compiler does
   that only for an address that is used again within the same statement; otherwise it steps a new temporary
   and the body keeps t = new, a register copy on each pass (the first use reads the new one, later uses t).
     1  expr is an integer (a scaled index, i * size)
     2  expr is an address and t's next reference is in the same statement (off: the arcade steps t here)
     4  expr is an address and t's next reference is in another statement
     8  expr is an address and t has no other reference
    32  bits 1 to 8 also when the variable steps by -1 (off: Release 26's code takes that case apart from the
        others, and the arcade's sites with such a variable do not decide: 4 for, 5 against)
    16  expr is a product by 1 (t = (long)i * 1, the index of a char array, which MDL_CAST_MUL keeps in a
        temporary): it is not reduced at all, t is computed from i on each pass and i stays the counter
        (Release 26 steps t beside i)
   MDL_IV_TEMP_LOG=<file> (a %d in the name is replaced by the process id) lists each such place: function,
   line, class, the variable's step, whether the next reference is in another statement, the number of
   references, the operators above the assignment and at the statement's root, the expression's type and
   operator, and whether the rule applied. */
#include "decls.h"
#include <stdlib.h>
#include <stdio.h>
#include <process.h>

int mdl_iv_rules(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_IV");
        k = v ? atoi(v) : 3;
    }
    return k;
}

#define IV_BASE_DEFAULT 3

/* the pass number hoist_invariants_in_tree asks at a member (bit 1) or at a struct dereference (bit 2) */
int mdl_iv_licm_pass(int pass, int bit)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_IV_BASE");
        k = v ? atoi(v) : IV_BASE_DEFAULT;
    }
    return (k & bit) ? 1 : pass;
}

#define IV_TEMP_DEFAULT 21

#undef g_iv_update_stmt
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))

/* reduce_induction_variable has met a derived expression that is already the value of an assignment to a
   compiler temporary (t = expr, made when the expression is used more than once). Does it step t itself, as
   Release 26 always does (1), or a new temporary, leaving t = new in the loop (0)? */
int mdl_iv_reuse_temp(il_node *assign)
{
    static int k = -1;
    static FILE *f;
    static int opened;
    il_node *expr = assign->child->next;
    il_node *ref = assign->refchn;
    il_node *other;
    int ptr = ((expr->type & 0xe0) == 0x80) || ((expr->type & 0xf8) == 0x40);
    int away = 0;      /* the temporary's next reference is in another statement */
    int cls;
    int step;
    if (k < 0) {
        const char *v = getenv("MDL_IV_TEMP");
        k = v ? atoi(v) : IV_TEMP_DEFAULT;
    }
    if (ref) {
        other = ref->refchn ? ref->refchn : assign;
        away = expression_root(other) != expression_root(ref);
    }
    cls = !ptr ? 1 : !ref ? 8 : away ? 4 : 2;
    step = induction_step(g_iv_update_stmt);
    if (step == -1 && !(k & 32))
        cls = 0;      /* Release 26 treats a variable that steps by -1 apart here; so does the rule */
    if (!opened) {
        const char *p = getenv("MDL_IV_TEMP_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    if (f) {
        int nref = 0;
        for (other = assign->refchn; other && nref < 99; other = other->refchn)
            nref++;
        fprintf(f, "%s\tline=%u\tcls=%d\tptr=%d\tstep=%d\taway=%d\tnref=%d\tparent=%02x\troot=%02x\ttype=%02x\top=%02x\ttaken=%d\n",
                g_symtab[g_func_node->symx].name, (unsigned)expr->line, cls, ptr,
                step, away, nref, (unsigned)(unsigned char)assign->parent->op,
                (unsigned)(unsigned char)expression_root(assign)->op, (unsigned)expr->type,
                (unsigned)(unsigned char)expr->op, (k & cls) != 0);
        fflush(f);
    }
    return (k & cls) ? 0 : 1;
}

/* reduce_induction_variable asks before it reduces an expression: is it a product by 1 that sits in a temporary
   (bit 16), which is left as it is? */
int mdl_iv_skip_use(il_node *expr)
{
    static int k = -1;
    il_node *a, *b, *p;
    if (k < 0) {
        const char *v = getenv("MDL_IV_TEMP");
        k = v ? atoi(v) : IV_TEMP_DEFAULT;
    }
    if (!(k & 16) || expr->op != IL_MUL)
        return 0;
    p = expr->parent;
    if (p->op != IL_ASSIGN || p->child->op != IL_ID || p->child->symx >= 0)
        return 0;
    a = expr->child;
    b = a->next;
    return (a->op == IL_CONST && a->val == 1) || (b && b->op == IL_CONST && b->val == 1);
}
