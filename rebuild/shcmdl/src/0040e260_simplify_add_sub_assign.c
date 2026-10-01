#include "decls.h"
#include "imports.h"

// entry: 0040e260
// name : simplify_add_sub_assign
// size : 202
// sig  : il_node * simplify_add_sub_assign(il_node * node)


il_node * __cdecl simplify_add_sub_assign(il_node *node)

{
  uint is_const;
  il_node *piVar1;
  il_node *rhs;
  
  if ((node->child->flag & 0x40) == 0) {
    piVar1 = node->child->next;
    is_const = is_const_value(piVar1,0,piVar1->type);
    if (is_const != 0) {
      piVar1 = copy_tree(0,node->child);
      replace_and_free_node(node,piVar1);
      node = piVar1;
      goto LAB_0040e2d2;
    }
  }
  piVar1 = node->child->next;
  if (piVar1->op == IL_MINUS) {
    replace_node(piVar1,piVar1->child);
    free_node(piVar1);
    node->op = (node->op == IL_A_ADD) + IL_A_ADD;
  }
LAB_0040e2d2:
  if ((((node->op == IL_A_SUB) && (piVar1 = node->child, piVar1->op == IL_ID)) &&
      ((piVar1->type & 2) == 0)) &&
     (((rhs = piVar1->next, rhs->op == IL_ID && ((rhs->type & 2) == 0)) &&
      (rhs->symx == piVar1->symx)))) {
    piVar1 = new_const_node(node->type & 0xfc,0);
    replace_and_free_node(node->child->next,piVar1);
    node->op = IL_ASSIGN;
  }
  return node;
}



