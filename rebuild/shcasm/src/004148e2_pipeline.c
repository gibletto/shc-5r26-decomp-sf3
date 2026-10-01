#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 004148e2
// name : pipeline
// size : 446
// sig  : void pipeline(void)


int __cdecl pipeline(void)

{
  pipeline_entry *last_entry;
  psd_op last_op;
  
  last_entry = load_pipeline_window();
  if (last_entry == (pipeline_entry *)0x0) {
    g_pipeline_input_exhausted = 1;
  }
  else {
    if ((g_pipeline_window_ended_at_c_jmp == 0) && (g_pipeline_lookahead_record.op == OP_DUMMY_00))
    {
      g_pipeline_input_exhausted = 1;
    }
    else {
      last_op = (last_entry->rec).op;
      if (((((last_op == OP_BRA) ||
            (((last_op == OP_BT || (last_op == OP_BF)) || (last_op == OP_JMP)))) ||
           (((last_op == OP_BSR || (last_op == OP_BT_S)) || (last_op == OP_BF_S)))) ||
          ((last_op == OP_BSRF || (last_op == OP_BRAF)))) ||
         (((last_op == OP_JSR ||
           ((((last_op == OP_RTS || (last_op == OP_RTE)) || (last_op == OP_TRAPA)) ||
            (g_pipeline_window_ended_at_c_jmp == 1)))) ||
          ((OP_BEND < g_pipeline_lookahead_record.op &&
           (g_pipeline_lookahead_record.op < OP_DUMMY_1C)))))) {
        g_pipeline_window_ends_block = 1;
        g_pipeline_window_ended_at_c_jmp = 0;
      }
    }
    mark_pipeline_tail_barrier();
    build_pipeline_dependency_graph();
    schedule_pipeline_window();
    refill_pipeline_when_drained();
    if ((g_current_request->flags_13c & 8) != 0) {
      _printf(s_pipetbl_dump_after_pipeline);
      dump_pipeline_table();
    }
  }
  return;
}
