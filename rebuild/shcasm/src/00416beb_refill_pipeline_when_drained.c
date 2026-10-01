#include "decls.h"
#include "imports.h"

// entry: 00416beb
// name : refill_pipeline_when_drained
// size : 131
// sig  : void refill_pipeline_when_drained(void)


int __cdecl refill_pipeline_when_drained(void)

{
  if (((g_pipeline_last_scheduled == -1) && (g_pipeline_first_scheduled == -1)) &&
     (g_pipeline_hold == 0)) {
    if (g_pipeline_window_ends_block == 1) {
      g_pipeline_reload_pending = 1;
    }
    if (g_pipeline_input_exhausted == 1) {
      g_pipeline_end_of_stream = 1;
    }
    if ((g_pipeline_window_ends_block == 0) && (g_pipeline_input_exhausted == 0)) {
      pipeline();
    }
  }
  return;
}
