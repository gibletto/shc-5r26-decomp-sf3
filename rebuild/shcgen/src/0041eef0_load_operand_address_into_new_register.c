#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041eef0
// name : load_operand_address_into_new_register
// size : 683
// sig  : ushort load_operand_address_into_new_register(gen_node * node, gen_node * left, gen_node * right, ushort excluded)


ushort __cdecl
load_operand_address_into_new_register
          (gen_node *node,gen_node *left,gen_node *right,ushort excluded)

{
  byte ea_kind;
  ushort uVar1;
  ushort xfer_excluded;
  uint mask32;
  ea *peVar2;
  int iVar3;
  int *frame_field;
  ushort right_reused;
  ea *op;
  ushort new_mask;
  ushort saved_value_regs;
  ushort right_temp;
  short new_reg;
  node_desc *desc;
  uchar *flags_ptr;
  ushort *mask_ptr;
  
  new_mask = 0;
  if (right == (gen_node *)0x0) {
    right_temp = 0;
  }
  else {
    right_temp = right->desc->temp_regs;
  }
  mask32 = ea_register_mask(&left->desc->value);
  uVar1 = (ushort)mask32;
  desc = left->desc;
  ea_kind = 0;
  peVar2 = desc->saved_ea;
  if (peVar2 != (ea *)0x0) {
    ea_kind = peVar2->type & 0x1f;
  }
  if (ea_kind == 0) {
    saved_value_regs = 0;
  }
  else {
    op = desc->saved_reg_ea;
    ea_kind = 0;
    if (op != (ea *)0x0) {
      ea_kind = op->type & 0x1f;
    }
    if ((ea_kind == 0) && (op = &g_ea_pop, (desc->flags3 & 0x10) == 0)) {
      op = peVar2;
    }
    mask32 = ea_register_mask(op);
    saved_value_regs = (ushort)mask32;
  }
  right_reused = 0;
  mask32 = result_reg_exclusion_mask(node);
  if (right != (gen_node *)0x0) {
    right_reused = right->desc->reused_regs;
  }
  xfer_excluded = right_reused | (ushort)mask32 | saved_value_regs;
  new_reg = choose_general_register
                      (right_temp | excluded | xfer_excluded,left->desc->pref_regs | uVar1,'\0');
  if (new_reg == -1) {
    new_reg = choose_general_register
                        ((ushort)mask32 & 0xfff0 | right_reused | saved_value_regs | right_temp |
                         excluded,left->desc->pref_regs | uVar1,'\0');
  }
  peVar2 = &left->desc->value;
  peVar2->type = peVar2->type | 0x40;
  mask_ptr = &left->desc->busy_regs;
  *mask_ptr = *mask_ptr ^ uVar1;
  if (new_reg == -1) {
    if (((g_request->cpu == 4) || ((left->type & 0xf8) != 0x30)) && ((left->type & 0xe0) != 0x60)) {
      if (right == (gen_node *)0x0) {
LAB_0041f0f5:
        g_stmt_pushed_operand = '\x01';
        uVar1 = 0xe00;
        peVar2 = &g_ea_push;
        flags_ptr = &left->desc->flags2;
        *flags_ptr = *flags_ptr | 8;
        goto LAB_0041f156;
      }
      if (((right->desc->flags2 & 8) == 0) && ((right->type & 0xe0) != 0x60)) {
        iVar3 = call_arguments_use_stack(right);
        if (iVar3 == 0) goto LAB_0041f0f5;
      }
    }
    if (right != (gen_node *)0x0) {
      iVar3 = right->desc->frame_low;
      frame_field = &left->desc->frame_top;
      if (iVar3 < *frame_field) {
        *frame_field = iVar3;
      }
    }
    allocate_temp_frame_slot(left,4,&left->desc->dest);
    frame_field = &node->desc->frame_low;
    iVar3 = left->desc->frame_low;
    if (iVar3 < *frame_field) {
      *frame_field = iVar3;
    }
  }
  else {
    fill_ea(&left->desc->dest,'\x01',(byte)new_reg,-1,'\0',0,(label_ref *)0x0);
    new_mask = 1 << ((byte)new_reg & 0x1f);
    mask_ptr = &left->desc->busy_regs;
    *mask_ptr = *mask_ptr | new_mask;
    g_used_gpr_mask = g_used_gpr_mask | left->desc->busy_regs;
    mask_ptr = &left->desc->temp_regs;
    *mask_ptr = *mask_ptr | new_mask;
    desc = left->desc;
    peVar2 = copy_ea(&desc->dest);
    desc->mem_ea = peVar2;
    peVar2 = left->desc->mem_ea;
    peVar2->type = peVar2->type & 0xf8 | 8;
  }
  uVar1 = 0xd00;
  peVar2 = &left->desc->dest;
LAB_0041f156:
  emit_operand_transfer
            (&left->desc->value,peVar2,'0',left,uVar1,'@',(int)(short)xfer_excluded,
             (int)(short)(right_reused | saved_value_regs),(int)left);
  invalidate_slot_registers(left,'0',right_temp);
  return new_mask;
}



