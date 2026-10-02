/* The ASM_NOSCHED diagnostic (only with SHC_REBUILD_UPDATED=1).

   ASM_NOSCHED=1 (off unless set): the SH-1/SH-2 list scheduler issues each window in the order shcpep wrote it,
   so -code=asmcode shows the code before scheduling. Use it with ASM_MULWAIT=1 (a forced issue under ASM_MULWAIT
   bit 2 may pick a later entry). */
#include "decls.h"
#include <stdlib.h>

int asm_sched_can_issue(int index)
{
    static int nosched = -1;
    if (nosched < 0) {
        const char *v = getenv("ASM_NOSCHED");
        nosched = (v && *v) ? atoi(v) : 0;
    }
    if (nosched) {
        int j;
        for (j = 0; j < index; j++)
            if (g_pipeline_window[j].rec.op != OP_DUMMY_00 && g_pipeline_window[j].next == -1)
                return 0;
    }
    return can_schedule_pipeline_entry_now(index);
}
