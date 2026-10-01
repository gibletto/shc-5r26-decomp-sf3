#include "decls.h"
#include "imports.h"

// entry: 00434c70
// name : ilb_node_operands_full
// size : 108
// sig  : short ilb_node_operands_full(gen_node * node, int depth)


short __cdecl ilb_node_operands_full(gen_node *node,int depth)

{
  int arity;
  int count;
  
  count = *(int *)(g_ilb_operand_counts + depth * 4);
  if (count == -1) {
    return 1;
  }
  arity = (int)(char)(&g_il_op_arity)[node->op];
  if (arity == -2) {
    report_message_by_code((char *)0x0,0,0x12d5,(char *)0x0);
    stock_exit(0xb);
  }
  if (arity == -1) {
    return 0;
  }
  if ((-1 < count) && (count < arity)) {
    return 0;
  }
  return 1;
}



