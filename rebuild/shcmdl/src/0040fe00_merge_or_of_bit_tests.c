#include "decls.h"
#include "imports.h"

// entry: 0040fe00
// name : merge_or_of_bit_tests
// size : 676
// sig  : il_node * merge_or_of_bit_tests(il_node * node)


il_node * __cdecl merge_or_of_bit_tests(il_node *node)

{
  il_op bitop;
  il_node *piVar1;
  il_node *piVar2;
  il_node *lhs_var;
  uchar type;
  il_node *rhs_var;
  il_node *rhs_inner;
  
  piVar1 = node->child;
  piVar2 = piVar1->next;
  lhs_var = piVar1->child;
  if (lhs_var == (il_node *)0x0) {
    return node;
  }
  rhs_inner = piVar2->child;
  if (((((rhs_inner == (il_node *)0x0) || (lhs_var->op != IL_ID)) || ((lhs_var->type & 2) != 0)) ||
      ((rhs_inner->op != IL_ID || ((rhs_inner->type & 2) != 0)))) ||
     (rhs_inner->symx != lhs_var->symx)) {
    if (lhs_var == (il_node *)0x0) {
      return node;
    }
    rhs_var = piVar2->child;
    if (rhs_var == (il_node *)0x0) {
      return node;
    }
    if ((piVar1->op == IL_NOT) && (lhs_var->op == IL_NOT)) {
      piVar1 = lhs_var->child;
      lhs_var = piVar1->child;
    }
    if ((piVar2->op == IL_NOT) && (rhs_var->op == IL_NOT)) {
      piVar2 = rhs_var->child;
      rhs_var = piVar2->child;
    }
    bitop = common_bitop_pair(piVar1,piVar2);
    if (bitop == IL_FILE) {
      return node;
    }
    if (bitop != IL_B_AND) {
      return node;
    }
    if (lhs_var == (il_node *)0x0) {
      return node;
    }
    if (rhs_var == (il_node *)0x0) {
      return node;
    }
    if (lhs_var->op != IL_ID) {
      return node;
    }
    if ((lhs_var->type & 2) != 0) {
      return node;
    }
    if (rhs_var->op != IL_ID) {
      return node;
    }
    if ((rhs_var->type & 2) != 0) {
      return node;
    }
    if (rhs_var->symx != lhs_var->symx) {
      return node;
    }
    piVar1 = piVar1->child->next;
    if (piVar1->op != IL_CONST) {
      return node;
    }
    if (piVar2->child->next->op != IL_CONST) {
      return node;
    }
    piVar1 = copy_tree(0,piVar1);
    piVar2 = copy_tree(0,piVar2->child->next);
    piVar1 = make_node(IL_B_OR,node->child->next->type,piVar1,piVar2,(il_node *)0x0);
    piVar2 = copy_tree(0,lhs_var);
    type = node->child->next->type;
    bitop = IL_B_AND;
  }
  else {
    bitop = common_bitop_pair(piVar1,piVar2);
    if (bitop == IL_FILE) {
      return node;
    }
    piVar1 = piVar1->child->next;
    if (piVar1->op != IL_CONST) {
      return node;
    }
    if (piVar2->child->next->op != IL_CONST) {
      return node;
    }
    piVar1 = copy_tree(0,piVar1);
    piVar2 = copy_tree(0,piVar2->child->next);
    piVar1 = make_node(IL_B_OR,node->child->type,piVar1,piVar2,(il_node *)0x0);
    piVar2 = copy_tree(0,node->child->child);
    if (bitop == IL_B_OR) {
      replace_and_free_node(node->child,piVar2);
      replace_and_free_node(node->child->next,piVar1);
      piVar1 = fold_constants(piVar1);
      node->child->next = piVar1;
      return node;
    }
    type = node->child->type;
  }
  piVar2 = make_node(bitop,type,piVar2,piVar1,(il_node *)0x0);
  piVar1 = fold_constants(piVar1);
  piVar2->child->next = piVar1;
  piVar1 = make_node(IL_NOT,node->type,piVar2,(il_node *)0x0,(il_node *)0x0);
  piVar1 = make_node(IL_NOT,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
  replace_and_free_node(node,piVar1);
  return piVar1;
}



