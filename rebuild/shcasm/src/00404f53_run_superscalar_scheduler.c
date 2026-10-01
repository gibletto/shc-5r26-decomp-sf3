#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00404f53
// name : run_superscalar_scheduler
// size : 114
// sig  : void run_superscalar_scheduler(void)


int __cdecl run_superscalar_scheduler(void)

{
  if (g_pipeline_window_last_index != 0) {
    clear_superscalar_window_analysis();
    for (g_superscalar_current_entry = '\0';
        g_superscalar_current_entry <= g_pipeline_window_last_index;
        g_superscalar_current_entry = g_superscalar_current_entry + '\x01') {
      describe_superscalar_window_entry();
    }
    build_superscalar_dependency_graph();
    if ((g_current_request->flags_13c & 8) != 0) {
      compute_original_order_issue_cycles();
    }
    schedule_superscalar_window();
  }
  return;
}
