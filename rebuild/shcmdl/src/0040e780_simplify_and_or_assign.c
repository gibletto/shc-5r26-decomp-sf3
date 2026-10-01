#include "decls.h"
#include "imports.h"

// entry: 0040e780
// name : simplify_and_or_assign
// size : 404
// sig  : il_node * simplify_and_or_assign(il_node * node)


il_node * __cdecl simplify_and_or_assign(il_node *node)

{
  il_node *piVar1;
  uint is_const;
  uint uVar2;
  il_node *rhs;
  
  piVar1 = node->child;
  uVar2 = (node->op == IL_A_AND) - 1;
  if ((((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) &&
      (rhs = piVar1->next, rhs->op == IL_ID)) &&
     (((rhs->type & 2) == 0 && (rhs->symx == piVar1->symx)))) {
    piVar1 = copy_tree(0,piVar1);
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  if (((piVar1->flag & 0x40) == 0) &&
     (is_const = is_const_value(piVar1->next,uVar2,node->type), is_const != 0)) {
    piVar1 = new_const_node(node->type & 0xfc,uVar2);
    replace_and_free_node(node->child->next,piVar1);
    node->op = IL_ASSIGN;
    return node;
  }
  if (((node->child->flag & 0x40) == 0) &&
     (uVar2 = is_const_value(node->child->next,~uVar2,node->type), uVar2 != 0)) {
    piVar1 = copy_tree(0,node->child);
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  if (node->op == IL_A_AND) {
    piVar1 = node->child->next;
    if (piVar1->op == IL_CAST) {
      piVar1 = piVar1->child;
    }
    if ((node->child->flag & 2) == 0) {
      uVar2 = is_const_value(piVar1,0xffff,node->type);
      if ((uVar2 == 0) && (is_const = is_const_value(piVar1,0xff,node->type), is_const == 0)) {
        return node;
      }
      piVar1 = copy_tree(0,node->child);
      piVar1 = make_node(IL_CAST,(-(uVar2 == 0) & 0xf8U) + 0xc,piVar1,(il_node *)0x0,(il_node *)0x0)
      ;
      piVar1 = make_node(IL_CAST,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
      replace_and_free_node(node->child->next,piVar1);
      node->op = IL_ASSIGN;
    }
  }
  return node;
}



