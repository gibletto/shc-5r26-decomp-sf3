#include "decls.h"
#include "imports.h"

// entry: 0040e4a0
// name : simplify_div_assign
// size : 355
// sig  : il_node * simplify_div_assign(il_node * node)


il_node * __cdecl simplify_div_assign(il_node *node)

{
  byte type;
  il_node *piVar1;
  uint is_const;
  int shift;
  il_node *rhs;
  
  piVar1 = node->child;
  if ((((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) &&
      (rhs = piVar1->next, rhs->op == IL_ID)) &&
     (((rhs->type & 2) == 0 && (rhs->symx == piVar1->symx)))) {
    piVar1 = new_const_node(node->type & 0xfc,1);
    replace_and_free_node(node->child->next,piVar1);
    node->op = IL_ASSIGN;
    return node;
  }
  if ((piVar1->flag & 0x40) == 0) {
    is_const = is_const_value(piVar1->next,1,piVar1->next->type);
    if (is_const != 0) {
      piVar1 = copy_tree(0,node->child);
      replace_and_free_node(node,piVar1);
      return piVar1;
    }
  }
  piVar1 = node->child;
  rhs = piVar1->next;
  if (((rhs->op == IL_CONST) && ((node->type & 0xe0) == 0)) &&
     (((node->type & 4) != 0 &&
      ((((piVar1->type & 0xe0) == 0 && ((piVar1->type & 4) != 0)) && ((rhs->type & 0xe0) == 0))))))
  {
    shift = power_of_two_index(rhs->val,0);
    if (shift != 0) {
      node->child->next->val = shift + -1;
      node->op = IL_A_SR;
      return node;
    }
  }
  else if ((((piVar1->flag & 2) == 0) && (((node->type & 0xe0) != 0 || ((node->type & 4) == 0)))) &&
          ((((piVar1->type & 0xe0) != 0 || ((piVar1->type & 4) == 0)) &&
           ((type = rhs->type, (type & 0xe0) != 0 || ((type & 4) == 0)))))) {
    is_const = is_const_value(rhs,0xffffffff,type);
    if (is_const != 0) {
      piVar1 = copy_tree(0,node->child);
      piVar1 = make_node(IL_MINUS,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
      replace_and_free_node(node->child->next,piVar1);
      node->op = IL_ASSIGN;
    }
  }
  return node;
}



