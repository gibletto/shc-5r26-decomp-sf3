#include "decls.h"
#include "imports.h"

// entry: 0041ec90
// name : move_saved_value_to_new_register
// size : 603
// sig  : ushort move_saved_value_to_new_register(gen_node * node, gen_node * left, gen_node * right, ushort excluded)


ushort __cdecl move_saved_value_to_new_register(gen_node *node,gen_node *left,gen_node *right,ushort excluded)

{
  ushort value_regs;
  ushort result_excl;
  short new_reg;
  uint mask32;
  ea *peVar1;
  uint excl32;
  int *frame_field;
  byte ea_kind;
  ushort macro;
  ushort new_mask;
  node_desc *desc;
  uchar *flags_ptr;
  int low;
  bool lower_top;
  ushort *mask_ptr;
  ushort right_reused;
  
  new_mask = 0;
  mask32 = ea_register_mask(&left->desc->value);
  desc = left->desc;
  ea_kind = 0;
  value_regs = (ushort)mask32;
  peVar1 = desc->mem_ea;
  if (peVar1 != (ea *)0x0) {
    ea_kind = peVar1->type & 0x1f;
  }
  if (((ea_kind == 0) && (peVar1 = &desc->dest, (peVar1->type & 0x1f) == 0)) &&
     (peVar1 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    peVar1 = &desc->value;
  }
  mask32 = ea_register_mask(peVar1);
  excl32 = result_reg_exclusion_mask(node);
  result_excl = (ushort)excl32;
  right_reused = right->desc->reused_regs;
  new_reg = choose_general_register
                      (result_excl | (ushort)mask32 | value_regs | excluded | right_reused,
                       left->desc->pref_regs,'\0');
  if (new_reg == -1) {
    new_reg = choose_general_register
                        (result_excl & 0xfff0 | (ushort)mask32 | value_regs | excluded |
                         right_reused,left->desc->pref_regs,'\0');
    if (new_reg == -1) {
      if ((right == (gen_node *)0x0) || ((right->desc->flags2 & 8) == 0)) {
        g_stmt_pushed_operand = '\x01';
        macro = 0x1500;
        peVar1 = &g_ea_push;
        flags_ptr = &left->desc->flags3;
        *flags_ptr = *flags_ptr | 0x10;
      }
      else {
        peVar1 = alloc_zeroed(0xc);
        left->desc->saved_reg_ea = peVar1;
        if (right == (gen_node *)0x0) {
          lower_top = false;
        }
        else {
          lower_top = true;
          if (left->desc->frame_top <= right->desc->frame_low) {
            lower_top = false;
          }
        }
        if (lower_top) {
          left->desc->frame_top = right->desc->frame_low;
        }
        allocate_temp_frame_slot(left,4,left->desc->saved_reg_ea);
        frame_field = &node->desc->frame_low;
        low = left->desc->frame_low;
        if (low < *frame_field) {
          *frame_field = low;
        }
        macro = 0xf00;
        peVar1 = left->desc->saved_reg_ea;
      }
      goto LAB_0041ee7c;
    }
  }
  peVar1 = alloc_zeroed(0xc);
  left->desc->saved_reg_ea = peVar1;
  fill_ea(left->desc->saved_reg_ea,'\x01',(byte)new_reg,-1,'\0',0,(label_ref *)0x0);
  new_mask = 1 << ((byte)new_reg & 0x1f);
  mask_ptr = &left->desc->busy_regs;
  *mask_ptr = *mask_ptr | new_mask;
  macro = 0xf00;
  g_used_gpr_mask = g_used_gpr_mask | left->desc->busy_regs;
  mask_ptr = &left->desc->temp_regs;
  *mask_ptr = *mask_ptr | new_mask;
  peVar1 = left->desc->saved_reg_ea;
LAB_0041ee7c:
  emit_operand_transfer
            (left->desc->saved_ea,peVar1,'p',left,macro,left->type,
             (int)(short)(result_excl | value_regs | right_reused),
             (int)(short)(value_regs | right_reused),(int)left);
  invalidate_slot_registers(left,'p',right->desc->temp_regs);
  desc = left->desc;
  mask32 = ea_register_mask(desc->saved_ea);
  mask_ptr = &desc->busy_regs;
  *mask_ptr = *mask_ptr ^ (ushort)mask32;
  return new_mask;
}



