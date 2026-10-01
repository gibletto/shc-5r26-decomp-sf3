#include "decls.h"
#include "imports.h"

// entry: 004184f0
// name : is_conditionally_evaluated
// size : 69
// sig  : char is_conditionally_evaluated(il_node * node)


char __cdecl is_conditionally_evaluated(il_node *node)

{
  int index;
  char result;
  il_node *parent;
  il_op parent_op;
  
  result = '\0';
  if ('\x1f' < (char)node->parent->op) {
    while( true ) {
      parent = node->parent;
      parent_op = parent->op;
      if (((parent_op == IL_COND) || (parent_op == IL_AND)) || (parent_op == IL_OR)) break;
      node = parent;
      if ((char)parent->parent->op < ' ') {
        return '\0';
      }
    }
    index = operand_index(node);
    if (index != 1) {
      result = '\x01';
    }
  }
  return result;
}



