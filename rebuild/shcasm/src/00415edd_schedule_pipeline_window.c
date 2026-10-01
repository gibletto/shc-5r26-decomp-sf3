#include "decls.h"
#include "imports.h"

// entry: 00415edd
// name : schedule_pipeline_window
// size : 341
// sig  : void schedule_pipeline_window(void)


int __cdecl schedule_pipeline_window(void)

{
  short last_index;
  int can_issue;
  short blocked_count;
  int i;
  short prev_blocked;
  
  last_index = (short)g_pipeline_window_last_index;
  prev_blocked = 0;
  blocked_count = 1;
  while (blocked_count != prev_blocked) {
    prev_blocked = blocked_count;
    blocked_count = 1;
    for (i = 0; i <= last_index; i = i + 1) {
      if (((g_pipeline_window[i].count == 0) && (g_pipeline_window[i].next == -1)) &&
         (g_pipeline_window[i].rec.op != OP_DUMMY_00)) {
        can_issue = can_schedule_pipeline_entry_now(i);
        if (can_issue == 0) {
          blocked_count = blocked_count + 1;
        }
        else {
          commit_scheduled_pipeline_entry(i);
        }
      }
    }
  }
  if (g_pipeline_last_scheduled == -1) {
    for (i = 0; i <= last_index; i = i + 1) {
      if (((g_pipeline_window[i].count == 0) && (g_pipeline_window[i].next == -1)) &&
         (g_pipeline_window[i].rec.op != OP_DUMMY_00)) {
        commit_scheduled_pipeline_entry(i);
        return;
      }
    }
  }
  return;
}
