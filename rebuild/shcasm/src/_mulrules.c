/* The arcade's rule for the multiplier in the SH-1/SH-2 list scheduler, ASM_MULWAIT (only with
   SHC_REBUILD_UPDATED=1).

   commit_scheduled_pipeline_entry sets g_pipeline_mac_busy after a MUL/MULS/MULU/MAC, and
   can_schedule_pipeline_entry_now holds back the next multiply and any STS/LDS of MACH/MACL while it is set; each
   other instruction issued counts it down. When every ready entry is held back (by that, by a load-use interlock or
   by the fetch/memory-access alignment rule), schedule_pipeline_window issues the first ready entry anyway.

   ASM_MULWAIT=<bits> (unset: 3, the arcade rule; 0: Release 26)
     1  the multiplier is busy for one instruction after the multiply, not two;
     2  when every ready entry is held back, the first one that is not waiting for the multiplier is issued.
   Together: `muls.w r3,r4 ; mov.l @(disp,pc),r0 ; sts macl,r4` where Release 26 writes `muls.w ; sts macl ;
   mov.l`, and the STS follows a single filler (q_em_dir, urien_dash_chk, comm_ixbw). */
#include "decls.h"
#include <stdlib.h>

#define MULWAIT_DEFAULT 3

static int mulwait(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("ASM_MULWAIT");
        k = (v && *v) ? atoi(v) : MULWAIT_DEFAULT;
    }
    return k;
}

/* the value commit_scheduled_pipeline_entry gives g_pipeline_mac_busy after a multiply */
int asm_mul_busy_count(void)
{
    return (mulwait() & 1) ? 1 : 2;
}

static int waits_for_multiplier(pipeline_entry *e)
{
    psd_op op = e->rec.op;
    if (!g_pipeline_mac_busy)
        return 0;
    if (op == OP_MUL || op == OP_MULS || op == OP_MULU || op == OP_MAC)
        return 1;
    if (op == OP_LDS && (e->rec.ea2->base == REG_MACH || e->rec.ea2->base == REG_MACL))
        return 1;
    return op == OP_STS && (e->rec.ea1->base == REG_MACH || e->rec.ea1->base == REG_MACL);
}

/* nothing could issue: issue the first ready entry that is not waiting for the multiplier (1), or leave it to
   Release 26's loop (0) */
int asm_mul_force_pick(int last_index)
{
    int i;
    if (!(mulwait() & 2))
        return 0;
    for (i = 0; i <= last_index; i++) {
        pipeline_entry *e = &g_pipeline_window[i];
        if (e->count == 0 && e->next == -1 && e->rec.op != OP_DUMMY_00 && !waits_for_multiplier(e)) {
            commit_scheduled_pipeline_entry(i);
            return 1;
        }
    }
    return 0;
}
