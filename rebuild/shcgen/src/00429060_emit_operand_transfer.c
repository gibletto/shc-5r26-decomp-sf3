#include "decls.h"
#include "imports.h"

// entry: 00429060
// name : emit_operand_transfer
// size : 856
// sig  : void emit_operand_transfer(ea * src, ea * dst, uchar rec_flags, gen_node * node, ushort macro, uchar type, uint excluded, uint excluded_retry, int extra)


int __cdecl
emit_operand_transfer
          (ea *src,ea *dst,uchar rec_flags,gen_node *node,ushort macro,uchar type,uint excluded,
          uint excluded_retry,int extra)

{
  byte bVar1;
  short sVar2;
  uint reg_mask;
  ushort uVar3;
  ushort last_regs44_bit;
  tmpl_header *chosen_tmpl;
  
  if (macro == 5) {
    bVar1 = src->type & 0x1f;
    if ((bVar1 == 1) || ((dst != (ea *)0x0 && ((dst->type & 0x1f) == 1)))) {
      if (bVar1 == 1) {
        macro = 0xf00;
      }
      else if ((dst->type & 0x1f) == 1) {
        macro = 0xc00;
      }
    }
    else {
      sVar2 = ea_operands_equal(dst,&g_ea_push);
      if (sVar2 != 0) {
        macro = 0x1500;
      }
    }
  }
  if (((macro == 0xd00) || (macro == 0xe00)) ||
     (((macro == 0xc00 || ((macro == 0x1500 || (macro == 5)))) && ((src->type & 0x40) != 0)))) {
    type = '@';
    if ((macro == 0xc00) || (macro == 5)) {
      macro = 0xd00;
    }
    else if (macro == 0x1500) {
      macro = 0xe00;
    }
  }
  if ((((((macro == 0xc00) || (macro == 0xf00)) || (macro == 0x1c00)) ||
       ((macro == 0xe00 || (macro == 0x2b00)))) || ((macro == 0x2700 || (macro == 0x2800)))) ||
     ((macro == 0xd00 && ((dst->type & 0x1f) == 1)))) {
    if ((dst->type & 0x1f) == 1) {
      bVar1 = dst->base;
      if (((char)bVar1 < ' ') && (-1 < (char)bVar1)) {
        reg_mask = 1 << (bVar1 & 0x1f);
      }
      else {
        reg_mask = (1 << (bVar1 - 0x1f & 0x1f) | 1 << (bVar1 - 0x20 & 0x1f)) << 0x10;
      }
      invalidate_register_contents(reg_mask);
    }
    uVar3 = choose_move_entry_register(src,dst,rec_flags,node,macro,type,excluded,(gen_node *)extra)
    ;
    if (uVar3 == 0) {
      choose_move_entry_register(src,dst,rec_flags,node,macro,type,excluded_retry,(gen_node *)extra)
      ;
    }
  }
  else {
    if (macro == 5) {
      chosen_tmpl = select_move_template(type,src,dst,node);
    }
    else if (macro == 0xd00) {
      chosen_tmpl = select_load_address_template(src,dst);
    }
    else if (macro == 0x1500) {
      chosen_tmpl = select_push_template(type,src,node->desc->usage,node);
    }
    else {
      report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    apply_template_to_node(node,chosen_tmpl,rec_flags,src,dst,excluded,(gen_node *)extra);
  }
  sVar2 = 0;
  uVar3 = 0;
  g_avoid_reg_mask = 0;
  do {
    bVar1 = node->desc->regs_41[sVar2];
    if (bVar1 != 0xff) {
      g_avoid_reg_mask = g_avoid_reg_mask | 1 << (bVar1 & 0x1f);
      uVar3 = 1 << (node->desc->regs_41[sVar2] & 0x1fU);
    }
    sVar2 = sVar2 + 1;
  } while (sVar2 < 3);
  sVar2 = 0;
  last_regs44_bit = 0;
  do {
    bVar1 = node->desc->regs_44[sVar2];
    if (bVar1 != 0xff) {
      g_avoid_reg_mask = g_avoid_reg_mask | 1 << (bVar1 & 0x1f);
      last_regs44_bit = 1 << (node->desc->regs_44[sVar2] & 0x1fU);
    }
    sVar2 = sVar2 + 1;
  } while (sVar2 < 2);
  reg_mask = ea_register_mask(src);
  g_avoid_reg_mask = g_avoid_reg_mask | (ushort)reg_mask;
  reg_mask = ea_register_mask(dst);
  g_avoid_reg_mask = g_avoid_reg_mask | (ushort)reg_mask;
  g_avoid_reg_mask = g_avoid_reg_mask & 0xf;
  if (g_avoid_reg_mask == 0xf) {
    reg_mask = ea_register_mask(src);
    g_avoid_reg_mask = (short)reg_mask;
    reg_mask = ea_register_mask(dst);
    g_avoid_reg_mask = g_avoid_reg_mask | (ushort)reg_mask;
    if (last_regs44_bit != 0) {
      g_avoid_reg_mask = g_avoid_reg_mask | last_regs44_bit;
      return;
    }
    g_avoid_reg_mask = g_avoid_reg_mask | uVar3;
  }
  return;
}



