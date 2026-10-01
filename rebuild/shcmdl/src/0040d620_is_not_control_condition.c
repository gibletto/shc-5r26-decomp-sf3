#include "decls.h"
#include "imports.h"

// entry: 0040d620
// name : is_not_control_condition
// size : 81
// sig  : char is_not_control_condition(il_node * node)


char __cdecl is_not_control_condition(il_node *node)

{
  int opno;
  
  opno = operand_index(node);
  switch(node->parent->op) {
  case IL_SWITCH:
  case IL_IF:
    return '\x01' - (opno == 1);
  default:
    return '\x01';
  case IL_FOR:
    return '\x01' - (opno == 4);
  case IL_WHILE:
  case IL_DO:
    return '\x01' - (opno == 2);
  }
}



