#include "decls.h"
#include "imports.h"

// entry: 0040f0f0
// name : simplify_shift
// size : 155
// sig  : il_node * simplify_shift(il_node * node)


il_node * __cdecl simplify_shift(il_node *node)

{
  uint is_const;
  il_node *piVar1;
  
  is_const = is_const_value(node->child->next,0,node->type);
  if (is_const == 0) {
    if (node->op == IL_SR) {
      piVar1 = node->child;
      if ((((piVar1->next->op == IL_ID) && ((piVar1->next->type & 2) == 0)) &&
          (((piVar1->type & 0xe0) != 0 || ((piVar1->type & 4) == 0)))) &&
         (is_const = is_const_value(piVar1,0xffffffff,node->type), is_const != 0))
      goto LAB_0040f16c;
    }
    piVar1 = node->child->next;
    if (piVar1->op != IL_ID) {
      return node;
    }
    if ((piVar1->type & 2) != 0) {
      return node;
    }
    is_const = is_const_value(node->child,0,node->type);
    if (is_const == 0) {
      return node;
    }
  }
LAB_0040f16c:
  piVar1 = copy_tree(0,node->child);
  replace_and_free_node(node,piVar1);
  return piVar1;
}



