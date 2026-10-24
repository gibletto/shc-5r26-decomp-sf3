#include "decls.h"
#include "imports.h"
#include "mulrules.h"
#include "nosched.h"
#include "ready_wave.h"

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
  int position;
  short prev_blocked;
  
  last_index = (short)g_pipeline_window_last_index;
  READY_WAVE_PREPARE(last_index);
  prev_blocked = 0;
  blocked_count = 1;
  while (blocked_count != prev_blocked) {
    prev_blocked = blocked_count;
    blocked_count = 1;
    for (position = 0; position < READY_WAVE_COUNT(last_index); position++) {
      i = READY_WAVE_INDEX(position);
      if (((g_pipeline_window[i].count == 0) && (g_pipeline_window[i].next == -1)) &&
         (g_pipeline_window[i].rec.op != OP_DUMMY_00)) {
        can_issue = SCHED_CAN_ISSUE(i);
        if (can_issue == 0) {
          blocked_count = blocked_count + 1;
        }
        else {
          commit_scheduled_pipeline_entry(i);
        }
      }
    }
  }
  if (g_pipeline_last_scheduled == -1 && MUL_FORCE_PICK(last_index)) {
    return;
  }
  if (g_pipeline_last_scheduled == -1) {
    for (position = 0; position < READY_WAVE_COUNT(last_index); position++) {
      i = READY_WAVE_INDEX(position);
      if (((g_pipeline_window[i].count == 0) && (g_pipeline_window[i].next == -1)) &&
         (g_pipeline_window[i].rec.op != OP_DUMMY_00)) {
        commit_scheduled_pipeline_entry(i);
        return;
      }
    }
  }
  return;
}
