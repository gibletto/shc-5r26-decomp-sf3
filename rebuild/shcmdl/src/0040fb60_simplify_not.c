#include "decls.h"
#include "imports.h"

// entry: 0040fb60
// name : simplify_not
// size : 83
// sig  : il_node * simplify_not(il_node * node)


il_node * __cdecl simplify_not(il_node *node)

{
  il_op new_op;
  il_node *inner;
  
  new_op = mirror_or_negate_relop(node->child->op,1);
  if (new_op != IL_NON_FF) {
    inner = node->child;
    if (((inner->child->type & 0xe0) == 0) && ((inner->child->next->type & 0xe0) == 0)) {
      inner->op = new_op;
      replace_node(node,inner);
      free_node(node);
      node = inner;
    }
  }
  return node;
}



