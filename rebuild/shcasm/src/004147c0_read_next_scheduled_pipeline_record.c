#include "decls.h"
#include "imports.h"

// entry: 004147c0
// name : read_next_scheduled_pipeline_record
// size : 285
// sig  : psd * read_next_scheduled_pipeline_record(psd * rec)


psd * __cdecl read_next_scheduled_pipeline_record(psd *rec)

{
  short index;
  
  if (g_pipeline_window_last_index == -1) {
    g_pipeline_end_of_stream = 1;
    g_pipeline_reload_pending = 1;
    rec = (psd *)0x0;
  }
  else if (g_pipeline_end_of_stream == 1) {
    rec = (psd *)0x0;
  }
  else {
    if (g_pipeline_reload_pending == 1) {
      pipeline();
    }
    g_pipeline_reload_pending = 0;
    g_pipeline_end_of_stream = 0;
    index = (short)g_pipeline_first_scheduled;
    stock_memcpy(rec,g_pipeline_window + index,0x18);
    release_pipeline_entry_successors(index);
    g_pipeline_first_scheduled = (int)g_pipeline_window[index].next;
    if (g_pipeline_first_scheduled == -2) {
      g_pipeline_first_scheduled = -1;
      g_pipeline_last_scheduled = -1;
    }
    clear_pipeline_entry_and_dependencies(index);
    schedule_pipeline_window();
    refill_pipeline_when_drained();
    g_pipeline_drained_count = g_pipeline_drained_count + 1;
  }
  return rec;
}



