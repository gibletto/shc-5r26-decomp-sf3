#include "decls.h"
#include "imports.h"

// entry: 0040efc0
// name : simplify_mod
// size : 302
// sig  : il_node * simplify_mod(il_node * node)


il_node * __cdecl simplify_mod(il_node *node)

{
  il_node *piVar1;
  uint is_const;
  int shift;
  int *lhs;
  int one;
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
    piVar1 = new_const_node(node->type & 0xfc,0);
    piVar1->filn = filn;
    piVar1->line = line;
    piVar1->listno = listno;
    replace_and_free_node(node,piVar1);
    return piVar1;
  }
  is_const = is_const_value(piVar1->next,1,piVar1->next->type);
  if (is_const == 0) {
    lhs_type = node->child->type;
    if (((lhs_type & 0xe0) != 0) || ((lhs_type & 4) == 0)) {
      piVar1 = node->child->next;
      is_const = is_const_value(piVar1,0xffffffff,piVar1->type);
      if (is_const != 0) goto LAB_0040f0d4;
    }
    lhs_type = node->child->type;
    if ((((lhs_type & 0xe0) == 0) && ((lhs_type & 4) != 0)) &&
       (piVar1 = node->child->next, piVar1->op == IL_CONST)) {
      shift = power_of_two_index(piVar1->val,0);
      if (shift != 0) {
        one = 1;
        lhs = &node->child->next->val;
        fold_sub_unsigned(lhs,&one,lhs);
        node->op = IL_B_AND;
        return node;
      }
    }
  }
  else {
LAB_0040f0d4:
    node->child->next->val = 0;
    node->op = IL_COMMA;
  }
  return node;
}



