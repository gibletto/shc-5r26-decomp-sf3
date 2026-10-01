#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00404ed0
// name : emit_comparison_node
// size : 1088
// sig  : void emit_comparison_node(gen_node * node)


int __cdecl emit_comparison_node(gen_node *node)

{
  byte bVar1;
  byte bVar2;
  char t_is_value;
  short label;
  ea *peVar3;
  ea *peVar4;
  byte bVar5;
  ushort branch_op;
  bool t_is_value_00;
  char left_is_zero;
  gen_node *right_node;
  node_desc *desc;
  gen_node *left_node;
  il_op op;
  
  left_node = node->child;
  if (left_node == (gen_node *)0x0) {
    right_node = (gen_node *)0x0;
  }
  else {
    right_node = left_node->next;
  }
  op = node->op;
  emit_node_operands_and_template(node);
  desc = node->desc;
  if ((desc->flags3 & 0x80) != 0) {
    return;
  }
  bVar2 = left_node->type;
  bVar1 = bVar2 & 0xe0;
  if (bVar1 != 0x20) {
    if (((((op == IL_LT) || (op == IL_GT)) || (op == IL_LE)) || (op == IL_GE)) &&
       ((((bVar2 & 4) == 0 && (bVar1 != 0x80)) &&
        ((bVar1 != 0x40 &&
         ((left_node->desc->opnd_class == '\x02' && ((left_node->desc->value).disp == 0)))))))) {
      left_is_zero = '\x01';
    }
    else {
      left_is_zero = '\0';
    }
  }
  if (desc->usage == '\x01') {
    bVar2 = right_node->type & 0xf8;
    if (bVar2 == 0x28) {
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(g_request->cpu == 4) & 2;
      }
      if (bVar1 != 0) goto LAB_00404fb9;
    }
    if ((bVar2 == 0x30) && (g_request->cpu == 4)) {
LAB_00404fb9:
      if ((((op == IL_LT) || (op == IL_GT)) && (desc->true_label != 0)) ||
         ((((op == IL_LE || (op == IL_GE)) && (desc->false_label != 0)) ||
          (((op == IL_EQ && (desc->true_label != 0)) || ((op == IL_NE && (desc->false_label != 0))))
          )))) {
        branch_op = 0x25;
      }
      else {
        branch_op = 0x26;
      }
      label = desc->true_label;
      if (label == 0) {
        label = desc->false_label;
      }
      peVar3 = new_label_operand(label);
      emit_psd_for_node(branch_op,node->desc->cond_regs[0],'\0','\x02',peVar3,(ea *)0x0,
                        (gen_node *)0x0);
      return;
    }
    if ((right_node->type & 0xe0) == 0x20) {
      peVar3 = copy_ea((ea *)&g_ea_r0);
      peVar4 = copy_ea(&g_ea_imm0);
      emit_psd_for_node(0x50,-1,'\0','\x02',peVar4,peVar3,(gen_node *)0x0);
      label = node->desc->false_label;
      if (label == 0) {
        label = node->desc->true_label;
        branch_op = 0x26;
      }
      else if ((op == IL_EQ) || (branch_op = 0x25, op == IL_NE)) {
        branch_op = 0x26;
      }
      peVar3 = new_label_operand(label);
      emit_psd_for_node(branch_op,node->desc->cond_regs[0],'\0','\x02',peVar3,(ea *)0x0,
                        (gen_node *)0x0);
      return;
    }
    if (((left_is_zero == '\0') && (desc->true_label != 0)) ||
       ((left_is_zero == '\x01' && (desc->false_label != 0)))) {
      if (((op == IL_EQ) || (op == IL_GT)) || (op == IL_GE)) {
        branch_op = 0x25;
        goto LAB_00405118;
      }
    }
    else if (((op != IL_EQ) && (op != IL_GT)) && (branch_op = 0x25, op != IL_GE)) goto LAB_00405118;
    branch_op = 0x26;
LAB_00405118:
    label = desc->true_label;
    if (label == 0) {
      label = desc->false_label;
    }
    peVar3 = new_label_operand(label);
    emit_psd_for_node(branch_op,node->desc->cond_regs[0],'\0','\x02',peVar3,(ea *)0x0,
                      (gen_node *)0x0);
    return;
  }
  if (desc->usage != '\x02') {
    return;
  }
  if ((bVar2 & 0xf8) == 0x28) {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      bVar5 = 1;
    }
    else {
      bVar5 = -(g_request->cpu == 4) & 2;
    }
    if (bVar5 != 0) goto LAB_004051ad;
  }
  if (((bVar2 & 0xf8) == 0x30) && (g_request->cpu == 4)) {
LAB_004051ad:
    if (((((op == IL_LT) || (op == IL_GT)) && ((desc->true_label != 0 || (desc->false_label == 0))))
        || (((op == IL_LE || (op == IL_GE)) && (desc->false_label != 0)))) ||
       (((op == IL_EQ && ((desc->true_label != 0 || (desc->false_label == 0)))) ||
        ((op == IL_NE && (desc->false_label != 0)))))) {
      t_is_value = '\x01';
    }
    else {
      t_is_value = '\0';
    }
    emit_movt_result(node,t_is_value,&desc->value);
    return;
  }
  if (bVar1 == 0x20) {
    if (desc->false_label == 0) {
      return;
    }
    if ((((op != IL_LT) && (op != IL_GT)) && (op != IL_LE)) && (op != IL_GE)) {
      return;
    }
    peVar3 = copy_ea((ea *)&g_ea_r0);
    emit_psd_for_node(0x42,-1,'\0','\x02',peVar3,(ea *)0x0,(gen_node *)0x0);
    peVar3 = copy_ea(&g_ea_imm1);
    peVar4 = copy_ea((ea *)&g_ea_r0);
    emit_psd_for_node(0x82,-1,'\0','\x02',peVar3,peVar4,(gen_node *)0x0);
    return;
  }
  if (((op == IL_LT) || (op == IL_GT)) || ((op == IL_LE || (op == IL_GE)))) {
    if (((left_is_zero == '\x01') && (desc->false_label != 0)) ||
       ((left_is_zero == '\0' && ((desc->true_label != 0 || (desc->false_label == 0)))))) {
      t_is_value_00 = true;
    }
    else {
      t_is_value_00 = false;
    }
    if ((op != IL_LT) && (op != IL_LE)) goto LAB_004052f7;
  }
  else {
    t_is_value_00 = desc->false_label == 0;
    if (op != IL_NE) goto LAB_004052f7;
  }
  t_is_value_00 = (bool)(t_is_value_00 ^ 1);
LAB_004052f7:
  emit_movt_result(node,t_is_value_00,&desc->value);
  return;
}



