#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004278c0
// name : choose_move_entry_register
// size : 3917
// sig  : ushort choose_move_entry_register(ea * src, ea * dst, uchar slot, gen_node * node, ushort op, uchar value_type, uint excluded, gen_node * account_node)


/* WARNING: Removing unreachable block (ram,0x00427fc5) */

ushort __cdecl
choose_move_entry_register
          (ea *src,ea *dst,uchar slot,gen_node *node,ushort op,uchar value_type,uint excluded,
          gen_node *account_node)

{
  char cVar1;
  ushort reg;
  uint uVar2;
  ea *const_ea;
  byte fpu_kind;
  byte bVar3;
  ushort found;
  ushort avoid_mask;
  short cpu;
  int disp;
  ushort *mask_ptr;
  
  uVar2 = ea_register_mask(src);
  if ((op == 0xc00) && ((src->type & 0x40) != 0)) {
    value_type = '@';
    op = 0xd00;
  }
  avoid_mask = (ushort)(excluded | uVar2);
  reg = found;
  if (op < 0xd01) {
    if (op != 0xd00) {
      if (op != 0xc00) goto LAB_00427967;
      goto LAB_0042799e;
    }
    bVar3 = src->type & 0x1f;
    if (bVar3 == 8) {
      if ((src->base == 'l') ||
         ((((src->labels == (label_ref *)0x0 && (-0x81 < src->disp)) && (src->disp < 0x80)) ||
          (dst->base != src->base)))) goto LAB_004280af;
      reg = choose_general_register(avoid_mask,0,'\0');
      found = (ushort)(reg != 0xffff);
      if (found != 1) goto LAB_004286ba;
      bVar3 = src->type & 0x1f;
      if (((bVar3 != 2) || (src->base != 'l')) && ((bVar3 != 8 || (src->base != 'l')))) {
        const_ea = copy_ea(src);
        const_ea->type = const_ea->type & 0xf7 | 7;
        record_constant_in_register(const_ea,reg,node);
        free_ea(const_ea);
      }
    }
    else {
      if (bVar3 != 9) {
        if (bVar3 != 0xd) {
          report_codegen_message(0x1225,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
          goto LAB_004280b7;
        }
        cVar1 = dst->base;
        const_ea = copy_ea(src);
        const_ea->type = const_ea->type & 0xf7 | 7;
        record_constant_in_register(const_ea,(short)cVar1,node);
        free_ea(const_ea);
      }
LAB_004280af:
      reg = 0xffff;
      found = 1;
    }
LAB_004280b7:
    if ((found == 1) && ((short)dst->base == reg)) {
      invalidate_register_contents(1 << ((byte)reg & 0x1f));
    }
    goto LAB_004286ba;
  }
  if (op < 0xf01) {
    if (op != 0xf00) {
      if (op != 0xe00) goto LAB_00427967;
LAB_004285ba:
      bVar3 = src->type & 0x1f;
      if ((((bVar3 != 2) || (src->base != 'l')) && ((bVar3 != 8 || (src->base != 'l')))) &&
         ((bVar3 == 2 || (((bVar3 == 8 && (src->disp == 0)) && (src->labels == (label_ref *)0x0)))))
         ) {
        found = 1;
        reg = 0xffff;
        goto LAB_004286ba;
      }
      if (bVar3 == 9) {
        if ((excluded & 1 << (src->index & 0x1fU)) == 0) {
          reg = (ushort)src->index;
        }
        else {
          bVar3 = src->base;
          if ((((('\x0e' < (char)bVar3) ||
                ((1 << (bVar3 & 0x1f) & (int)(short)~g_var_gpr_mask) == 0)) &&
               (('\x1f' < (char)bVar3 ||
                (((char)bVar3 < '\x10' ||
                 ((1 << (bVar3 - 0x10 & 0x1f) & (int)(short)~g_var_fpr_mask) == 0)))))) &&
              (('.' < (char)bVar3 ||
               (((char)bVar3 < ' ' ||
                (((int)(short)g_var_fpr_mask &
                 (1 << (bVar3 - 0x1f & 0x1f) | 1 << (bVar3 - 0x20 & 0x1f))) != 0)))))) ||
             ((excluded & 1 << (bVar3 & 0x1f)) != 0)) goto LAB_00428695;
          reg = (ushort)(char)bVar3;
        }
      }
      else {
LAB_00428695:
        reg = choose_general_register(avoid_mask,0,'\0');
      }
      found = (ushort)(reg != 0xffff);
      goto LAB_004286ba;
    }
LAB_004280e6:
    uVar2 = ea_register_mask(dst);
    avoid_mask = avoid_mask | (ushort)uVar2;
    switch(dst->type & 0x1f) {
    case 2:
    case 9:
      if ((g_request->cpu == 4) && ((value_type & 0xf8) == 0x30)) {
        g_last_chosen_reg = -1;
        reg = choose_general_register(avoid_mask,1,'\x01');
        found = (ushort)(reg != 0xffff);
      }
      else {
        reg = 0xffff;
        found = 1;
      }
      break;
    default:
      report_codegen_message(0x1225,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      break;
    case 8:
      cpu = g_request->cpu;
      if ((cpu == 4) && ((value_type & 0xf8) == 0x30)) {
        g_last_chosen_reg = -1;
        reg = choose_general_register(avoid_mask,1,'\x01');
        found = (ushort)(reg != 0xffff);
        break;
      }
      if ((cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar3 = 1;
      }
      else {
        bVar3 = -(cpu == 4) & 2;
      }
      if ((bVar3 != 0) && ((value_type & 0xf8) == 0x28)) {
        if ((dst->base == 'l') || ((dst->disp != 0 || (dst->labels != (label_ref *)0x0)))) {
          g_last_chosen_reg = -1;
          reg = choose_general_register(avoid_mask,1,'\x01');
          found = (ushort)(reg != 0xffff);
        }
        else {
          reg = 0xffff;
          found = 1;
        }
        break;
      }
      cVar1 = dst->base;
      if (((cVar1 == 'l') || (dst->labels != (label_ref *)0x0)) ||
         ((dst->disp != 0 &&
          (((((bVar3 = value_type & 0xe0, bVar3 != 0x60 && (bVar3 != 0x80)) ||
             ((value_type & 0x18) != 0x10)) &&
            ((((value_type & 0xf8) != 0x10 && ((value_type & 0xf8) != 0x18)) &&
             ((bVar3 != 0x20 && (bVar3 != 0x40)))))) || ((dst->disp < 1 || (0x3c < dst->disp))))))))
      {
        if (cVar1 == '\0') {
          reg = choose_general_register(avoid_mask,0,'\0');
          found = (ushort)(reg != 0xffff);
        }
        else if ((((src->base == '\0') && (cVar1 != 'l')) && (dst->labels == (label_ref *)0x0)) &&
                ((((((bVar3 = value_type & 0xe0, bVar3 == 0x60 || (bVar3 == 0x80)) &&
                    ((value_type & 0x18) == 0)) || ((value_type & 0xf8) == 0)) &&
                  ((0 < dst->disp && (dst->disp < 0x10)))) ||
                 (((((bVar3 == 0x60 || (bVar3 == 0x80)) && ((value_type & 0x18) == 8)) ||
                   ((value_type & 0xf8) == 8)) && ((0 < dst->disp && (dst->disp < 0x1f)))))))) {
          reg = 0;
          found = 1;
        }
        else {
          g_last_chosen_reg = -1;
          reg = choose_general_register(avoid_mask,1,'\x01');
          found = (ushort)(reg != 0xffff);
          if (((((found == 1) && ((bVar3 = dst->type & 0x1f, bVar3 != 2 || (dst->base != 'l')))) &&
               ((bVar3 != 8 || (dst->base != 'l')))) && (reg == 0)) &&
             ((dst->labels != (label_ref *)0x0 ||
              ((((((bVar3 = value_type & 0xe0, bVar3 != 0x60 && (bVar3 != 0x80)) ||
                  ((value_type & 0x18) != 0)) && ((value_type & 0xf8) != 0)) ||
                ((dst->disp < 1 || (0xf < dst->disp)))) &&
               (((((bVar3 != 0x60 && (bVar3 != 0x80)) || ((value_type & 0x18) != 8)) &&
                 ((value_type & 0xf8) != 8)) || ((dst->disp < 1 || (0x1e < dst->disp)))))))))) {
            const_ea = copy_ea(dst);
            const_ea->type = const_ea->type & 0xf7 | 7;
            record_constant_in_register(const_ea,0,node);
            free_ea(const_ea);
          }
        }
        break;
      }
    case 1:
    case 3:
      reg = 0xffff;
      found = 1;
      break;
    case 0xd:
      if (((src->type & 0x1f) == 1) && (src->base == '\0')) {
        if (dst->labels == (label_ref *)0x0) {
          uVar2 = 0;
        }
        else {
          uVar2 = (uint)dst->labels->labno1;
        }
        if ((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 3) != 0) {
          reg = 0xffff;
          found = 1;
          break;
        }
      }
      cpu = g_request->cpu;
      if ((cpu != 2) || (bVar3 = 1, g_request->fpu_mode != '\x03')) {
        bVar3 = -(cpu == 4) & 2;
      }
      if (((bVar3 == 0) || ((value_type & 0xf8) != 0x28)) &&
         ((cpu != 4 || ((value_type & 0xf8) != 0x30)))) {
        if (dst->labels == (label_ref *)0x0) {
          uVar2 = 0;
        }
        else {
          uVar2 = (uint)dst->labels->labno1;
        }
        if ((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 3) == 0)
        goto LAB_004284dd;
        cVar1 = '\x01';
        reg = 1;
      }
      else {
LAB_004284dd:
        reg = 0;
        cVar1 = '\0';
      }
      reg = choose_general_register(avoid_mask,reg,cVar1);
      found = (ushort)(reg != 0xffff);
      if (found == 1) {
        if (dst->labels == (label_ref *)0x0) {
          uVar2 = 0;
        }
        else {
          uVar2 = (uint)dst->labels->labno1;
        }
        if (((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 3) == 0) ||
           ((reg != 0 && (((src->type & 0x1f) != 1 || (src->base != '\0')))))) {
          const_ea = copy_ea(dst);
          const_ea->type = const_ea->type & 0xf7 | 7;
          record_constant_in_register(const_ea,reg,node);
          free_ea(const_ea);
        }
      }
    }
  }
  else {
    if (op < 0x1c01) {
      if (op != 0x1c00) {
        if (op == 0x1b00) {
          if ((node->desc->flags3 & 0x20) != 0) {
            reg = choose_general_register(avoid_mask,0,'\0');
            found = (ushort)(reg != 0xffff);
            goto LAB_004286ba;
          }
          goto LAB_004285ba;
        }
LAB_00427967:
        report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        goto LAB_004286ba;
      }
      goto LAB_004280e6;
    }
    if (op != 0x2700) {
      if (op == 0x2800) goto LAB_004280e6;
      if (op != 0x2b00) goto LAB_00427967;
    }
LAB_0042799e:
    bVar3 = src->type & 0x1f;
    switch(bVar3) {
    case 1:
    case 4:
      reg = 0xffff;
      found = 1;
      break;
    case 2:
    case 9:
      if ((g_request->cpu == 4) && ((value_type & 0xf8) == 0x30)) {
        g_last_chosen_reg = -1;
        reg = choose_general_register(avoid_mask,1,'\x01');
        found = (ushort)(reg != 0xffff);
      }
      else {
        reg = 0xffff;
        found = 1;
      }
      break;
    default:
      report_codegen_message(0x1225,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      break;
    case 7:
      record_constant_in_register(src,(short)dst->base,node);
      goto LAB_00427e7e;
    case 8:
      disp = src->disp;
      cpu = g_request->cpu;
      if ((cpu == 4) && ((value_type & 0xf8) == 0x30)) {
        g_last_chosen_reg = -1;
        reg = choose_general_register(avoid_mask,1,'\x01');
        found = (ushort)(reg != 0xffff);
      }
      else {
        if ((cpu == 2) && (g_request->fpu_mode == '\x03')) {
          fpu_kind = 1;
        }
        else {
          fpu_kind = -(cpu == 4) & 2;
        }
        if ((fpu_kind == 0) || ((value_type & 0xf8) != 0x28)) {
          if ((((bVar3 == 2) && (src->base == 'l')) ||
              (((bVar3 == 8 && (src->base == 'l')) || (src->labels != (label_ref *)0x0)))) ||
             ((((disp != 0 &&
                (((((bVar3 = value_type & 0xe0, bVar3 != 0x60 && (bVar3 != 0x80)) ||
                   ((value_type & 0x18) != 0x10)) &&
                  ((((value_type & 0xf8) != 0x10 && ((value_type & 0xf8) != 0x18)) &&
                   ((bVar3 != 0x20 && (bVar3 != 0x40)))))) || ((disp < 1 || (0x3c < disp)))))) &&
               (((cVar1 = src->base, cVar1 != '\0' || (dst->base != '\0')) ||
                ((((((bVar3 != 0x60 && (bVar3 != 0x80)) || ((value_type & 0x18) != 0)) &&
                   ((value_type & 0xf8) != 0)) || ((disp < 1 || (0xf < disp)))) &&
                 (((((bVar3 != 0x60 && (bVar3 != 0x80)) || ((value_type & 0x18) != 8)) &&
                   ((value_type & 0xf8) != 8)) || ((disp < 1 || (0x1e < disp)))))))))) &&
              ((cVar1 == '\0' || ((dst->base == cVar1 || (((excluded | uVar2) & 1) == 0)))))))) {
            g_last_chosen_reg = -1;
            reg = choose_general_register(avoid_mask,1,'\x01');
            found = (ushort)(reg != 0xffff);
            if (found != 1) goto LAB_004286ba;
            bVar3 = src->type & 0x1f;
            if (((bVar3 != 2) || (src->base != 'l')) && ((bVar3 != 8 || (src->base != 'l')))) {
              if (reg == 0) {
                if ((src->labels != (label_ref *)0x0) ||
                   ((((((bVar3 = value_type & 0xe0, bVar3 != 0x60 && (bVar3 != 0x80)) ||
                       ((value_type & 0x18) != 0)) && ((value_type & 0xf8) != 0)) ||
                     ((src->disp < 1 || (0xf < src->disp)))) &&
                    (((((bVar3 != 0x60 && (bVar3 != 0x80)) || ((value_type & 0x18) != 8)) &&
                      ((value_type & 0xf8) != 8)) || ((src->disp < 1 || (0x1e < src->disp)))))))) {
LAB_00427cdb:
                  const_ea = copy_ea(src);
                  const_ea->type = const_ea->type & 0xf7 | 7;
                  record_constant_in_register(const_ea,reg,node);
                  free_ea(const_ea);
                }
              }
              else if (src->base == '\0') goto LAB_00427cdb;
            }
          }
          else {
            reg = 0xffff;
            found = 1;
          }
        }
        else if (((src->base == 'l') || (disp != 0)) || (src->labels != (label_ref *)0x0)) {
          g_last_chosen_reg = -1;
          reg = choose_general_register(avoid_mask,1,'\x01');
          found = (ushort)(reg != 0xffff);
        }
        else {
          reg = 0xffff;
          found = 1;
        }
      }
      break;
    case 0xd:
      if (((dst->type & 0x1f) == 1) && (dst->base == '\0')) {
        if (src->labels == (label_ref *)0x0) {
          uVar2 = 0;
        }
        else {
          uVar2 = (uint)src->labels->labno1;
        }
        if ((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 3) != 0) {
          reg = 0xffff;
          found = 1;
          break;
        }
      }
      cpu = g_request->cpu;
      if ((cpu != 2) || (bVar3 = 1, g_request->fpu_mode != '\x03')) {
        bVar3 = -(cpu == 4) & 2;
      }
      if (((bVar3 == 0) || ((value_type & 0xf8) != 0x28)) &&
         ((cpu != 4 || ((value_type & 0xf8) != 0x30)))) {
        if (src->labels == (label_ref *)0x0) {
          uVar2 = 0;
        }
        else {
          uVar2 = (uint)src->labels->labno1;
        }
        if ((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 3) == 0)
        goto LAB_00427dc7;
        reg = 1;
      }
      else {
LAB_00427dc7:
        reg = 0;
      }
      uVar2 = ea_register_mask(dst);
      reg = choose_general_register(avoid_mask | (ushort)uVar2,reg,(char)reg);
      found = (ushort)(reg != 0xffff);
      if (found != 1) goto LAB_004286ba;
      if (src->labels == (label_ref *)0x0) {
        uVar2 = 0;
      }
      else {
        uVar2 = (uint)src->labels->labno1;
      }
      if (((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 3) == 0) ||
         ((reg != 0 && (((dst->type & 0x1f) != 1 || (dst->base != '\0')))))) {
        const_ea = copy_ea(src);
        const_ea->type = const_ea->type & 0xf7 | 7;
        record_constant_in_register(const_ea,reg,node);
        free_ea(const_ea);
      }
      break;
    case 0xe:
LAB_00427e7e:
      cpu = g_request->cpu;
      if ((cpu == 4) && ((value_type & 0xf8) == 0x30)) {
        g_last_chosen_reg = -1;
        reg = choose_general_register(avoid_mask,1,'\x01');
        found = (ushort)(reg != 0xffff);
      }
      else {
        if ((cpu == 2) && (g_request->fpu_mode == '\x03')) {
          bVar3 = 1;
        }
        else {
          bVar3 = -(cpu == 4) & 2;
        }
        if ((bVar3 == 0) || ((value_type & 0xf8) != 0x28)) {
          reg = 0xffff;
          found = 1;
        }
        else if ((src->disp == g_float_one_bits) || (src->disp == g_float_zero_bits)) {
          reg = 0xffff;
          found = 1;
        }
        else {
          g_last_chosen_reg = -1;
          reg = choose_general_register(avoid_mask,1,'\x01');
          found = (ushort)(reg != 0xffff);
        }
      }
    }
    if ((found == 1) && ((short)dst->base == reg)) {
      invalidate_register_contents(1 << ((byte)reg & 0x1f));
    }
  }
LAB_004286ba:
  bVar3 = (byte)reg;
  if (reg != 0xffff) {
    mask_ptr = &account_node->desc->temp_regs;
    *mask_ptr = *mask_ptr | 1 << (bVar3 & 0x1f);
  }
  if (found == 1) {
    switch(slot & 0xf0) {
    case 0x10:
      node->desc->regs_2c[slot & 0xf] = bVar3;
      return 1;
    case 0x20:
      node->desc->regs_34[slot & 0xf] = bVar3;
      return 1;
    case 0x30:
      node->desc->regs_41[slot & 0xf] = bVar3;
      return 1;
    case 0x40:
      node->desc->regs_44[slot & 0xf] = bVar3;
      return 1;
    case 0x50:
      node->desc->addr_reg = bVar3;
      return 1;
    case 0x60:
      node->desc->regs_3d[slot & 0xf] = bVar3;
      return 1;
    case 0x70:
      node->desc->reg_47 = bVar3;
      return 1;
    case 0x80:
      node->desc->cond_regs[slot & 0xf] = bVar3;
      break;
    default:
      report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return 1;
    }
  }
  return found;
}



