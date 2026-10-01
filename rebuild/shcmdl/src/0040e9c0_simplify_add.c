#include "decls.h"
#include "imports.h"

// entry: 0040e9c0
// name : simplify_add
// size : 122
// sig  : il_node * simplify_add(il_node * node)


il_node * __cdecl simplify_add(il_node *node)

{
  uint is_const;
  il_node *result;
  
  is_const = is_const_value(node->child,0,node->type);
  if (is_const != 0) {
    result = copy_tree(0,node->child->next);
    replace_and_free_node(node,result);
    return result;
  }
  is_const = is_const_value(node->child->next,0,node->type);
  result = node;
  if (is_const != 0) {
    result = copy_tree(0,node->child);
    replace_and_free_node(node,result);
  }
  return result;
}



