#include "decls.h"
#include "imports.h"

// entry: 0041e740
// name : move_operand_to_new_general_register
// size : 670
// sig  : void move_operand_to_new_general_register(gen_node * node, gen_node * left, gen_node * right, short which, ushort excluded)


int __cdecl
move_operand_to_new_general_register
          (gen_node *node,gen_node *left,gen_node *right,short which,ushort excluded)

{
  uint mask32;
  byte bVar1;
  ea *peVar2;
  ushort uVar3;
  int *frame_field;
  ushort keep_regs;
  ushort xfer_excluded;
  ea *op;
  gen_node *moved;
  short new_reg;
  node_desc *desc;
  uchar *flags_ptr;
  int low;
  ushort *mask_ptr;
  
  mask32 = result_reg_exclusion_mask(node);
  uVar3 = (ushort)mask32;
  if (which == 0) {
    desc = right->desc;
    keep_regs = desc->reused_regs;
    frame_field = &left->desc->frame_top;
    xfer_excluded = uVar3 | keep_regs;
    excluded = excluded | desc->temp_regs | keep_regs;
    moved = left;
    if (desc->frame_low < *frame_field) {
      *frame_field = desc->frame_low;
    }
  }
  else {
    bVar1 = 0;
    desc = left->desc;
    peVar2 = desc->mem_ea;
    if (peVar2 != (ea *)0x0) {
      bVar1 = peVar2->type & 0x1f;
    }
    if (((bVar1 == 0) && (peVar2 = &desc->dest, (peVar2->type & 0x1f) == 0)) &&
       (peVar2 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      peVar2 = &desc->value;
    }
    mask32 = ea_register_mask(peVar2);
    keep_regs = (ushort)mask32;
    desc = left->desc;
    bVar1 = 0;
    peVar2 = desc->saved_ea;
    if (peVar2 != (ea *)0x0) {
      bVar1 = peVar2->type & 0x1f;
    }
    if (bVar1 != 0) {
      op = desc->saved_reg_ea;
      bVar1 = 0;
      if (op != (ea *)0x0) {
        bVar1 = op->type & 0x1f;
      }
      if ((bVar1 == 0) && (op = &g_ea_pop, (desc->flags3 & 0x10) == 0)) {
        op = peVar2;
      }
      mask32 = ea_register_mask(op);
      keep_regs = keep_regs | (ushort)mask32;
    }
    xfer_excluded = keep_regs | uVar3;
    excluded = excluded | keep_regs;
    moved = right;
    right = left;
  }
  new_reg = choose_general_register(excluded | uVar3,moved->desc->pref_regs,'\0');
  if (new_reg == -1) {
    new_reg = choose_general_register(uVar3 & 0xfff0 | excluded,moved->desc->pref_regs,'\0');
  }
  bVar1 = (byte)new_reg;
  if (new_reg == -1) {
    if (((right->desc->flags2 & 8) == 0) && ((right->desc->flags3 & 0x10) == 0)) {
      g_stmt_pushed_operand = '\x01';
      uVar3 = 0x1500;
      peVar2 = &g_ea_push;
      flags_ptr = &moved->desc->flags2;
      *flags_ptr = *flags_ptr | 8;
      goto LAB_0041e93e;
    }
    allocate_temp_frame_slot(moved,4,&moved->desc->dest);
    frame_field = &node->desc->frame_low;
    low = moved->desc->frame_low;
    if (low < *frame_field) {
      *frame_field = low;
    }
    uVar3 = 5;
  }
  else {
    fill_ea(&moved->desc->dest,'\x01',bVar1,-1,'\0',0,(label_ref *)0x0);
    uVar3 = 1 << (bVar1 & 0x1f);
    mask_ptr = &moved->desc->busy_regs;
    *mask_ptr = *mask_ptr | uVar3;
    g_used_gpr_mask = g_used_gpr_mask | moved->desc->busy_regs;
    mask_ptr = &moved->desc->temp_regs;
    *mask_ptr = *mask_ptr | uVar3;
    uVar3 = 0xc00;
  }
  peVar2 = &moved->desc->dest;
LAB_0041e93e:
  emit_operand_transfer
            (&moved->desc->value,peVar2,'0',moved,uVar3,moved->type,(int)(short)xfer_excluded,
             (int)(short)keep_regs,(int)moved);
  if (which == 0) {
    invalidate_slot_registers(moved,'0',right->desc->temp_regs);
  }
  desc = moved->desc;
  mask32 = ea_register_mask(&desc->value);
  mask_ptr = &desc->busy_regs;
  *mask_ptr = *mask_ptr ^ (ushort)mask32;
  if (new_reg == -1) {
    moved->desc->opnd_class = '\x03';
    return;
  }
  if ((1 << (bVar1 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0) {
    moved->desc->opnd_class = '\0';
    return;
  }
  moved->desc->opnd_class = '\x01';
  return;
}



