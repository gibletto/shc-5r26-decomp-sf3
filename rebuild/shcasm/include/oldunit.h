/* ASM_SIDE_ORDER (src/_oldunit.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's. A behaviour of the
   older compiler that built New Generation's sound driver, for a unit profile; unset or 0: Release 26. */
#ifndef OLDUNIT_H
#define OLDUNIT_H
#if SHC_REBUILD_UPDATED
extern int asm_side_order_fence(pipeline_entry *e);
#define SIDE_ORDER_FENCE(e) asm_side_order_fence(e)
#else
#define SIDE_ORDER_FENCE(e) 0
#endif
#endif
