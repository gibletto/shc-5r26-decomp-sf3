#include "decls.h"
#include "imports.h"

// entry: 0040e920
// name : simplify_xor_assign
// size : 150
// sig  : il_node * simplify_xor_assign(il_node * node)


il_node * __cdecl simplify_xor_assign(il_node *node)

{
  il_node *piVar1;
  uint is_const;
  il_node *piVar2;
  
  piVar1 = node->child;
  if ((((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) &&
      (piVar2 = piVar1->next, piVar2->op == IL_ID)) &&
     (((piVar2->type & 2) == 0 && (piVar2->symx == piVar1->symx)))) {
    piVar1 = new_const_node(node->type & 0xfc,0);
    replace_and_free_node(node->child->next,piVar1);
    node->op = IL_ASSIGN;
    return node;
  }
  piVar2 = node;
  if ((piVar1->flag & 0x40) == 0) {
    is_const = is_const_value(piVar1->next,0,node->type);
    if (is_const != 0) {
      piVar2 = copy_tree(0,node->child);
      replace_and_free_node(node,piVar2);
    }
  }
  return piVar2;
}



