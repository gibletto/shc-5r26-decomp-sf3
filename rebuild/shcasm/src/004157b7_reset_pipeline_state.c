#include "decls.h"
#include "imports.h"

// entry: 004157b7
// name : reset_pipeline_state
// size : 322
// sig  : void reset_pipeline_state(void)


int __cdecl reset_pipeline_state(void)

{
  short i;
  
  g_pipeline_first_scheduled = -1;
  g_pipeline_last_scheduled = -1;
  g_pipeline_end_of_stream = 0;
  g_pipeline_input_exhausted = 0;
  g_pipeline_reload_pending = 0;
  g_pipeline_window_ends_block = 0;
  g_pipeline_window_last_index = 0xffffffff;
  g_pipeline_hold = 0;
  g_pipeline_edge_count = 0;
  g_pipeline_drained_count = 0;
  g_pipeline_load_result_regs[1] = 0;
  g_pipeline_load_result_regs[0] = 0;
  for (i = 0; i < 0x20; i = i + 1) {
    g_pipeline_window[i].rec.op = OP_DUMMY_00;
    g_pipeline_window[i].setreg[0] = 0;
    g_pipeline_window[i].setreg[1] = 0;
    g_pipeline_window[i].refreg[0] = 0;
    g_pipeline_window[i].refreg[1] = 0;
    g_pipeline_window[i].flags = 0;
    g_pipeline_window[i].depend = -1;
    g_pipeline_window[i].next = -1;
    g_pipeline_window[i].count = 0;
  }
  return;
}
