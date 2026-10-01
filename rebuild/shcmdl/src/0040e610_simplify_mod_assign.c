#include "decls.h"
#include "imports.h"

// entry: 0040e610
// name : simplify_mod_assign
// size : 274
// sig  : il_node * simplify_mod_assign(il_node * node)


il_node * __cdecl simplify_mod_assign(il_node *node)

{
  unsigned char _frec_4[4];
#define one (*(int *)(_frec_4 + 0))
  uint is_const;
  int shift;
  int *lhs;
  il_node *piVar1;
  byte lhs_type;
  il_node *rhs;
  
  piVar1 = node->child;
  if (((((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) &&
       (rhs = piVar1->next, rhs->op == IL_ID)) &&
      (((rhs->type & 2) == 0 && (rhs->symx == piVar1->symx)))) ||
     ((is_const = is_const_value(piVar1->next,1,piVar1->next->type), is_const != 0 ||
      ((((node->type & 0xe0) != 0 || ((node->type & 4) == 0)) &&
       (piVar1 = node->child->next, is_const = is_const_value(piVar1,0xffffffff,piVar1->type),
       is_const != 0)))))) {
    if ((node->child->flag & 0x40) == 0) {
      piVar1 = new_const_node(node->type & 0xfc,0);
      replace_and_free_node(node->child->next,piVar1);
      node->op = IL_ASSIGN;
    }
    return node;
  }
  lhs_type = node->child->type;
  if ((lhs_type & 0xe0) != 0) {
    return node;
  }
  if ((lhs_type & 4) == 0) {
    return node;
  }
  if ((node->type & 0xe0) != 0) {
    return node;
  }
  if ((node->type & 4) == 0) {
    return node;
  }
  piVar1 = node->child->next;
  if (piVar1->op != IL_CONST) {
    return node;
  }
  shift = power_of_two_index(piVar1->val,0);
  if (shift == 0) {
    return node;
  }
  one = 1;
  lhs = &node->child->next->val;
  fold_sub_unsigned(lhs,&one,lhs);
  node->op = IL_A_AND;
  return node;
#undef one
}



