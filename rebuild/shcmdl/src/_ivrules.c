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

   MDL_IV_TEMP=<bits> (unset: 117, the arcade rule; 0: Release 26). An expression used more than once in a loop
   body is computed into a temporary at its first use (t = expr). When expr is derived from an induction
   variable, Release 26's reduce_induction_variable makes t itself the stepping variable: t is set before the
   loop and stepped with the variable, and the assignment in the body goes away. The arcade's compiler does
   that only for an address that is used again by another argument of the same call or in the same test, and
   for an address that a later statement uses when the variable counts down; otherwise it steps a new
   temporary and the body keeps t = new, a register copy on each pass (the first use reads the new one, later
   uses t).
     1  expr is an integer (a scaled index, i * size)
     2  expr is an address and t's next reference is in the same statement (off: the arcade steps t when the
        statement is a call that takes the address twice in its arguments, or a test)
     4  expr is an address and t's next reference is in another statement
     8  expr is an address and t has no other reference
    32  bit 1 also when the variable steps by -1 (Release 26's code takes that case apart from the others)
    64  expr is an address and t's next reference is in the same statement, which is an assignment
        (a[j + 1] = a[j] for structures; x[i].m = f ^ x[i].n): whatever the step
   128  bits 2 to 8 also when the variable steps by -1 (off: the arcade steps t when a later statement uses the
        address of a variable that counts down)
    16  expr is a product by 1 (t = (long)i * 1, the index of a char array, which MDL_CAST_MUL keeps in a
        temporary): it is not reduced at all, t is computed from i on each pass and i stays the counter
        (Release 26 steps t beside i)
   MDL_IV_TEMP_LOG=<file> (a %d in the name is replaced by the process id) lists each such place: function,
   line, class, the variable's step, whether the next reference is in another statement, the number of
   references, the operators above the assignment and at the statement's root, the expression's type and
   operator, whether the rule applied, where each later reference is (S the statement of t = expr, p the
   statement of the reference before it, D another), and the number of the place within its function.
   MDL_IV_TEMP_FORCE="fn:n=v,fn:n=v" (diagnostic) answers v (1 a new temporary, 0 Release 26) at place n of
   function fn, whatever the bits say; tools use it to ask which answer the arcade gave at one place. */
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

#define IV_TEMP_DEFAULT 117

#undef g_iv_update_stmt
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))

/* reduce_induction_variable has met a derived expression that is already the value of an assignment to a
   compiler temporary (t = expr, made when the expression is used more than once). Does it step t itself, as
   Release 26 always does (1), or a new temporary, leaving t = new in the loop (0)? */
/* MDL_IV_TEMP_FORCE: the answer forced at place n of function fn, or -1 */
static int iv_force(const char *fn, int n)
{
    const char *v = getenv("MDL_IV_TEMP_FORCE");
    while (v && *v) {
        int k = 0;
        while (fn[k] && v[k] == fn[k])
            k++;
        if (!fn[k] && v[k] == ':' && atoi(v + k + 1) == n) {
            const char *e = v + k + 1;
            while (*e && *e != '=' && *e != ',')
                e++;
            if (*e == '=')
                return atoi(e + 1);
        }
        while (*v && *v != ',')
            v++;
        if (*v == ',')
            v++;
    }
    return -1;
}

int mdl_iv_reuse_temp(il_node *assign)
{
    static int k = -1;
    static FILE *f;
    static int opened;
    static int lastfn = -1, ord;
    int forced;
    il_node *expr = assign->child->next;
    il_node *ref = assign->refchn;
    il_node *other;
    int ptr = ((expr->type & 0xe0) == 0x80) || ((expr->type & 0xf8) == 0x40);
    int away = 0;      /* the temporary's next reference is in another statement */
    int cls;
    int step;
    int on;
    int asg = 0;       /* ... and it is in the statement that holds t = expr, an assignment */
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
    if (ptr && ref && !away) {
        il_node *root = expression_root(assign);
        asg = expression_root(ref) == root && ((unsigned char)root->op & 0xf0) == 0x50;
    }
    if (asg)
        on = (k & 66) != 0;
    else if (step != -1)
        on = (k & cls) != 0;
    else if (cls == 1)
        on = (k & 1) && (k & 32);
    else
        on = (k & cls) && (k & 128);
    if (lastfn != g_func_node->symx) {
        lastfn = g_func_node->symx;
        ord = 0;
    }
    forced = iv_force(g_symtab[g_func_node->symx].name, ord);
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
        char pat[104];
        il_node *aroot = expression_root(assign), *prev = aroot;
        for (other = assign->refchn; other && nref < 99; other = other->refchn) {
            il_node *r = expression_root(other);
            pat[nref] = r == aroot ? 'S' : r == prev ? 'p' : 'D';
            prev = r;
            nref++;
        }
        pat[nref] = 0;
        fprintf(f, "%s\tord=%d\tline=%u\tcls=%d\tptr=%d\tstep=%d\taway=%d\tnref=%d\tparent=%02x\troot=%02x\ttype=%02x\top=%02x\ttaken=%d\tpat=%s\trootline=%u\n",
                g_symtab[g_func_node->symx].name, ord, (unsigned)expr->line, cls, ptr,
                step, away, nref, (unsigned)(unsigned char)assign->parent->op,
                (unsigned)(unsigned char)expression_root(assign)->op, (unsigned)expr->type,
                (unsigned)(unsigned char)expr->op, on, pat, (unsigned)aroot->line);
        fflush(f);
    }
    ord++;
    if (forced >= 0)
        return forced ? 0 : 1;
    return on ? 0 : 1;
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

