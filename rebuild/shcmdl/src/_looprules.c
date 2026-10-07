/* Loop inversion rule (only with SHC_REBUILD_UPDATED=1).

   MDL_LOOP_INV=<bits> (unset: 31, the arcade rule; 0: Release 26).
   select_loops_to_invert turns a loop whose trip count is not known into a guarded do-loop
   (for/while -> if (cond) do ... while (cond)). Release 26 asks the -speed option at five places, and with
   -speed it inverts every such loop. A set bit makes that place answer as without -speed, so the loop keeps
   its jump to the test at the bottom:
     1  a loop that contains another loop
     2  the condition is not a comparison
     4  a floating-point comparison
     8  a comparison whose left operand is a local or a constant and whose right operand is not
    16  a comparison whose left operand is not a local or a constant
   A comparison of two locals or constants is inverted with or without -speed.

   MDL_LOOP_LOG=<file> (off unless set; a %d in the name is replaced by the process id): a line per loop
   select_loops_to_invert looks at, with the function, the loop statement's source line and operator, its number,
   nesting count, whether it holds another loop, its trip count (repet) and flags; then, each with the loop's
   number (an outer loop is decided after its inner loops), the places that asked for -speed (ask<bit>@<loop>)
   and inverted@<loop> if the loop was inverted. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>
#include <process.h>

static int mdl_loop_inv(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_LOOP_INV");
        k = v ? atoi(v) : 31;
    }
    return k;
}

static FILE *loop_log(void)
{
    static FILE *f;
    static int opened;
    if (!opened) {
        const char *p = getenv("MDL_LOOP_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    return f;
}

/* the start of a loop's line */
void mdl_loop_log(loop *lp)
{
    FILE *f = loop_log();
    if (f) {
        fprintf(f, "\n%s line=%u op=%d lp=%d nest=%d child=%d repet=%d flag=%x", g_symtab[g_func_node->symx].name,
                (unsigned)lp->node->line, (int)lp->node->op, lp->lpnumber, lp->nestcnt, lp->child != 0, lp->repet,
                lp->flag);
        fflush(f);
    }
}

/* a place of select_loops_to_invert asks whether -speed is on */
int mdl_loop_speed(loop *lp, int speed, int bit)
{
    FILE *f = loop_log();
    if (f) {
        fprintf(f, " ask%d@%d", bit, lp->lpnumber);
        fflush(f);
    }
    return speed != 0 && !(mdl_loop_inv() & bit);
}

void mdl_loop_inverted(loop *lp)
{
    FILE *f = loop_log();
    if (f) {
        fprintf(f, " inverted@%d", lp->lpnumber);
        fflush(f);
    }
}
