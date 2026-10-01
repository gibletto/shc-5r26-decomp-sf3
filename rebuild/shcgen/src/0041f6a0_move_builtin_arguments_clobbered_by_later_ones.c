#include "decls.h"
#include "imports.h"

// entry: 0041f6a0
// name : move_builtin_arguments_clobbered_by_later_ones
// size : 546
// sig  : void move_builtin_arguments_clobbered_by_later_ones(gen_node * arg_list)


int __cdecl move_builtin_arguments_clobbered_by_later_ones(gen_node *arg_list)

{
  ushort xfer_excluded;
  uint value_regs;
  int pos;
  gen_node *arg;
  int *frame_field;
  ushort new_mask;
  ushort mask;
  ushort arg_regs;
  short new_reg;
  ushort later_reused;
  ushort list_busy;
  int low;
  ushort *mask_ptr;
  node_desc *next_desc;
  
  arg_regs = 0;
  list_busy = arg_list->desc->busy_regs;
  for (arg = arg_list->child; (arg != (gen_node *)0x0 && (arg->op != IL_E_ARG)); arg = arg->next) {
    value_regs = ea_register_mask(&arg->desc->value);
    arg_regs = arg_regs | (ushort)value_regs;
    arg->desc->busy_regs = list_busy | (ushort)value_regs;
  }
  mask = 0;
  later_reused = 0;
  pos = count_operands(arg_list);
  pos = pos + -2;
  while ((pos != 0 && (arg = nth_operand(arg_list,pos), arg != (gen_node *)0x0))) {
    next_desc = arg->next->desc;
    mask = mask | next_desc->temp_regs;
    later_reused = later_reused | next_desc->reused_regs;
    arg_regs = arg_regs & ~mask;
    value_regs = ea_register_mask(&arg->desc->value);
    if ((~g_var_gpr_mask & (ushort)value_regs & mask & 0x7fff) != 0) {
      xfer_excluded = later_reused | list_busy;
      new_reg = choose_general_register(mask | arg_regs | xfer_excluded,0xf,'\0');
      if (new_reg == -1) {
        new_reg = choose_general_register(later_reused | mask | arg_regs,0xf,'\0');
      }
      if (new_reg == -1) {
        frame_field = &arg->desc->frame_top;
        low = arg_list->desc->frame_low;
        if (low < *frame_field) {
          *frame_field = low;
        }
        allocate_temp_frame_slot(arg,4,&arg->desc->dest);
        low = arg->desc->frame_low;
        frame_field = &arg_list->desc->frame_low;
        if (low < *frame_field) {
          *frame_field = low;
        }
        arg->desc->opnd_class = '\x03';
      }
      else {
        fill_ea(&arg->desc->dest,'\x01',(byte)new_reg,-1,'\0',0,(label_ref *)0x0);
        new_mask = 1 << ((byte)new_reg & 0x1f);
        mask_ptr = &arg->desc->busy_regs;
        *mask_ptr = *mask_ptr | new_mask;
        g_used_gpr_mask = g_used_gpr_mask | arg->desc->busy_regs;
        mask_ptr = &arg->desc->temp_regs;
        *mask_ptr = *mask_ptr | new_mask;
        arg->desc->opnd_class = '\0';
      }
      emit_operand_transfer
                (&arg->desc->value,&arg->desc->dest,'0',arg,5,arg->type,
                 (int)(short)(arg_regs | xfer_excluded),(int)(short)(later_reused | arg_regs),
                 (int)arg);
      invalidate_slot_registers(arg,'0',mask);
      mask_ptr = &arg->desc->busy_regs;
      *mask_ptr = *mask_ptr ^ (ushort)value_regs;
    }
    pos = pos + -1;
  }
  return;
}



