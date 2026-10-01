#include "decls.h"
#include "imports.h"
int shcgen_knob_tst_r0(void);
int shcgen_knob_mul_l(void);
void regtrace_site(int site, char *node);
char regtrace_chooser_enter(char ascending, unsigned ret);
void regtrace_chooser_exit(unsigned short p1, unsigned short p2, char p3, short *slots, int chosen);
void regtrace_function(char *rec);
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004289f0
// name : assign_condition_value_registers
// size : 1635
// sig  : void assign_condition_value_registers(gen_node * node)


int __cdecl assign_condition_value_registers(gen_node *node)

{
  char cVar1;
  char second_freg;
  byte bVar2;
  short chosen;
  int result;
  uint excluded_mask;
  ea *reg_ea;
  byte bVar3;
  ushort reg_bits;
  ushort uVar4;
  gen_node *pgVar5;
  node_desc *desc;
  uchar *mode_flags_ptr;
  ushort *regs_ptr;
  bool track_fpscr;
  ea *value_ea;
  
  if ((g_request->cpu != 4) || (track_fpscr = true, g_request->unknown_155[2] != '\0')) {
    track_fpscr = false;
  }
  if (((node->desc->true_label != 0) && (node->desc->opnd_class == '\x02')) &&
     (result = constant_condition_is_zero(node), result != 0)) {
    return;
  }
  if (((node->desc->false_label != 0) && (node->desc->opnd_class == '\x02')) &&
     (result = constant_condition_is_zero(node), result == 0)) {
    return;
  }
  bVar3 = node->type & 0xf8;
  if (bVar3 == 0x30) {
    if (g_request->cpu != 4) {
      node->desc->cond_regs[0] = '\0';
      node->desc->cond_regs[1] = -1;
      regs_ptr = &node->desc->temp_regs;
      *(byte *)regs_ptr = (byte)*regs_ptr | 1;
      invalidate_register_contents(1);
      g_used_gpr_mask = g_used_gpr_mask | 1;
      g_r0_used = 1;
      return;
    }
    desc = node->desc;
    value_ea = &desc->value;
    if ((value_ea->type & 0x1f) != 0) {
      cVar1 = desc->opnd_class;
      if (cVar1 != '\x02') {
        if ((cVar1 == '\0') || (cVar1 == '\x01')) {
          cVar1 = (desc->value).base;
        }
        else {
          chosen = 0;
          excluded_mask = result_reg_exclusion_mask(node);
          chosen = choose_float_register_pair((ushort)(excluded_mask >> 0x10),chosen);
          cVar1 = (char)chosen;
          if (cVar1 == -1) {
            chosen = 0;
            excluded_mask = ea_register_mask(value_ea);
            chosen = choose_float_register_pair((ushort)(excluded_mask >> 0x10),chosen);
            cVar1 = (char)chosen;
          }
        }
        node->desc->cond_regs[2] = cVar1;
        chosen = 0;
        reg_bits = 1 << (cVar1 - 0x1fU & 0x1f) | 1 << (cVar1 - 0x20U & 0x1f);
        regs_ptr = &node->desc->ftemp_regs;
        *regs_ptr = *regs_ptr | reg_bits;
        g_used_fpr_mask = g_used_fpr_mask | reg_bits;
        excluded_mask = result_reg_exclusion_mask(node);
        chosen = choose_float_register_pair((ushort)(excluded_mask >> 0x10) | reg_bits,chosen);
        second_freg = (char)chosen;
        if (second_freg == -1) {
          chosen = 0;
          excluded_mask = ea_register_mask(value_ea);
          chosen = choose_float_register_pair((ushort)(excluded_mask >> 0x10) | reg_bits,chosen);
          second_freg = (char)chosen;
        }
        node->desc->cond_regs[3] = second_freg;
        reg_bits = 1 << (second_freg - 0x1fU & 0x1f) | 1 << (second_freg - 0x20U & 0x1f);
        regs_ptr = &node->desc->ftemp_regs;
        *regs_ptr = *regs_ptr | reg_bits;
        g_used_fpr_mask = g_used_fpr_mask | reg_bits;
        reg_ea = alloc_zeroed(0xc);
        fill_ea(reg_ea,'\x01',cVar1,-1,'\0',0,(label_ref *)0x0);
        g_last_chosen_reg = -1;
        pgVar5 = node;
        excluded_mask = ea_register_mask(value_ea);
        choose_move_entry_register(value_ea,reg_ea,0x81,node,0xc00,node->type,excluded_mask,pgVar5);
      }
      cVar1 = '\0';
      reg_bits = 0;
      excluded_mask = result_reg_exclusion_mask(node);
      chosen = choose_general_register((ushort)excluded_mask,reg_bits,cVar1);
      bVar3 = (byte)chosen;
      if (bVar3 == 0xff) {
        chosen = choose_general_register(0,0,'\0');
        bVar3 = (byte)chosen;
      }
      node->desc->cond_regs[0] = bVar3;
      reg_bits = 1 << (bVar3 & 0x1f);
      regs_ptr = &node->desc->temp_regs;
      *regs_ptr = *regs_ptr | reg_bits;
      g_used_gpr_mask = g_used_gpr_mask | reg_bits;
      if ((track_fpscr) && ((g_fpscr_pr == '\0' || (g_fpscr_pr == '\x02')))) {
        cVar1 = '\0';
        mode_flags_ptr = &node->desc->fpu_mode_flags;
        *mode_flags_ptr = *mode_flags_ptr | 2;
        g_fpscr_pr = '\x01';
        uVar4 = 0;
        excluded_mask = result_reg_exclusion_mask(node);
        chosen = choose_general_register((ushort)excluded_mask | reg_bits,uVar4,cVar1);
        bVar3 = (byte)chosen;
        if (bVar3 == 0xff) {
          chosen = choose_general_register(reg_bits,0,'\0');
          bVar3 = (byte)chosen;
        }
        node->desc->cond_regs[4] = bVar3;
        reg_bits = 1 << (bVar3 & 0x1f);
        regs_ptr = &node->desc->temp_regs;
        *regs_ptr = *regs_ptr | reg_bits;
        g_used_gpr_mask = g_used_gpr_mask | reg_bits;
        return;
      }
    }
  }
  else {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      bVar2 = 1;
    }
    else {
      bVar2 = -(g_request->cpu == 4) & 2;
    }
    if ((bVar2 != 0) && (bVar3 == 0x28)) {
      desc = node->desc;
      value_ea = &desc->value;
      if ((value_ea->type & 0x1f) != 0) {
        cVar1 = desc->opnd_class;
        if (cVar1 != '\x02') {
          if ((cVar1 == '\0') || (cVar1 == '\x01')) {
            cVar1 = (desc->value).base;
          }
          else {
            chosen = 0;
            excluded_mask = result_reg_exclusion_mask(node);
            chosen = choose_float_register((ushort)(excluded_mask >> 0x10),chosen);
            cVar1 = (char)chosen;
            if (cVar1 == -1) {
              chosen = 0;
              excluded_mask = ea_register_mask(value_ea);
              chosen = choose_float_register((ushort)(excluded_mask >> 0x10),chosen);
              cVar1 = (char)chosen;
            }
          }
          node->desc->cond_regs[2] = cVar1;
          chosen = 0;
          reg_bits = 1 << (cVar1 - 0x10U & 0x1f);
          regs_ptr = &node->desc->ftemp_regs;
          *regs_ptr = *regs_ptr | reg_bits;
          g_used_fpr_mask = g_used_fpr_mask | reg_bits;
          excluded_mask = result_reg_exclusion_mask(node);
          chosen = choose_float_register((ushort)(excluded_mask >> 0x10) | reg_bits,chosen);
          second_freg = (char)chosen;
          if (second_freg == -1) {
            chosen = 0;
            excluded_mask = ea_register_mask(value_ea);
            chosen = choose_float_register((ushort)(excluded_mask >> 0x10) | reg_bits,chosen);
            second_freg = (char)chosen;
          }
          node->desc->cond_regs[3] = second_freg;
          reg_bits = 1 << (second_freg - 0x10U & 0x1f);
          regs_ptr = &node->desc->ftemp_regs;
          *regs_ptr = *regs_ptr | reg_bits;
          g_used_fpr_mask = g_used_fpr_mask | reg_bits;
          reg_ea = alloc_zeroed(0xc);
          fill_ea(reg_ea,'\x01',cVar1,-1,'\0',0,(label_ref *)0x0);
          g_last_chosen_reg = -1;
          pgVar5 = node;
          excluded_mask = ea_register_mask(value_ea);
          choose_move_entry_register
                    (value_ea,reg_ea,0x81,node,0xc00,node->type,excluded_mask,pgVar5);
        }
        cVar1 = '\0';
        reg_bits = 0;
        excluded_mask = result_reg_exclusion_mask(node);
        chosen = choose_general_register((ushort)excluded_mask,reg_bits,cVar1);
        bVar3 = (byte)chosen;
        if (bVar3 == 0xff) {
          chosen = choose_general_register(0,0,'\0');
          bVar3 = (byte)chosen;
        }
        node->desc->cond_regs[0] = bVar3;
        reg_bits = 1 << (bVar3 & 0x1f);
        regs_ptr = &node->desc->temp_regs;
        *regs_ptr = *regs_ptr | reg_bits;
        g_used_gpr_mask = g_used_gpr_mask | reg_bits;
        if (!track_fpscr) {
          return;
        }
        if ((g_fpscr_pr != '\x01') && (g_fpscr_pr != '\x02')) {
          return;
        }
        cVar1 = '\0';
        mode_flags_ptr = &node->desc->fpu_mode_flags;
        *mode_flags_ptr = *mode_flags_ptr | 2;
        g_fpscr_pr = '\0';
        uVar4 = 0;
        excluded_mask = result_reg_exclusion_mask(node);
        chosen = choose_general_register((ushort)excluded_mask | reg_bits,uVar4,cVar1);
        bVar3 = (byte)chosen;
        if (bVar3 == 0xff) {
          chosen = choose_general_register(reg_bits,0,'\0');
          bVar3 = (byte)chosen;
        }
        node->desc->cond_regs[4] = bVar3;
        reg_bits = 1 << (bVar3 & 0x1f);
        regs_ptr = &node->desc->temp_regs;
        *regs_ptr = *regs_ptr | reg_bits;
        g_used_gpr_mask = g_used_gpr_mask | reg_bits;
        return;
      }
    }
    value_ea = &node->desc->value;
    if ((value_ea->type & 0x1f) != 0) {
      result = operand_access_needs_r0(value_ea,node->type);
      reg_bits = (ushort)(result != 0);
      cVar1 = '\0';
      if (shcgen_knob_tst_r0() != 0) {
        cVar1 = '\x01';
      }
      uVar4 = reg_bits;
      excluded_mask = result_reg_exclusion_mask(node);
      regtrace_site(372,(char *)node);
      chosen = choose_general_register((ushort)excluded_mask,uVar4,cVar1);
      bVar3 = (byte)chosen;
      if (bVar3 == 0xff) {
        cVar1 = '\0';
        excluded_mask = ea_register_mask(value_ea);
        chosen = choose_general_register((ushort)excluded_mask,reg_bits,cVar1);
        bVar3 = (byte)chosen;
      }
      node->desc->cond_regs[0] = bVar3;
      reg_bits = 1 << (bVar3 & 0x1f);
      regs_ptr = &node->desc->temp_regs;
      *regs_ptr = *regs_ptr | reg_bits;
      g_used_gpr_mask = g_used_gpr_mask | reg_bits;
      bVar2 = node->type & 0xf8;
      if ((bVar2 != 0x28) || (node->desc->opnd_class == '\0')) {
        cVar1 = node->desc->opnd_class;
        if ((cVar1 == '\0') || (cVar1 == '\x01')) {
          if (bVar2 != 0x28) {
            return;
          }
          if (cVar1 != '\0') {
            return;
          }
          excluded_mask = ea_register_mask(&node->desc->value);
          invalidate_register_contents(excluded_mask);
          return;
        }
      }
      reg_ea = alloc_zeroed(0xc);
      fill_ea(reg_ea,'\x01',bVar3,-1,'\0',0,(label_ref *)0x0);
      g_last_chosen_reg = -1;
      pgVar5 = node;
      excluded_mask = ea_register_mask(value_ea);
      choose_move_entry_register(value_ea,reg_ea,0x81,node,0xc00,node->type,excluded_mask,pgVar5);
      free_ea(reg_ea);
      invalidate_register_contents(1 << (bVar3 & 0x1f));
      return;
    }
    if ((node->op == IL_B_AND) && ((node->desc->flags2 & 0x20) != 0)) {
      cVar1 = '\0';
      reg_bits = 0;
      excluded_mask = result_reg_exclusion_mask(node);
      chosen = choose_general_register((ushort)excluded_mask,reg_bits,cVar1);
      bVar3 = (byte)chosen;
      if (bVar3 == 0xff) {
        chosen = choose_general_register(0,0,'\0');
        bVar3 = (byte)chosen;
      }
      regs_ptr = &node->desc->temp_regs;
      *regs_ptr = *regs_ptr | 1 << (bVar3 & 0x1f);
      node->desc->cond_regs[0] = bVar3;
    }
  }
  return;
}



