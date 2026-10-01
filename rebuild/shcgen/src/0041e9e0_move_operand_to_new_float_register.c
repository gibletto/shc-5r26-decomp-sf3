#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041e9e0
// name : move_operand_to_new_float_register
// size : 685
// sig  : void move_operand_to_new_float_register(gen_node * node, gen_node * left, gen_node * right, short which, ushort excluded)


int __cdecl
move_operand_to_new_float_register
          (gen_node *node,gen_node *left,gen_node *right,short which,ushort excluded)

{
  short new_reg;
  uint mask32;
  byte ea_kind;
  int *frame_field;
  ea *peVar1;
  ushort uVar2;
  uint excluded_retry;
  gen_node *other_opnd;
  uint xfer_excluded;
  node_desc *desc;
  uchar *flags_ptr;
  int low;
  ushort *mask_ptr;
  
  mask32 = result_reg_exclusion_mask(node);
  if (which == 0) {
    other_opnd = right;
    desc = right->desc;
    excluded = excluded | desc->ftemp_regs | desc->freused_regs;
    frame_field = &left->desc->frame_top;
    excluded_retry = (int)(short)desc->reused_regs | (int)(short)desc->freused_regs << 0x10;
    xfer_excluded = excluded_retry | mask32;
    if (desc->frame_low < *frame_field) {
      *frame_field = desc->frame_low;
    }
  }
  else {
    other_opnd = left;
    desc = left->desc;
    ea_kind = 0;
    peVar1 = desc->mem_ea;
    if (peVar1 != (ea *)0x0) {
      ea_kind = peVar1->type & 0x1f;
    }
    if (((ea_kind == 0) && (peVar1 = &desc->dest, (peVar1->type & 0x1f) == 0)) &&
       (peVar1 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      peVar1 = &desc->value;
    }
    excluded_retry = ea_register_mask(peVar1);
    excluded = excluded | (ushort)(excluded_retry >> 0x10);
    xfer_excluded = excluded_retry | mask32;
    left = right;
  }
  uVar2 = (ushort)(mask32 >> 0x10);
  if ((g_request->cpu == 4) && ((left->type & 0xf8) == 0x30)) {
    new_reg = choose_float_register_pair(excluded | uVar2,left->desc->fpref_regs);
    if (new_reg != -1) goto LAB_0041eb44;
    new_reg = choose_float_register_pair(uVar2 & 0xfff0 | excluded,left->desc->fpref_regs);
LAB_0041eb38:
    if (new_reg != -1) goto LAB_0041eb44;
    if (((other_opnd->desc->flags2 & 8) == 0) && ((other_opnd->desc->flags3 & 0x10) == 0)) {
      g_stmt_pushed_operand = '\x01';
      uVar2 = 0x1500;
      peVar1 = &g_ea_push;
      flags_ptr = &left->desc->flags2;
      *flags_ptr = *flags_ptr | 8;
      goto LAB_0041ebeb;
    }
    allocate_temp_frame_slot(left,4,&left->desc->dest);
    frame_field = &node->desc->frame_low;
    low = left->desc->frame_low;
    if (low < *frame_field) {
      *frame_field = low;
    }
    uVar2 = 5;
  }
  else {
    new_reg = choose_float_register(excluded | uVar2,left->desc->fpref_regs);
    if (new_reg == -1) {
      new_reg = choose_float_register(uVar2 & 0xfff0 | excluded,left->desc->fpref_regs);
      goto LAB_0041eb38;
    }
LAB_0041eb44:
    fill_ea(&left->desc->dest,'\x01',(char)new_reg,-1,'\0',0,(label_ref *)0x0);
    uVar2 = 1 << ((char)new_reg - 0x10U & 0x1f);
    mask_ptr = &left->desc->fbusy_regs;
    *mask_ptr = *mask_ptr | uVar2;
    g_used_fpr_mask = g_used_fpr_mask | left->desc->fbusy_regs;
    mask_ptr = &left->desc->ftemp_regs;
    *mask_ptr = *mask_ptr | uVar2;
    uVar2 = 0xc00;
  }
  peVar1 = &left->desc->dest;
LAB_0041ebeb:
  emit_operand_transfer
            (&left->desc->value,peVar1,'0',left,uVar2,left->type,xfer_excluded,excluded_retry,
             (int)left);
  if (which == 0) {
    invalidate_slot_registers(left,'0',other_opnd->desc->temp_regs);
  }
  desc = left->desc;
  mask32 = ea_register_mask(&desc->value);
  mask_ptr = &desc->fbusy_regs;
  *mask_ptr = *mask_ptr ^ (ushort)(mask32 >> 0x10);
  if (new_reg == -1) {
    left->desc->opnd_class = '\x03';
    return;
  }
  if ((1 << ((char)new_reg - 0x10U & 0x1f) & (int)(short)~g_var_fpr_mask) != 0) {
    left->desc->opnd_class = '\0';
    return;
  }
  left->desc->opnd_class = '\x01';
  return;
}



