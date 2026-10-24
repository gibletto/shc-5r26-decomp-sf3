/* ASM_READY_WAVES: stable ready frontiers, default0 (native scheduler). */
#ifndef READY_WAVE_H
#define READY_WAVE_H
#if SHC_REBUILD_UPDATED
extern void asm_ready_wave_reset(void);
extern void asm_ready_wave_prepare(int last);
extern void asm_ready_wave_promote(int parent);
extern int asm_ready_wave_count(int last);
extern int asm_ready_wave_index(int position);
#define READY_WAVE_RESET() asm_ready_wave_reset()
#define READY_WAVE_PREPARE(last) asm_ready_wave_prepare(last)
#define READY_WAVE_PROMOTE(parent) asm_ready_wave_promote(parent)
#define READY_WAVE_COUNT(last) asm_ready_wave_count(last)
#define READY_WAVE_INDEX(position) asm_ready_wave_index(position)
#else
#define READY_WAVE_RESET() ((void)0)
#define READY_WAVE_PREPARE(last) ((void)0)
#define READY_WAVE_PROMOTE(parent) ((void)0)
#define READY_WAVE_COUNT(last) ((last)+1)
#define READY_WAVE_INDEX(position) (position)
#endif
#endif
