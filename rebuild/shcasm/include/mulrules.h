/* ASM_MULWAIT (src/_mulrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's scheduler. */
#ifndef MULRULES_H
#define MULRULES_H
#if SHC_REBUILD_UPDATED
extern int asm_mul_busy_count(void);
extern int asm_mul_force_pick(int last_index);
#define MUL_BUSY_COUNT asm_mul_busy_count()
#define MUL_FORCE_PICK(last) asm_mul_force_pick(last)
#else
#define MUL_BUSY_COUNT 2
#define MUL_FORCE_PICK(last) 0
#endif
#endif
