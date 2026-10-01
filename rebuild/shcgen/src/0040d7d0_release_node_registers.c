#include "decls.h"
#include "imports.h"

// entry: 0040d7d0
// name : release_node_registers
// size : 520
// sig  : void release_node_registers(gen_node * node)


int __cdecl release_node_registers(gen_node *node)

{
  int position;
  gen_node *pgVar1;
  uint uVar2;
  ushort reg_bit;
  ushort freed_mask;
  node_desc *desc;
  ushort *mask_ptr;
  byte reg;
  char *slot;
  ea *value_ea;
  
  freed_mask = 0;
  uVar2 = 0;
  do {
    slot = node->desc->regs_2c + uVar2;
    reg = *slot;
    if (reg != 0xff) {
      if (((char)reg < ' ') && (-1 < (char)reg)) {
        reg_bit = 1 << (reg & 0x1f);
      }
      else {
        reg_bit = 0;
      }
      freed_mask = freed_mask | reg_bit;
    }
    uVar2 = uVar2 + 1;
    *slot = 0xff;
  } while (uVar2 < 5);
  uVar2 = 0;
  do {
    slot = node->desc->regs_34 + uVar2;
    reg = *slot;
    if (reg != 0xff) {
      freed_mask = freed_mask | 1 << (reg & 0x1f);
    }
    uVar2 = uVar2 + 1;
    *slot = 0xff;
  } while (uVar2 < 4);
  uVar2 = 0;
  do {
    slot = node->desc->regs_41 + uVar2;
    reg = *slot;
    if (reg != 0xff) {
      freed_mask = freed_mask | 1 << (reg & 0x1f);
    }
    uVar2 = uVar2 + 1;
    *slot = 0xff;
  } while (uVar2 < 3);
  uVar2 = 0;
  do {
    slot = node->desc->regs_44 + uVar2;
    reg = *slot;
    if (reg != 0xff) {
      freed_mask = freed_mask | 1 << (reg & 0x1f);
    }
    uVar2 = uVar2 + 1;
    *slot = 0xff;
  } while (uVar2 < 2);
  uVar2 = 0;
  do {
    slot = node->desc->regs_3d + uVar2;
    reg = *slot;
    if (reg != 0xff) {
      freed_mask = freed_mask | 1 << (reg & 0x1f);
    }
    uVar2 = uVar2 + 1;
    *slot = 0xff;
  } while (uVar2 < 2);
  uVar2 = 0;
  do {
    slot = node->desc->cond_regs + uVar2;
    reg = *slot;
    if (reg != 0xff) {
      if (((char)reg < ' ') && (-1 < (char)reg)) {
        reg_bit = 1 << (reg & 0x1f);
      }
      else {
        reg_bit = 0;
      }
      freed_mask = freed_mask | reg_bit;
    }
    uVar2 = uVar2 + 1;
    *slot = 0xff;
  } while (uVar2 < 5);
  reg = node->desc->addr_reg;
  if (reg != 0xff) {
    freed_mask = freed_mask | 1 << (reg & 0x1f);
  }
  node->desc->addr_reg = -1;
  reg = node->desc->reg_47;
  if (reg != 0xff) {
    freed_mask = freed_mask | 1 << (reg & 0x1f);
  }
  node->desc->reg_47 = -1;
  position = operand_position(node);
  if (position == 1) {
    pgVar1 = node->parent;
  }
  else {
    position = operand_position(node);
    pgVar1 = nth_operand(node->parent,position + -1);
  }
  node->desc->busy_regs = pgVar1->desc->busy_regs;
  desc = node->desc;
  value_ea = &desc->value;
  if ((value_ea->type & 0x1f) != 0) {
    uVar2 = ea_register_mask(value_ea);
    mask_ptr = &desc->busy_regs;
    *mask_ptr = *mask_ptr | (ushort)uVar2;
  }
  node->desc->temp_regs = 0;
  for (pgVar1 = node->child; pgVar1 != (gen_node *)0x0; pgVar1 = pgVar1->next) {
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | pgVar1->desc->temp_regs;
  }
  g_last_chosen_reg = -1;
  g_avoid_reg_mask = 0;
  invalidate_register_contents((int)(short)freed_mask);
  return;
}



