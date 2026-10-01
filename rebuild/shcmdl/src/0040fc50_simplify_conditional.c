#include "decls.h"
#include "imports.h"

// entry: 0040fc50
// name : simplify_conditional
// size : 78
// sig  : il_node * simplify_conditional(il_node * node)


il_node * __cdecl simplify_conditional(il_node *node)

{
  uint is_zero;
  il_node *chosen;
  il_node *result;
  
  chosen = node->child;
  result = node;
  if (chosen->op == IL_CONST) {
    is_zero = is_const_value(chosen,0,chosen->type);
    if (is_zero == 0) {
      chosen = node->child->next;
    }
    else {
      chosen = node->child->next->next;
    }
    result = copy_tree(0,chosen);
    replace_and_free_node(node,result);
  }
  return result;
}



