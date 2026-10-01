#include "decls.h"
#include "imports.h"

// entry: 0041d010
// name : in_conditional_operator
// size : 70
// sig  : int in_conditional_operator(il_node * node)


int __cdecl in_conditional_operator(il_node *node)

{
  ushort flag;
  il_op op;
  
  flag = node->flag;
  while ((flag & 0x200) == 0) {
    op = node->op;
    if (((op == IL_OR) || (op == IL_COND)) || (op == IL_AND)) {
      return 1;
    }
    node = node->parent;
    flag = node->flag;
  }
  op = node->op;
  if (((op != IL_OR) && (op != IL_COND)) && (op != IL_AND)) {
    return 0;
  }
  return 1;
}



