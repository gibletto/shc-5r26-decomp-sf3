#include "decls.h"
#include "imports.h"

// entry: 0041e460
// name : tree_has_conditional_op
// size : 65
// sig  : int tree_has_conditional_op(il_node * tree)


int __cdecl tree_has_conditional_op(il_node *tree)

{
  int found;
  il_node *child;
  il_op op;
  
  child = tree->child;
  while( true ) {
    found = 0;
    if (child == (il_node *)0x0) {
      op = tree->op;
      if ((((op == IL_COMMA) || (op == IL_COND)) || (op == IL_AND)) || (op == IL_OR)) {
        found = 1;
      }
      return found;
    }
    found = tree_has_conditional_op(child);
    if (found != 0) break;
    child = child->next;
  }
  return found;
}



