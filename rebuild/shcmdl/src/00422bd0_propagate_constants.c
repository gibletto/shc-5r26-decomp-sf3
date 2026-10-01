#include "decls.h"
#include "imports.h"

// entry: 00422bd0
// name : propagate_constants
// size : 889
// sig  : il_node * propagate_constants(il_node * node)


il_node * __cdecl propagate_constants(il_node *node)

{
  int iVar1;
  il_node *constant;
  il_node *copy;
  il_node *operand;
  il_op op;
  uint value;
  il_node *assign_node;
  bool all_const;
  bool split;
  
  split = false;
  switch(node->op) {
  case IL_ADD:
  case IL_MUL:
  case IL_B_AND:
  case IL_B_XOR:
  case IL_B_OR:
  case IL_EQ:
  case IL_NE:
  case IL_LT:
  case IL_LE:
  case IL_GT:
  case IL_GE:
  case IL_ARG:
    operand = node->child;
    if (operand != (il_node *)0x0) {
      do {
        constant = find_constant_value(operand);
        if (constant != (il_node *)0x0) {
          value = constant->val;
          iVar1 = operand_index(operand);
          iVar1 = is_immediate_operand(node,iVar1,value);
          if (iVar1 != 0) {
            operand = overwrite_with_constant(operand,constant);
          }
        }
        operand = operand->next;
      } while (operand != (il_node *)0x0);
      goto LAB_00422d29;
    }
    break;
  case IL_SUB:
  case IL_SL:
  case IL_SR:
  case IL_A_ADD:
  case IL_A_SUB:
  case IL_A_MUL:
  case IL_A_SL:
  case IL_A_SR:
  case IL_A_AND:
  case IL_A_XOR:
  case IL_A_OR:
  case IL_ASSIGN:
    operand = node->child->next;
    constant = find_constant_value(operand);
    if ((constant != (il_node *)0x0) &&
       (iVar1 = is_immediate_operand(node,2,constant->val), iVar1 != 0)) {
      overwrite_with_constant(operand,constant);
    }
    goto LAB_00422d29;
  case IL_DIV:
  case IL_MOD:
  case IL_A_DIV:
  case IL_A_MOD:
    operand = node->child->next;
    constant = find_constant_value(operand);
    if ((constant != (il_node *)0x0) &&
       (iVar1 = is_immediate_operand(node,2,constant->val), iVar1 != 0)) {
      overwrite_with_constant(operand,constant);
    }
    goto LAB_00422d29;
  case IL_ID:
    op = node->parent->op;
    if (((((op == IL_IF) && (iVar1 = operand_index(node), iVar1 == 1)) || (op == IL_RETURN)) ||
        (((op == IL_WHILE || (op == IL_DO)) && (iVar1 = operand_index(node), iVar1 == 2)))) ||
       ((op == IL_FOR && (iVar1 = operand_index(node), iVar1 == 4)))) {
      constant = find_constant_value(node);
      if (constant != (il_node *)0x0) {
        overwrite_with_constant(node,constant);
      }
      goto LAB_00422d29;
    }
  }
  constant = assign_node;
LAB_00422d29:
  op = node->op;
  if (((('O' < (char)op) && ((char)op < '_')) &&
      ((node->child->next->op == IL_CONST ||
       ((constant != (il_node *)0x0 && (constant->op == IL_CONST)))))) &&
     (constant = find_constant_value(node->child), constant != (il_node *)0x0)) {
    operand = node->child->next;
    if (operand->op == IL_ID) {
      copy = find_constant_value(operand);
      overwrite_with_constant(operand,copy);
    }
    copy = copy_tree(1,node);
    copy->op = copy->op - IL_SWITCH;
    operand = node->child->next;
    insert_parent(operand,copy);
    copy = copy_tree(1,node->child);
    constant = overwrite_with_constant(copy,constant);
    constant->cmnexp = constant;
    node->op = IL_ASSIGN;
    insert_before(operand,constant);
    if (node->child->type != node->type) {
      copy = new_node(IL_CAST,node->type);
      insert_parent(constant,copy);
      constant = propagate_constants(copy);
      constant->cmnexp = constant;
    }
    if (node->child->type != operand->type) {
      copy = new_node(IL_CAST,operand->type);
      insert_parent(constant,copy);
      propagate_constants(copy);
      node->child->next->type = operand->type;
      constant = node->child;
      operand = propagate_constants(constant->next);
      constant->next = operand;
      constant = new_node(IL_CAST,node->type);
      insert_parent(node->child->next,constant);
    }
    assign_node = node;
    node = node->child->next;
    split = true;
    op = node->op;
  }
  if (((('\x1f' < (char)op) && ((char)op < '.')) || (('?' < (char)op && ((char)op < 'O')))) ||
     (('_' < (char)op && ((char)op < 'j')))) {
    all_const = true;
    for (constant = node->child; constant != (il_node *)0x0; constant = constant->next) {
      operand = find_constant_value(constant);
      if ((operand == (il_node *)0x0) && (constant->op != IL_CONST)) {
        all_const = false;
        break;
      }
    }
    if (all_const) {
      for (constant = node->child; constant != (il_node *)0x0; constant = constant->next) {
        if (constant->op != IL_CONST) {
          operand = find_constant_value(constant);
          constant = overwrite_with_constant(constant,operand);
        }
      }
      constant = copy_tree(0,node);
      operand = fold_constants(constant);
      if (operand != constant) {
        unlink_from_common_expression_chains(node);
      }
      free_tree(operand);
      node = fold_constants(node);
    }
  }
  if (split) {
    node = assign_node;
  }
  return node;
}



