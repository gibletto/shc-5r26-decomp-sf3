#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_late_handler_index_by_op
#define g_late_handler_index_by_op (*(unsigned char * *)(g_sd + 0x98e8))


// entry: 00431e40
// name : map_code_node_opcode_to_late_handler_index
// size : 133
// sig  : int map_code_node_opcode_to_late_handler_index(short op)


int __cdecl map_code_node_opcode_to_late_handler_index(short op)

{
  int handler_index;
  
  if (op == 0x6f) {
    return -1;
  }
  handler_index = op + -0x20;
  if (handler_index < 0) {
    report_codegen_message(0x1222,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return handler_index;
  }
  handler_index = (int)*(char *)((int)&g_late_handler_index_by_op + (int)op);
  if ((handler_index < 0) || (0x2f < handler_index)) {
    report_codegen_message(0x1222,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  return handler_index;
}



