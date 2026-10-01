#include "decls.h"
#include "imports.h"

// entry: 0040e730
// name : simplify_shift_assign
// size : 71
// sig  : il_node * simplify_shift_assign(il_node * node)


il_node * __cdecl simplify_shift_assign(il_node *node)

{
  uint is_const;
  il_node *result;
  
  result = node;
  if ((node->child->flag & 0x40) == 0) {
    is_const = is_const_value(node->child->next,0,node->type);
    if (is_const != 0) {
      result = copy_tree(0,node->child);
      replace_and_free_node(node,result);
    }
  }
  return result;
}



