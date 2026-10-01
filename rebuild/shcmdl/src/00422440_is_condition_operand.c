#include "decls.h"
#include "imports.h"

// entry: 00422440
// name : is_condition_operand
// size : 91
// sig  : int is_condition_operand(il_node * node)


int __cdecl is_condition_operand(il_node *node)

{
  int index;
  int result;
  
  result = 0;
  index = operand_index(node);
  switch(node->parent->op) {
  case IL_IF:
  case IL_COND:
    if (index == 1) {
      return 1;
    }
    break;
  case IL_FOR:
    if (index == 4) {
      return 1;
    }
    break;
  case IL_WHILE:
  case IL_DO:
    if (index != 1) {
      result = 1;
    }
  }
  return result;
}



