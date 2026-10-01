#include "decls.h"
#include "imports.h"

// entry: 0040edc0
// name : simplify_div
// size : 512
// sig  : il_node * simplify_div(il_node * node)


il_node * __cdecl simplify_div(il_node *node)

{
  il_node *piVar1;
  uint is_const;
  int shift;
  short filn;
  byte lhs_type;
  ushort line;
  short listno;
  il_node *rhs;
  
  filn = node->filn;
  line = node->line;
  listno = node->listno;
  piVar1 = node->child;
  if ((((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) &&
      (rhs = piVar1->next, rhs->op == IL_ID)) &&
     (((rhs->type & 2) == 0 && (rhs->symx == piVar1->symx)))) {
    piVar1 = new_const_node(node->type & 0xfc,1);
    piVar1->filn = filn;
    piVar1->line = line;
    piVar1->listno = listno;
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  is_const = is_const_value(piVar1->next,1,node->type);
  if (is_const != 0) {
    piVar1 = copy_tree(0,node->child);
    if (node->child->type != node->type) {
      piVar1 = make_node(IL_CAST,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
    }
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  lhs_type = node->child->type;
  if ((((lhs_type & 0xe0) != 0) || ((lhs_type & 4) == 0)) &&
     (is_const = is_const_value(node->child->next,0xffffffff,node->type), is_const != 0)) {
    piVar1 = copy_tree(0,node->child);
    piVar1 = make_node(IL_MINUS,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
    piVar1->filn = filn;
    piVar1->line = line;
    piVar1->listno = listno;
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  if (((node->type & 0xe0) == 0) && ((node->type & 4) != 0)) {
    lhs_type = node->child->type;
    if (((lhs_type & 0xe0) == 0) &&
       (((lhs_type & 4) != 0 && (piVar1 = node->child->next, piVar1->op == IL_CONST)))) {
      shift = power_of_two_index(piVar1->val,0);
      if (shift == 0) {
        return node;
      }
      node->child->next->val = shift + -1;
      node->child->next->type = '\x10';
      node->op = IL_SR;
      return node;
    }
  }
  piVar1 = node->child;
  if (((((piVar1->op == IL_CAST) && ((piVar1->type & 0xe0) == 0)) && (piVar1->child->op == IL_ID))
      && ((lhs_type = piVar1->child->type, (lhs_type & 0xe0) == 0 && ((lhs_type & 4) != 0)))) &&
     ((((lhs_type & 0xf8) == 0 || ((lhs_type & 0xf8) == 8)) &&
      ((piVar1->next->op == IL_CONST &&
       (shift = power_of_two_index(piVar1->next->val,0), shift != 0)))))) {
    node->child->next->val = shift + -1;
    node->child->next->type = '\x10';
    node->op = IL_SR;
  }
  return node;
}



