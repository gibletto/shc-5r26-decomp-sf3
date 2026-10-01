#include "decls.h"
#include "imports.h"

// entry: 0041ced0
// name : select_shift_routine
// size : 154
// sig  : short select_shift_routine(gen_node * node)


short __cdecl select_shift_routine(gen_node *node)

{
  short shift;
  gen_node *right;
  byte type_class;
  short local_2;
  gen_node *left;
  
  right = (gen_node *)0x0;
  left = node->child;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  shift = (short)(right->desc->value).disp;
  switch(node->op) {
  case IL_SL:
  case IL_A_SL:
    return shift + 0x4b;
  case IL_SR:
  case IL_A_SR:
    break;
  default:
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  }
  if ((((left->type & 4) == 0) && (type_class = left->type & 0xe0, type_class != 0x80)) &&
     (type_class != 0x40)) {
    return shift + 0x8b;
  }
  return shift + 0x6b;
}