/* MDL_TEST_REPLACE=<bits> (unset: 13, the arcade rule; 0: Release 26).

   reduce_induction_variable ends by rewriting the loop's test: when every use of the counter has become a stepped
   temporary (at most three) and the test reads the counter, the test compares one of the temporaries with the
   limit scaled the same way and the counter goes away (replace_loop_test; for (i = 0; i < 8; i++) over
   task_tbl[i] becomes a pointer that stops at task_tbl + 8, `mov.w #H'200,r14`, `add r7,r14` before the loop and
   `cmp/hs r14,r4` in it). Release 26 holds that code behind a flag (g_test_replace_ok) that only bit 0 of the
   option record raises, which no command-line option sets, so it never runs: the counter stays beside the
   stepped pointers (`add #1,r14`, `cmp/hs r13,r14`). The arcade's compiler runs it:
     1  the flag is raised before each induction variable, as that option bit does
     4  only an address may take the test over (use size 8), never an integer multiple of the counter: with a
        member array reached through a pointer the arcade keeps the counter beside the stepped index
        (clear_my_shell_ix, erase_my_shell_ix, write_my_shell_ix, setup_shell_hit_stop: i * 2 steps, `cmp/ge` on i)
     8  only when the test reads the counter itself and it is as wide as an address (an int or long variable): a
        short or char counter is widened for the test and wraps where the address would not
   Evidence over the Street Fighter III build (every C routine, MDL_TEST_LOG): with 13 the test is rewritten in
   task_sleep_tick (the arcade's code exactly, 70 instructions) and kill_tasks_by_func (the arcade's
   `cmp/hs r12,r5` on the stepped pointer); in no routine does the arcade keep a counter the rule removes. The
   other loops it reaches are int counters in our source where the arcade's counter is 16-bit (`exts.w` before the
   compare: Check_Same_CPU, set_char_move_init2, debug_hit_judgment_init, debug_menu_work_init, K5_main_process),
   which a short counter in the source takes out of the rule's reach.
   MDL_TEST_LOG=<file> (a diagnostic, off unless set) lists each stepped temporary the rule is asked about:
   function, use size, the test's operand size, operator and type, the flag, and the answer. */
#define TEST_REPLACE_DEFAULT 13

static int test_replace_bits(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_TEST_REPLACE");
        k = (v && *v) ? atoi(v) : TEST_REPLACE_DEFAULT;
    }
    return k;
}

/* strength_reduce_induction_vars asks before each induction variable: is the flag raised (bit 1)? */
int mdl_iv_test_replace(void)
{
    return test_replace_bits() & 1;
}

static void test_log(unsigned int use_size, int test_size, int verdict)
{
    static FILE *f;
    static int tried;
    il_node *test = *(il_node **)(g_sd + 0x26854);
    if (!tried) {
        const char *p = getenv("MDL_TEST_LOG");
        tried = 1;
        if (p && *p)
            f = fopen(p, "a");
    }
    if (f) {
        fprintf(f, "%s use=%u test=%d lhs_op=%d lhs_type=%x op=%d ok=%d reduced=%d -> %d\n",
                g_symtab[g_func_node->symx].name, use_size, test_size, test ? (int)test->child->op : -1,
                test ? (unsigned)test->child->type : 0, test ? (int)test->op : -1, g_test_replace_ok,
                g_iv_reduced_count, verdict);
        fflush(f);
    }
}

/* reduce_induction_variable asks for each stepped temporary the type table allows: may it take over the loop's
   test (bits 4 and 8)? */
int mdl_iv_test_use(unsigned int use_size, int test_size)
{
    int k = test_replace_bits(), v = 1;
    il_node *test = *(il_node **)(g_sd + 0x26854);
    if (!(k & 1))
        return 1;
    if ((k & 4) && use_size != 8)
        v = 0;
    if ((k & 8) && (test_size < 4 || test_size > 7 || !test || test->child->op != IL_ID))
        v = 0;
    test_log(use_size, test_size, v);
    return v;
}
