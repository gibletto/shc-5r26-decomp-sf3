/* Unit-profile rule of the older compiler that built New Generation's sound driver (only with
   SHC_REBUILD_UPDATED=1; unset or 0: Release 26).
   ASM_SIDE_ORDER=<bits>: the list scheduler treats a memory access with a side effect as it treats a volatile access
   (compute_pipeline_opcode_masks_and_flags: it sets every register and writes memory), so it keeps its place in the
   window: what comes before it issues before it, what comes after it issues after it.
     1  an access through a pointer that it steps (@Rn+, @-Rn; not the stack pointer's pushes and pops)
     2  a store through a pointer (not to the stack frame) */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "oldunit.h"

static int setting(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("ASM_SIDE_ORDER");
        k = (v && *v) ? (int)strtol(v, 0, 0) : 0;
    }
    return k;
}

static int memory_kind(ea *e)
{
    int t = e != 0 ? (e->type & 0x1f) : 0;
    return (t >= 2 && t <= 4) || (t >= 8 && t <= 13 && t != 10);
}

static int stepped(ea *e)
{
    return e != 0 && ((e->type & 0x1f) == 3 || (e->type & 0x1f) == 4) && e->base != REG_R15;
}

/* the operands the native mask code looks at: the written one (1: ea1, 2: ea2) and the read ones (1: ea1, 2: ea2
   and ea1) */
int asm_side_order_fence(pipeline_entry *e)
{
    int k = setting(), op, w, r;
    ea *dst;
    if (!k)
        return 0;
    op = e->rec.op;
    w = (&g_pipeline_op_written_operand)[op];
    r = (&g_pipeline_op_read_operands)[op];
    dst = w == 1 ? e->rec.ea1 : w == 2 ? e->rec.ea2 : 0;
    if (k & 1) {
        if (stepped(dst))
            return 1;
        if ((r == 1 || r == 2) && stepped(e->rec.ea1))
            return 1;
        if (r == 2 && stepped(e->rec.ea2))
            return 1;
    }
    if ((k & 2) && memory_kind(dst) && dst->base != REG_R15)
        return 1;
    return 0;
}
#endif
