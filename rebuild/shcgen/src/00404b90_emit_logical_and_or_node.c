#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 00404b90
// name : emit_logical_and_or_node
// size : 507
// sig  : void emit_logical_and_or_node(gen_node * node)


int __cdecl emit_logical_and_or_node(gen_node *node)

{
  uchar size_code;
  short other_label;
  ea *peVar1;
  ea *peVar2;
  short labno;
  gen_node *right_node;
  ea *peVar3;
  node_desc *desc;
  gen_node *left_node;
  
  right_node = (gen_node *)0x0;
  left_node = node->child;
  if (left_node != (gen_node *)0x0) {
    right_node = left_node->next;
  }
  emit_node_code(left_node);
  emit_node_code(right_node);
  desc = node->desc;
  if ((desc->flags3 & 0x80) == 0) {
    if (node->op == IL_OR) {
      labno = left_node->desc->true_label;
      other_label = right_node->desc->false_label;
      peVar2 = &g_ea_imm0;
      peVar3 = &g_ea_imm1;
    }
    else {
      labno = left_node->desc->false_label;
      other_label = right_node->desc->true_label;
      peVar2 = &g_ea_imm1;
      peVar3 = &g_ea_imm0;
    }
    peVar1 = peVar2;
    if (desc->false_label != 0) {
      peVar1 = peVar3;
      peVar3 = peVar2;
    }
    if (desc->usage == '\x01') {
      if (other_label != 0) {
        fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
        emit_psd_record((psd *)&g_psd_scratch,0);
        return;
      }
    }
    else {
      if (desc->usage == '\x02') {
        peVar2 = copy_ea(peVar1);
        peVar1 = copy_ea(&node->desc->value);
        left_node = (gen_node *)0x0;
        size_code = psd_size_code_of_node(node);
        emit_psd_for_node(0x2a,-1,'\0',size_code,peVar2,peVar1,left_node);
        other_label = make_new_label_number();
        peVar2 = new_label_operand(other_label);
        emit_psd_for_node(0x24,node->desc->regs_2c[0],'\0','\x02',peVar2,(ea *)0x0,(gen_node *)0x0);
        fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
        emit_psd_record((psd *)&g_psd_scratch,0);
        peVar3 = copy_ea(peVar3);
        peVar2 = copy_ea(&node->desc->value);
        left_node = (gen_node *)0x0;
        size_code = psd_size_code_of_node(node);
        emit_psd_for_node(0x2a,-1,'\0',size_code,peVar3,peVar2,left_node);
        fill_label_record((psd *)&g_psd_scratch,OP_LABEL,other_label,(short)g_sptravel);
        emit_psd_record((psd *)&g_psd_scratch,0);
        return;
      }
      if (node->parent->op != node->op) {
        fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
        emit_psd_record((psd *)&g_psd_scratch,0);
      }
    }
  }
  return;
}



