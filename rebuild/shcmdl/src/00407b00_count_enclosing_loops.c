#include "decls.h"
#include "imports.h"

// entry: 00407b00
// name : count_enclosing_loops
// size : 41
// sig  : int count_enclosing_loops(il_node * node)


int __cdecl count_enclosing_loops(il_node *node)

{
  int count;
  il_node *ancestor;
  il_op op;
  
  count = 0;
  ancestor = node->parent;
  op = ancestor->op;
  while (op != IL_FUNC) {
    op = ancestor->op;
    if (((op == IL_FOR) || (op == IL_WHILE)) || (op == IL_DO)) {
      count = count + 1;
    }
    ancestor = ancestor->parent;
    op = ancestor->op;
  }
  return count;
}



