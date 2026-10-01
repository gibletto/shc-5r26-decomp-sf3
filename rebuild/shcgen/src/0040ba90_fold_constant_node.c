#include "decls.h"
#include "imports.h"

// entry: 0040ba90
// name : fold_constant_node
// size : 483
// sig  : void fold_constant_node(gen_node * node)


int __cdecl fold_constant_node(gen_node *node)

{
  il_op op;
  gen_node *left;
  short status;
  int msgno;
  gen_node *right;
  int fold_status;
  node_desc *desc;
  uchar *flags_ptr;
  
  right = (gen_node *)0x0;
  left = node->child;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  op = node->op;
  switch(op) {
  case IL_CAST:
    status = fold_constant_cast(node,left,node);
    break;
  default:
    report_codegen_message(0x1220,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    goto LAB_0040bb59;
  case IL_PLUS:
  case IL_MINUS:
  case IL_CMPL:
    status = fold_constant_unary(op,left,node);
    break;
  case IL_NOT:
    status = fold_constant_not(left,node);
    break;
  case IL_ADD:
  case IL_SUB:
  case IL_MUL:
  case IL_DIV:
  case IL_MOD:
    status = fold_constant_arithmetic(op,left,right,node);
    break;
  case IL_SL:
  case IL_SR:
  case IL_B_AND:
  case IL_B_XOR:
  case IL_B_OR:
    status = fold_constant_bitwise(op,left,right,node);
    break;
  case IL_EQ:
  case IL_NE:
  case IL_LT:
  case IL_LE:
  case IL_GT:
  case IL_GE:
    status = fold_constant_comparison(op,left,right,node);
    break;
  case IL_AND:
  case IL_OR:
    status = fold_constant_logical(op,left,right,node);
  }
  fold_status = (int)status;
LAB_0040bb59:
  if (fold_status != 0) {
    if (fold_status == 1) {
      msgno = 0x4b1;
    }
    else if (fold_status == 4) {
      msgno = 0x4b0;
    }
    else if (fold_status == 6) {
      msgno = 0x9c5;
    }
    else {
      msgno = 0;
    }
    if (msgno != 0) {
      report_codegen_message(msgno,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
  }
  flags_ptr = &node->desc->flags3;
  *flags_ptr = *flags_ptr | 0x80;
  desc = node->desc;
  if ((((desc->flags2 & 0x40) != 0) || (desc->cached_regs != 0)) || (desc->fcached_regs != 0)) {
    desc->flags3 = desc->flags3 | 8;
  }
  if ((node->op == IL_AND) || (node->op == IL_OR)) {
    left->desc->usage = '\0';
    right->desc->usage = '\0';
  }
  node->desc->opnd_class = '\x02';
  if ((node->type & 0xf8) == 0x30) {
    flags_ptr = &left->desc->flags2;
    *flags_ptr = *flags_ptr & 0xf7;
    if (right != (gen_node *)0x0) {
      flags_ptr = &right->desc->flags2;
      *flags_ptr = *flags_ptr & 0xf7;
    }
    desc = node->desc;
    fill_ea(&desc->value,'\x0e',-1,-1,'\0',(desc->value).disp,(desc->value).labels);
    return;
  }
  if ((((left->type & 0xf8) == 0x30) &&
      (flags_ptr = &left->desc->flags2, *flags_ptr = *flags_ptr & 0xf7, right != (gen_node *)0x0))
     && ((right->type & 0xf8) == 0x30)) {
    flags_ptr = &right->desc->flags2;
    *flags_ptr = *flags_ptr & 0xf7;
  }
  fill_ea(&node->desc->value,'\a',-1,-1,'\0',(node->desc->value).disp,(label_ref *)0x0);
  return;
}



