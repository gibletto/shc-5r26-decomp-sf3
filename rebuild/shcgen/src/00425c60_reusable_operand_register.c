#include "decls.h"
#include "imports.h"

// entry: 00425c60
// name : reusable_operand_register
// size : 767
// sig  : short reusable_operand_register(gen_node * node, ea * extra0, ea * extra1, uint spec, short target_reg, char slot_state)


short __cdecl
reusable_operand_register
          (gen_node *node,ea *extra0,ea *extra1,uint spec,short target_reg,char slot_state)

{
  uchar ea_kind;
  uint source;
  il_op iVar1;
  short reg;
  gen_node *operand;
  byte base_reg;
  node_desc *opnd_desc;
  
  reg = -1;
  source = spec & 0x1c00;
  if (source < 0x801) {
    if (source == 0x800) {
      if (node->child == (gen_node *)0x0) {
        operand = (gen_node *)0x0;
      }
      else {
        operand = node->child->next;
      }
      opnd_desc = operand->desc;
      iVar1 = IL_FILE;
      extra0 = opnd_desc->mem_ea;
      if ((gen_node *)extra0 != (gen_node *)0x0) {
        iVar1 = ((gen_node *)extra0)->op & IL_NON_1F;
      }
      if ((iVar1 == IL_FILE) && (extra0 = &opnd_desc->dest, ((opnd_desc->dest).type & 0x1f) == 0)) {
        if ((opnd_desc->flags2 & 8) == 0) {
          extra0 = &opnd_desc->value;
        }
        else {
          extra0 = &g_ea_pop;
        }
      }
    }
    else {
      extra0 = (ea *)operand;
      if (source == 0x400) {
        iVar1 = IL_FILE;
        operand = node->child;
        opnd_desc = operand->desc;
        extra0 = opnd_desc->mem_ea;
        if ((gen_node *)extra0 != (gen_node *)0x0) {
          iVar1 = ((gen_node *)extra0)->op & IL_NON_1F;
        }
        if ((iVar1 == IL_FILE) && (extra0 = &opnd_desc->dest, ((opnd_desc->dest).type & 0x1f) == 0))
        {
          if ((opnd_desc->flags2 & 8) == 0) {
            extra0 = &opnd_desc->value;
          }
          else {
            extra0 = &g_ea_pop;
          }
        }
      }
    }
  }
  else if (source < 0x1001) {
    if (source == 0x1000) {
      operand = nth_operand(node,4);
      opnd_desc = operand->desc;
      iVar1 = IL_FILE;
      extra0 = opnd_desc->mem_ea;
      if ((gen_node *)extra0 != (gen_node *)0x0) {
        iVar1 = ((gen_node *)extra0)->op & IL_NON_1F;
      }
      if ((iVar1 == IL_FILE) && (extra0 = &opnd_desc->dest, ((opnd_desc->dest).type & 0x1f) == 0)) {
        if ((opnd_desc->flags2 & 8) == 0) {
          extra0 = &opnd_desc->value;
        }
        else {
          extra0 = &g_ea_pop;
        }
      }
    }
    else {
      extra0 = (ea *)operand;
      if (source == 0xc00) {
        operand = nth_operand(node,3);
        opnd_desc = operand->desc;
        iVar1 = IL_FILE;
        extra0 = opnd_desc->mem_ea;
        if ((gen_node *)extra0 != (gen_node *)0x0) {
          iVar1 = ((gen_node *)extra0)->op & IL_NON_1F;
        }
        if ((iVar1 == IL_FILE) && (extra0 = &opnd_desc->dest, ((opnd_desc->dest).type & 0x1f) == 0))
        {
          if ((opnd_desc->flags2 & 8) == 0) {
            extra0 = &opnd_desc->value;
          }
          else {
            extra0 = &g_ea_pop;
          }
        }
      }
    }
  }
  else if (source == 0x1400) {
    operand = (gen_node *)0x0;
  }
  else {
    extra0 = (ea *)operand;
    if (source == 0x1800) {
      operand = (gen_node *)0x0;
      extra0 = extra1;
    }
  }
  if ((operand == (gen_node *)0x0) || (operand->desc->opnd_class != '\0')) {
    if (((spec & 0x400000) == 0) ||
       ((operand == (gen_node *)0x0 || (operand->desc->opnd_class != '\x01')))) {
      ea_kind = ((gen_node *)extra0)->op & IL_NON_1F;
      if ((ea_kind == '\x01') ||
         (((spec & 0x800000) == 0 &&
          (((ea_kind == '\x02' || (ea_kind == '\b')) && ((spec & 0x3000000) == 0)))))) {
        base_reg = ((gen_node *)extra0)->bit_offset;
        reg = (short)(char)base_reg;
        if ((((((0xe < reg) || (reg < 4)) && ((0x1f < reg || (reg < 0x14)))) &&
             ((0x2e < reg || (reg < 0x23)))) ||
            (((('\x0e' < (char)base_reg ||
               ((1 << (base_reg & 0x1f) & (int)(short)~g_var_gpr_mask) == 0)) &&
              ((('\x1f' < (char)base_reg || ((char)base_reg < '\x10')) ||
               ((1 << (base_reg - 0x10 & 0x1f) & (int)(short)~g_var_fpr_mask) == 0)))) &&
             ((('.' < (char)base_reg || ((char)base_reg < ' ')) ||
              (((int)(short)g_var_fpr_mask &
               (1 << (base_reg - 0x1f & 0x1f) | 1 << (base_reg - 0x20 & 0x1f))) != 0)))))) &&
           (((3 < reg || ((char)base_reg < '\0')) || ((g_gpr_contents[reg].flags & 0x80) != 0)))) {
          reg = -1;
        }
      }
    }
    else {
      reg = (short)(char)((gen_node *)extra0)->bit_offset;
    }
  }
  else {
    reg = (short)(char)((gen_node *)extra0)->bit_offset;
  }
  if ((reg != -1) &&
     (((slot_state != '\x02' && (reg == target_reg)) ||
      ((1 << ((byte)reg & 0x1f) & spec & 0xf) != 0)))) {
    reg = -1;
  }
  return reg;
}



