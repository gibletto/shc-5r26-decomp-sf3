#include "decls.h"
#include "imports.h"

// entry: 004158f9
// name : mark_pipeline_tail_barrier
// size : 343
// sig  : void mark_pipeline_tail_barrier(void)


int __cdecl mark_pipeline_tail_barrier(void)

{
  short last_index;
  psd_op last_op;
  
  last_index = (short)g_pipeline_window_last_index;
  if ((last_index != 0) &&
     (((((last_op = g_pipeline_window[last_index].rec.op, last_op == OP_BRA || (last_op == OP_BT))
        || (last_op == OP_BF)) ||
       ((((last_op == OP_JMP || (last_op == OP_BSR)) ||
         ((last_op == OP_BT_S || ((last_op == OP_BF_S || (last_op == OP_BSRF)))))) ||
        (last_op == OP_BRAF)))) ||
      ((((last_op == OP_B_ASM || (last_op == OP_JSR)) || (last_op == OP_RTS)) ||
       ((last_op == OP_RTE || (last_op == OP_TRAPA)))))))) {
    g_pipeline_window[last_index].setreg[0] = 0xffffffff;
    g_pipeline_window[last_index].setreg[1] = 0xffffffff;
    g_pipeline_window[last_index].flags = g_pipeline_window[last_index].flags | 0x4000;
  }
  return;
}
