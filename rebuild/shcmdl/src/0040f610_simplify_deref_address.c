#include "decls.h"
#include "imports.h"

// entry: 0040f610
// name : simplify_deref_address
// size : 110
// sig  : il_node * simplify_deref_address(il_node * node)


il_node * __cdecl simplify_deref_address(il_node *node)

{
  il_node *result;
  
  result = node;
  if ((il_op)((node->op == IL_ASTER) + IL_ASTER) == node->child->op) {
    if (node->op == IL_ASTER) {
      result = node->child->child;
      if ((result->type != node->type) || (result->val != node->val)) {
        if (result->op == IL_ID) {
          return node;
        }
        result->type = node->type;
        node->child->child->val = node->val;
      }
    }
    result = copy_tree(0,node->child->child);
    replace_and_free_node(node,result);
  }
  return result;
}



