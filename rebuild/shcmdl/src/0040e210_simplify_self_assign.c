#include "decls.h"
#include "imports.h"

// entry: 0040e210
// name : simplify_self_assign
// size : 74
// sig  : il_node * simplify_self_assign(il_node * node)


il_node * __cdecl simplify_self_assign(il_node *node)

{
  il_node *result;
  il_node *lhs;
  il_node *rhs;
  
  lhs = node->child;
  result = node;
  if ((((lhs->op == IL_ID) && ((lhs->type & 2) == 0)) && (rhs = lhs->next, rhs->op == IL_ID)) &&
     (((rhs->type & 2) == 0 && (rhs->symx == lhs->symx)))) {
    result = copy_tree(0,lhs);
    replace_and_free_node(node,result);
  }
  return result;
}



