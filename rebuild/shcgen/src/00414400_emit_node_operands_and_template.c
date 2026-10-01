#include "decls.h"
#include "imports.h"

// entry: 00414400
// name : emit_node_operands_and_template
// size : 671
// sig  : void emit_node_operands_and_template(gen_node * node)


int __cdecl emit_node_operands_and_template(gen_node *node)

{
  unsigned char _frec_21[33];
#define saved_nested_emit (*(char *)(_frec_21 + 0))
#define opnd0 (*(ea * *)(_frec_21 + 5))
#define opnd1 (*(undefined4 *)(_frec_21 + 9))
#define opnd2 (*(undefined4 *)(_frec_21 + 13))
#define opnd3 (*(undefined4 *)(_frec_21 + 17))
#define opnd4 (*(undefined4 *)(_frec_21 + 21))
#define opnd5 (*(undefined4 *)(_frec_21 + 25))
#define opnd6 (*(undefined4 *)(_frec_21 + 29))
  int n;
  short reg;
  int first;
  gen_node *pgVar1;
  ea *peVar2;
  ea *peVar3;
  int step;
  uint reg_bit;
  int iVar4;
  ushort regs_left;
  char cVar5;
  uchar uVar6;
  label_ref *plVar7;
  int addr_index;
  node_desc *desc;
  tmpl_header *tmpl;
  
  desc = node->desc;
  if (((((desc->flags3 & 0x80) == 0) && (desc->tmpl != (tmpl_header *)0x0)) &&
      ((desc->tmpl->flags & 0x80) == 0)) || ((desc->flags3 & 8) != 0)) {
    if ((desc->flags2 & 0x80) == 0) {
      if (node->op == IL_ARG) {
        iVar4 = count_operands(node);
      }
      else {
        iVar4 = count_operands(node);
        iVar4 = iVar4 + 1;
      }
      first = 1;
      step = 1;
    }
    else {
      iVar4 = 0;
      step = -1;
      first = count_operands(node);
    }
    cVar5 = g_nested_operand_emit;
    tmpl = node->desc->tmpl;
    n = first;
    if ((tmpl != (tmpl_header *)0x0) && (tmpl->push_mode != '\0')) {
      g_nested_operand_emit = '\x01';
      saved_nested_emit = cVar5;
    }
    for (; n != iVar4; n = n + step) {
      pgVar1 = nth_operand(node,n);
      emit_node_code(pgVar1);
      if ((n == first) || (node->op == IL_CALL)) {
        if (('7' < (char)node->op) && (addr_index = n, (char)node->op < '>')) goto LAB_004144c7;
      }
      else {
        addr_index = n - step;
LAB_004144c7:
        pgVar1 = nth_operand(node,addr_index);
        load_node_address_register(pgVar1);
      }
    }
    tmpl = node->desc->tmpl;
    if ((tmpl != (tmpl_header *)0x0) && (tmpl->push_mode != '\0')) {
      g_nested_operand_emit = saved_nested_emit;
    }
  }
  desc = node->desc;
  if ((desc->flags3 & 0x80) == 0) {
    if (desc->tmpl == (tmpl_header *)0x0) {
      report_codegen_message(0x11fd,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    else {
      opnd0 = (ea *)0x0;
      opnd1 = 0;
      opnd2 = 0;
      opnd3 = 0;
      opnd4 = 0;
      opnd5 = 0;
      opnd6 = 0;
      regs_left = desc->saved_regs;
      if (regs_left != 0) {
        reg_bit = 0x8000;
        do {
          if ((reg_bit & (int)(short)regs_left) != 0) {
            regs_left = regs_left ^ (ushort)reg_bit;
            pgVar1 = (gen_node *)0x0;
            peVar2 = copy_ea(&g_ea_push);
            plVar7 = (label_ref *)0x0;
            uVar6 = '\0';
            iVar4 = 0;
            cVar5 = -1;
            reg = mask_to_register(reg_bit);
            peVar3 = new_ea_operand_with_flags('\x01',(char)reg,cVar5,iVar4,uVar6,plVar7);
            emit_psd_for_node(0x40,-1,'\0','\x02',peVar3,peVar2,pgVar1);
          }
          reg_bit = (uint)(ushort)((ushort)reg_bit >> 1);
        } while (regs_left != 0);
      }
      desc = node->desc;
      if (((((desc->tmpl->flags & 1) != 0) && ((desc->flags3 & 1) == 0)) &&
          (((desc->dest).type & 0x1f) == 0)) && (desc->target_regs == 0)) {
        g_template_value_unused = 1;
        g_stmt_invalidate_mask = g_stmt_invalidate_mask | 1 << ((node->desc->value).base & 0x1fU);
      }
      emit_template_record_sequence_for_node(node,node->desc->tmpl->entries,&opnd0);
      g_template_value_unused = 0;
      regs_left = node->desc->saved_regs;
      if (regs_left != 0) {
        reg_bit = 1;
        do {
          if ((reg_bit & (int)(short)regs_left) != 0) {
            regs_left = regs_left ^ (ushort)reg_bit;
            pgVar1 = (gen_node *)0x0;
            plVar7 = (label_ref *)0x0;
            uVar6 = '\0';
            iVar4 = 0;
            cVar5 = -1;
            reg = mask_to_register(reg_bit);
            peVar2 = new_ea_operand_with_flags('\x01',(char)reg,cVar5,iVar4,uVar6,plVar7);
            peVar3 = copy_ea(&g_ea_pop);
            emit_psd_for_node(0x40,-1,'\0','\x02',peVar3,peVar2,pgVar1);
          }
          reg_bit = (uint)(ushort)((ushort)reg_bit * 2);
        } while (regs_left != 0);
        return;
      }
    }
  }
  return;
#undef saved_nested_emit
#undef opnd0
#undef opnd1
#undef opnd2
#undef opnd3
#undef opnd4
#undef opnd5
#undef opnd6
}



