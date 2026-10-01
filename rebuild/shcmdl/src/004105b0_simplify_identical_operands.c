#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 004105b0
// name : simplify_identical_operands
// size : 799
// sig  : il_node * simplify_identical_operands(il_node * node)


il_node * __cdecl simplify_identical_operands(il_node *node)

{
  int same;
  il_node *piVar1;
  il_node *second;
  byte ty;
  il_op op;
  il_node *third;
  uint value;
  
  piVar1 = node->child;
  if ((piVar1 == (il_node *)0x0) || (piVar1->next == (il_node *)0x0)) {
    return node;
  }
  op = node->op;
  if (((op & IL_NON_F0) == IL_A_ADD) && (((piVar1->type ^ node->type) & 0xfc) != 0)) {
    return node;
  }
  if ((((node->type & 2) != 0) || ((piVar1->type & 2) != 0)) || ((piVar1->next->type & 2) != 0)) {
    return node;
  }
  if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 4) != 0) {
    dump_tree(node,1,s_str_00435300);
  }
  same = same_common_expression(node->child,node->child->next);
  if ((same == 0) || (same = tree_has_float(node->child), same != 0)) {
    switch(op) {
    case IL_SL:
    case IL_SR:
      piVar1 = node->child;
      if (piVar1->next->cmnexp == (il_node *)0x0) goto switchD_00410663_caseD_42;
      value = is_const_value(piVar1,0,piVar1->type);
      if (value == 0) {
        if (op != IL_SR) goto switchD_00410663_caseD_42;
        ty = node->child->type;
        if ((((ty & 0xe0) == 0) && ((ty & 4) != 0)) ||
           (value = is_const_value(node->child,0xffffffff,ty), value == 0))
        goto switchD_00410663_caseD_42;
      }
      piVar1 = copy_tree(0,node->child->next);
      third = (il_node *)0x0;
      second = copy_tree(0,node->child);
      piVar1 = make_node(IL_COMMA,node->type,piVar1,second,third);
      break;
    default:
      goto switchD_00410663_caseD_42;
    case IL_B_XOR:
    case IL_B_OR:
      piVar1 = node->child;
      if ((piVar1->op != IL_CMPL) ||
         (same = same_common_expression(piVar1->child,piVar1->next), same == 0)) {
        piVar1 = node->child->next;
        if ((piVar1->op != IL_CMPL) ||
           (same = same_common_expression(node->child,piVar1->child), same == 0))
        goto switchD_00410663_caseD_42;
      }
      piVar1 = copy_tree(0,node->child);
      ty = node->type;
      value = 0xffffffff;
      goto LAB_00410856;
    }
    goto LAB_00410891;
  }
  switch(op) {
  case IL_SUB:
  case IL_MOD:
  case IL_NE:
    piVar1 = copy_tree(0,node->child);
    ty = node->type;
    value = 0;
    break;
  default:
    goto switchD_00410663_caseD_42;
  case IL_DIV:
  case IL_EQ:
    piVar1 = copy_tree(0,node->child);
    ty = node->type;
    value = 1;
    break;
  case IL_B_AND:
  case IL_B_OR:
    piVar1 = copy_tree(0,node->child);
    goto LAB_00410891;
  case IL_B_XOR:
    piVar1 = copy_tree(0,node->child);
    ty = node->type;
    value = 0;
    break;
  case IL_A_SUB:
  case IL_A_MOD:
  case IL_A_XOR:
    piVar1 = new_const_node(node->type & 0xfc,0);
    unlink_from_common_expression_chains(node);
    replace_and_free_node(node->child->next,piVar1);
    node->op = IL_ASSIGN;
    goto switchD_00410663_caseD_42;
  case IL_A_DIV:
    piVar1 = new_const_node(node->type & 0xfc,1);
    unlink_from_common_expression_chains(node);
    replace_and_free_node(node->child->next,piVar1);
    node->op = IL_ASSIGN;
    goto switchD_00410663_caseD_42;
  case IL_A_AND:
  case IL_A_OR:
  case IL_ASSIGN:
    piVar1 = copy_tree(0,node->child);
    goto LAB_00410891;
  }
LAB_00410856:
  third = (il_node *)0x0;
  second = new_const_node(ty & 0xfc,value);
  piVar1 = make_node(IL_COMMA,ty,piVar1,second,third);
  piVar1->filn = node->filn;
  piVar1->line = node->line;
  piVar1->listno = node->listno;
LAB_00410891:
  unlink_from_common_expression_chains(node);
  replace_and_free_node(node,piVar1);
  node = piVar1;
switchD_00410663_caseD_42:
  if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 4) != 0) {
    dump_tree(node,1,s_str_004352e4);
  }
  return node;
}



