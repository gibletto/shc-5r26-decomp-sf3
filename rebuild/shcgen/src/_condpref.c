/* GEN_COND_PREF (only with SHC_REBUILD_UPDATED=1): an assignment to a register does not hand that register to a
   conditional right side as a preference.

   generate_assign_node, when the destination is a register the right side does not need, sets the right side's
   pref_regs to it (and its dest is that register already, copy_ea_into(&right->desc->dest, ...)). For a
   conditional right side, `msg = (credit_1p < 2) ? &msg_credit : &msg_credits;` with msg in r7,
   generate_conditional_node passes its pref_regs to the test (cond->desc->pref_regs), so the test value is
   loaded into r7 and the constant 2 into r1. The arcade (credit_display_render) has the test with no preference:
   the value in r1 and #2 in r0 (cmp/ge), the result still in r7.

   Measured on the game (every C routine, 15f3f43d): the handover meets a conditional right side at 2 places
   (credit_display_render, mode_init_task); with the bit credit_display_render comes 3 halfwords closer
   (image 636 -> 633) and mode_init_task's code does not change; nothing else changes. Bit 2 (the test of any
   conditional takes no preference, a diagnostic) changes 548 routines and breaks effect_13_move and
   test_menu_init. A single witness (owner-approved 2026-10-17 as such).

   GEN_COND_PREF=<bits> (unset: 1, the arcade rule; 0: Release 26): 1 the rule; 2 no conditional's test takes
   its preference (a diagnostic, off: it breaks effect_13_move and test_menu_init). GEN_COND_PREF_LOG=<file> (a %d is the process id) logs each conditional right side met
   by the handover. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include "decls.h"
#include "imports.h"
#include "gen_rules.h"

extern char *gen_function_name;
int gen_cond_pref_mode(void)
{
    static int mode = -1;
    if (mode < 0) {
        const char *p = getenv("GEN_COND_PREF");
        mode = (p && *p) ? (int)strtol(p, 0, 0) : 1;
    }
    return mode;
}
/* generate_assign_node, the destination is a register that the right side does not need: 1 when it is not handed
   to a conditional right side as its preference (GEN_COND_PREF bit 1). GEN_COND_PREF_LOG=<file> (a %d is the
   process id) logs each conditional right side met there. */
int gen_assign_no_cond_handover(gen_node *right)
{
    static FILE *f;
    static int opened;
    int r = (gen_cond_pref_mode() & 1) != 0 && right->op == IL_COND;
    if (!opened) {
        const char *p = getenv("GEN_COND_PREF_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    if (f && right->op == IL_COND) {
        fprintf(f, "%s line %d cond handover %s\n", gen_function_name ? gen_function_name : "?", right->line, r ? "dropped" : "kept");
        fflush(f);
    }
    return r;
}
#endif
