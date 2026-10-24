/* Stable topological frontiers, with native hazard/phase choices within each.
   Ready successors enter the next frontier only on predecessor retirement. */
#if SHC_REBUILD_UPDATED
#include "decls.h"
#include "ready_wave.h"
#include <stdlib.h>

static short wave[32], next_wave[32];
static int wave_count, next_count, initialized;

static int enabled(void)
{
    static int value = -1;
    if (value < 0) {
        const char *p = getenv("ASM_READY_WAVES");
        value = (p && *p) ? atoi(p) : 0;
    }
    return value != 0;
}

void asm_ready_wave_reset(void)
{
    wave_count = next_count = initialized = 0;
}

void asm_ready_wave_prepare(int last)
{
    int i;
    if (!enabled()) return;
    if (!initialized) {
        for (i = 0; i <= last; i++) {
            pipeline_entry *e = &g_pipeline_window[i];
            if (e->count == 0 && e->next == -1 && e->rec.op != OP_DUMMY_00)
                wave[wave_count++] = (short)i;
        }
        initialized = 1;
        return;
    }
    if (g_pipeline_first_scheduled != -1 || g_pipeline_last_scheduled != -1)
        return;
    for (i = 0; i < wave_count; i++)
        if (g_pipeline_window[wave[i]].rec.op != OP_DUMMY_00) return;
    wave_count = next_count;
    for (i = 0; i < next_count; i++) wave[i] = next_wave[i];
    next_count = 0;
}

void asm_ready_wave_promote(int parent)
{
    unsigned int released = 0;
    short edge;
    int i;
    if (!enabled()) return;
    /* Native edge lists need not be in source order. Simultaneous releases
       from one retired parent are inserted in original instruction order. */
    for (edge = g_pipeline_window[parent].depend; edge != -1;
         edge = g_pipeline_edges[edge].next) {
        int child = g_pipeline_edges[edge].entry;
        pipeline_entry *e = &g_pipeline_window[child];
        if (e->count == 0 && e->next == -1 && e->rec.op != OP_DUMMY_00)
            released |= 1u << child;
    }
    for (i = 0; i < 32; i++)
        if (released & (1u << i)) next_wave[next_count++] = (short)i;
}

int asm_ready_wave_count(int last)
{
    return enabled() ? wave_count : last + 1;
}

int asm_ready_wave_index(int position)
{
    return enabled() ? wave[position] : position;
}
#endif
