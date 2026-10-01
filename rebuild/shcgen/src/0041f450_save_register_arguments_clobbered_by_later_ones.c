#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041f450
// name : save_register_arguments_clobbered_by_later_ones
// size : 584
// sig  : void save_register_arguments_clobbered_by_later_ones(gen_node * arg_list, int skip_last)


int __cdecl save_register_arguments_clobbered_by_later_ones(gen_node *arg_list,int skip_last)

{
  ushort mask;
  char base;
  int pos;
  gen_node *arg;
  uint mask32;
  ea *operand;
  ushort later_ftemp;
  char index;
  char misc;
  int disp;
  label_ref *labels;
  ushort later_temp;
  ushort later_reused;
  ushort earlier_target;
  ushort later_freused;
  ushort earlier_ftarget;
  int stop_pos;
  short sVar1;
  byte bank_count;
  node_desc *desc;
  uchar *flags_ptr;
  node_desc *next_desc;
  
  later_ftemp = 0;
  arg = arg_list->parent;
  sVar1 = arg->call_06;
  pos = count_operands(arg_list);
  later_temp = 0;
  later_reused = 0;
  earlier_target = 0;
  earlier_ftarget = 0;
  later_freused = 0;
  if ((sVar1 == 0) || ((arg->val3 & 1) == 0)) {
    stop_pos = 0;
  }
  else {
    stop_pos = pos - sVar1;
  }
  pos = pos - skip_last;
  while ((pos = pos + -1, stop_pos < pos &&
         (arg = nth_operand(arg_list,pos), arg != (gen_node *)0x0))) {
    desc = arg->desc;
    next_desc = arg->next->desc;
    later_temp = later_temp | next_desc->temp_regs;
    later_ftemp = later_ftemp | next_desc->ftemp_regs;
    later_reused = later_reused | next_desc->reused_regs;
    later_freused = later_freused | next_desc->freused_regs;
    if (((desc->target_regs & later_temp) != 0) || ((desc->ftarget_regs & later_ftemp) != 0)) {
      if ((((desc->value).type & 0x1f) == 0) ||
         (bank_count = g_request->scratch_bank_reg_count, mask32 = ea_register_mask(&desc->value),
         (mask32 & (((1 << (bank_count & 0x1f)) + -1) * 0x100000 | 0xf00ffU)) != 0)) {
        flags_ptr = &arg->desc->flags2;
        *flags_ptr = *flags_ptr | 8;
        emit_operand_transfer
                  (&arg->desc->value,&g_ea_push,'0',arg,0x1500,arg->type,
                   (int)(short)(arg_list->desc->fbusy_regs | later_freused) << 0x10 |
                   (int)(short)arg_list->desc->busy_regs | (int)(short)later_reused,
                   (int)(short)later_freused << 0x10 | (int)(short)later_reused,(int)arg);
      }
      else {
        copy_ea_into(&arg->desc->dest,&arg->desc->value);
        flags_ptr = &arg->desc->flags3;
        *flags_ptr = *flags_ptr | 4;
        operand = alloc_zeroed(0xc);
        labels = (label_ref *)0x0;
        mask = arg->desc->ftarget_regs;
        disp = 0;
        misc = '\0';
        index = -1;
        if (mask == 0) {
          sVar1 = mask_to_register((int)(short)arg->desc->target_regs);
          base = (char)sVar1;
        }
        else {
          sVar1 = float_mask_to_register(mask);
          base = (char)sVar1;
        }
        fill_ea(operand,'\x01',base,index,misc,disp,labels);
        emit_operand_transfer
                  (&arg->desc->dest,operand,'P',arg,0xc00,arg->type,
                   (int)(short)(arg_list->desc->fbusy_regs | earlier_ftarget) << 0x10 |
                   (int)(short)arg_list->desc->busy_regs | (int)(short)earlier_target,
                   (int)(short)earlier_ftarget << 0x10 | (int)(short)earlier_target,(int)arg);
        free_ea(operand);
      }
    }
    earlier_target = earlier_target | arg->desc->target_regs;
    earlier_ftarget = earlier_ftarget | arg->desc->ftarget_regs;
  }
  return;
}



