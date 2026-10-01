#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00404830
// name : prepare_constant_node
// size : 751
// sig  : void prepare_constant_node(gen_node * node)


int __cdecl prepare_constant_node(gen_node *node)

{
  byte bVar1;
  short reg;
  label_ref *ref;
  int position;
  int operand_count;
  ushort reg_bit;
  int iVar2;
  uchar type;
  int saved_hit;
  node_desc *first_desc;
  uchar *flags_p;
  gen_node *parent;
  tmpl_header *parent_tmpl;
  ushort *regs_p;
  
  bVar1 = node->type & 0xf8;
  if ((bVar1 == 0x40) && (node->val2 != 0)) {
    node->desc->opnd_class = '\x03';
    ref = alloc_zeroed(8);
    fill_ea(&node->desc->value,'\a',-1,-1,'\0',node->val,ref);
    ((node->desc->value).labels)->labno1 = (short)node->val2 + 0xb6;
  }
  else {
    if (bVar1 == 0x30) {
      ref = (label_ref *)node->val2;
      iVar2 = node->val;
      type = '\x0e';
    }
    else {
      ref = (label_ref *)0x0;
      iVar2 = node->val;
      type = '\a';
    }
    fill_ea(&node->desc->value,type,-1,-1,'\0',iVar2,ref);
    node->desc->opnd_class = '\x02';
  }
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 0x80;
  iVar2 = g_content_hit;
  parent = node->parent;
  saved_hit = g_content_hit;
  reg = find_register_holding_constant(&node->desc->value,node->type);
  position = operand_position(node);
  if (((parent->desc != (node_desc *)0x0) && (reg != -1)) && ((node->desc->flags7 & 0x40) == 0)) {
    parent_tmpl = parent->desc->tmpl;
    if (parent_tmpl != (tmpl_header *)0x0) {
      if ((position == 1) && ((parent_tmpl->flags2 & 0x40) != 0)) {
        g_content_hit = iVar2;
        return;
      }
      if ((position == 2) && ((parent_tmpl->flags2 & 0x20) != 0)) {
        g_content_hit = iVar2;
        return;
      }
      if (((parent_tmpl->flags2 & 0x10) != 0) &&
         (operand_count = count_operands(parent), operand_count - position == 1)) {
        g_content_hit = iVar2;
        return;
      }
    }
    if (position == 2) {
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(g_request->cpu == 4) & 2;
      }
      if (((bVar1 == 0) || ((node->type & 0xf8) != 0x28)) &&
         ((parent->op == IL_ADD || (parent->op == IL_SUB)))) {
        first_desc = parent->child->desc;
        bVar1 = (first_desc->value).type & 0x1f;
        if ((bVar1 == 7) && ((first_desc->value).labels != (label_ref *)0x0)) {
          g_content_hit = iVar2;
          return;
        }
        if (bVar1 == 1) {
          g_content_hit = iVar2;
          return;
        }
      }
    }
    saved_hit = g_content_hit;
    iVar2 = (int)reg;
    bVar1 = (byte)reg;
    fill_ea(&node->desc->value,'\x01',bVar1,-1,'\0',0,(label_ref *)0x0);
    if (((reg < 0x10) || (0x13 < reg)) ||
       (((&g_fpr_contents_flags_by_reg)[iVar2 * 0x18] & 0x80) == 0)) {
      if (((reg < 0) || (3 < reg)) || ((g_gpr_contents[iVar2].flags & 0x80) == 0)) {
        node->desc->opnd_class = '\0';
        if ((reg < 0x10) || (0x13 < reg)) {
          reg_bit = 1 << (bVar1 & 0x1f);
          regs_p = &node->desc->busy_regs;
          *regs_p = *regs_p | reg_bit;
          g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
          regs_p = &node->desc->temp_regs;
          *regs_p = *regs_p | reg_bit;
          g_gpr_contents[iVar2].flags = g_gpr_contents[iVar2].flags | 0x80;
        }
        else {
          reg_bit = 1 << (bVar1 - 0x10 & 0x1f);
          regs_p = &node->desc->fbusy_regs;
          *regs_p = *regs_p | reg_bit;
          g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
          regs_p = &node->desc->ftemp_regs;
          *regs_p = *regs_p | reg_bit;
          (&g_fpr_contents_flags_by_reg)[iVar2 * 0x18] =
               (&g_fpr_contents_flags_by_reg)[iVar2 * 0x18] | 0x80;
        }
      }
      else {
        node->desc->opnd_class = '\x01';
        regs_p = &node->desc->busy_regs;
        *regs_p = *regs_p | 1 << (bVar1 & 0x1f);
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
      }
    }
    else {
      node->desc->opnd_class = '\x01';
      regs_p = &node->desc->fbusy_regs;
      *regs_p = *regs_p | 1 << (bVar1 - 0x10 & 0x1f);
      g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
    }
    regs_p = &node->desc->reused_regs;
    *regs_p = *regs_p | 1 << (bVar1 & 0x1f);
    regs_p = &node->desc->freused_regs;
    *regs_p = *regs_p | 1 << (bVar1 - 0x10 & 0x1f);
  }
  g_content_hit = saved_hit;
  return;
}



