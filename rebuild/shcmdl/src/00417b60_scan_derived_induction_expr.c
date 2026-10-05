#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef _g_iv_negated_count
#define _g_iv_negated_count (*(short *)(g_sd + 0xdf70))
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_iv_cur_block
#define g_iv_cur_block (*(bblock * *)(g_sd + 0xdb64))
#undef g_iv_negated_count
#define g_iv_negated_count (*(short *)(g_sd + 0xdf70))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))


// entry: 00417b60
// name : scan_derived_induction_expr
// size : 842
// sig  : void scan_derived_induction_expr(il_node * node, il_node * copy)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl scan_derived_induction_expr(il_node *node,il_node *copy)

{
  char rank;
  char child_rank;
  byte ty;
  int child_unsigned;
  uint is_zero;
  il_node *operand;
  int iVar1;
  il_node *piVar2;
  int *adjust;
  short first_ivno;
  il_op test_op;
  iv_use *use;
  
  piVar2 = copy->child;
  for (operand = node->child; operand != (il_node *)0x0; operand = operand->next) {
    scan_derived_induction_expr(operand,piVar2);
    piVar2 = piVar2->next;
  }
  switch(node->op) {
  case IL_CAST:
    iVar1 = node_type_rank(node);
    rank = (char)iVar1;
    iVar1 = node_type_rank(node->child);
    if ((((rank < '\x01') || ('\x03' < rank)) || (child_rank = (char)iVar1, child_rank < '\x01')) ||
       ('\x03' < child_rank)) {
      node->ivno = 0;
      return;
    }
    if ((rank == '\x03') || (child_rank < rank)) {
      node->ivno = node->child->ivno;
      return;
    }
    if (child_rank > rank && (IV_RULES() & 1) && ((IV_RULES() & 6) == 0 || (IV_RULES() & (rank == 1 ? 2 : 4)))) {
      node->ivno = node->child->ivno;
      return;
    }
    if (child_rank != rank) {
LAB_00417c21:
      node->ivno = 0;
      return;
    }
    ty = node->type;
    if (((ty & 0xe0) != 0) || ((ty & 4) == 0)) {
      if (((ty & 0xe0) != 0) || (iVar1 = 1, (ty & 4) == 0)) {
        iVar1 = 0;
      }
      ty = node->child->type;
      if (((ty & 0xe0) != 0) || (child_unsigned = 1, (ty & 4) == 0)) {
        child_unsigned = 0;
      }
      if (iVar1 != child_unsigned) goto LAB_00417c21;
    }
    node->ivno = node->child->ivno;
    return;
  default:
    goto switchD_00417ba1_caseD_21;
  case IL_ADD:
  case IL_SUB:
    goto switchD_00417ba1_caseD_40;
  case IL_MUL:
    break;
  case IL_SL:
    ty = node->type & 0xf8;
    if (ty == 0x28) {
      return;
    }
    if (ty == 0x30) {
      return;
    }
    operand = node->child;
    if (operand->ivno == 0) {
      return;
    }
    if (operand->next->op != IL_CONST) {
      return;
    }
    link_derived_induction(node,operand,copy,copy->child);
    operand = node->child->next;
    operand = copy_tree(0,(il_node *)(-(uint)(operand->op == IL_CONST) & (uint)operand));
    iVar1 = shift_to_power_of_two(operand->val);
    operand->val = iVar1;
    piVar2 = (il_node *)((node->child->ivno == 0) - 1 & (uint)node->child);
    if ((operand != (il_node *)0x0) && (piVar2 != (il_node *)0x0)) {
      add_induction_factor(piVar2,operand);
    }
    (g_iv_table[node->ivno].uses)->block = g_iv_cur_block;
    return;
  case IL_ID:
    record_induction_use(node,copy);
    return;
  }
  operand = node->child->next;
  if ((operand->op == IL_CONST) && (is_zero = is_const_value(operand,0,operand->type), is_zero != 0)
     ) {
    *(byte *)&node->flag2 = (byte)node->flag2 | 4;
    *(byte *)&copy->flag2 = (byte)copy->flag2 | 4;
  }
switchD_00417ba1_caseD_40:
  ty = node->type & 0xf8;
  if (ty == 0x28) {
    return;
  }
  if (ty == 0x30) {
    return;
  }
  operand = node->child;
  first_ivno = operand->ivno;
  if (first_ivno == 0) {
LAB_00417cb8:
    if (operand->next->ivno == 0) {
      return;
    }
    if ((short)operand->invno < g_cur_loop->lpnumber) {
      return;
    }
  }
  else {
    if (operand->next->ivno != 0) {
      return;
    }
    if ((first_ivno == 0) || ((short)operand->next->invno < g_cur_loop->lpnumber))
    goto LAB_00417cb8;
  }
  if (first_ivno == 0) {
    operand = operand->next;
  }
  piVar2 = copy->child;
  if (piVar2->ivno == 0) {
    piVar2 = piVar2->next;
  }
  link_derived_induction(node,operand,copy,piVar2);
  if ((node->op == IL_SUB) && (node->child->next->ivno != 0)) {
    use = g_iv_table[node->ivno].uses;
    operand = use->incr;
    if (operand == (il_node *)0x0) {
      operand = make_node(IL_MINUS,node->type,(il_node *)0x0,(il_node *)0x0,(il_node *)0x0);
      use->incr = operand;
    }
    else {
      free_node(operand);
      (g_iv_table[node->ivno].uses)->incr = (il_node *)0x0;
    }
    test_op = g_loop_test->op;
    if ((test_op == IL_LT) || (test_op == IL_LE)) {
      adjust = &(g_iv_table[node->ivno].uses)->test_adjust;
      *adjust = *adjust + 2;
    }
    else if ((test_op == IL_GT) || (test_op == IL_GE)) {
      adjust = &(g_iv_table[node->ivno].uses)->test_adjust;
      *adjust = *adjust + -2;
    }
    _g_iv_negated_count = _g_iv_negated_count + 1;
  }
  if (node->op == IL_MUL) {
    operand = node->child;
    if (operand->ivno == 0) {
      piVar2 = operand->next;
    }
    else {
      piVar2 = operand;
      operand = operand->next;
    }
    add_induction_factor(piVar2,operand);
  }
  (g_iv_table[node->ivno].uses)->block = g_iv_cur_block;
switchD_00417ba1_caseD_21:
  return;
}



