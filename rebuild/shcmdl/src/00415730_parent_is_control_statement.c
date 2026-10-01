#include "decls.h"
#include "imports.h"

// entry: 00415730
// name : parent_is_control_statement
// size : 41
// sig  : int parent_is_control_statement(il_node * node)


int __cdecl parent_is_control_statement(il_node *node)

{
  int result;
  
  result = 0;
  switch(node->parent->op) {
  case IL_SWITCH:
  case IL_IF:
  case IL_RETURN:
  case IL_GLABEL:
  case IL_CLABEL:
  case IL_DLABEL:
    result = 1;
  }
  return result;
}



