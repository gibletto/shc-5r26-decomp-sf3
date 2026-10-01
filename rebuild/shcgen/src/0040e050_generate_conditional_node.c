#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040e050
// name : generate_conditional_node
// size : 2094
// sig  : void generate_conditional_node(gen_node * node)


int __cdecl generate_conditional_node(gen_node *node)

{
  uchar *puVar1;
  ushort *puVar2;
  byte bVar3;
  short sVar4;
  gen_node *else_node;
  uint reg_mask;
  ushort mask;
  ushort pair_mask;
  gen_node *then_node;
  char cVar5;
  gen_node *cond;
  node_desc *desc;
  byte node_type;
  ea *operand;
  
  then_node = (gen_node *)0x0;
  cond = node->child;
  if (cond != (gen_node *)0x0) {
    then_node = cond->next;
  }
  else_node = nth_operand(node,3);
  desc = node->desc;
  if (desc->usage != '\0') {
    if (desc->usage == '\x01') {
      then_node->desc->false_label = desc->false_label;
      then_node->desc->true_label = node->desc->true_label;
      else_node->desc->false_label = node->desc->false_label;
      else_node->desc->true_label = node->desc->true_label;
    }
    else if ((desc->flags2 & 8) == 0) {
      if ((desc->flags3 & 0x20) == 0) {
        if (desc->target_regs == 0) {
          if (desc->ftarget_regs == 0) {
            operand = &desc->dest;
            bVar3 = operand->type & 0x1f;
            if ((bVar3 == 0) ||
               (((bVar3 == 2 || (bVar3 == 8)) &&
                ((((desc->dest).base < '\x0f' &&
                  (((int)(short)~g_var_gpr_mask & 1 << ((desc->dest).base & 0x1fU)) != 0)) ||
                 (((((desc->dest).base < ' ' && ('\x0f' < (desc->dest).base)) &&
                   ((1 << ((desc->dest).base - 0x10U & 0x1f) & (int)(short)~g_var_fpr_mask) != 0))
                  || ((((desc->dest).base < '/' && ('\x1f' < (desc->dest).base)) &&
                      (((int)(short)g_var_fpr_mask &
                       (1 << ((desc->dest).base - 0x1fU & 0x1f) |
                       1 << ((desc->dest).base - 0x20U & 0x1f))) == 0)))))))))) {
              if (bVar3 != 0) {
                operand->type = operand->type & 0xf0;
              }
              sVar4 = g_request->cpu;
              if (sVar4 == 4) {
LAB_0040e392:
                if ((node->type & 0xf8) == 0x30) {
                  mask = node->desc->fpref_regs;
                  reg_mask = result_reg_exclusion_mask(node);
                  sVar4 = choose_float_register_pair((ushort)(reg_mask >> 0x10),mask);
                  if (sVar4 == -1) {
                    sVar4 = choose_float_register_pair(0,node->desc->fpref_regs);
                  }
                }
                else {
LAB_0040e3d9:
                  if ((sVar4 == 2) && (g_request->fpu_mode == '\x03')) {
                    bVar3 = 1;
                  }
                  else {
                    bVar3 = -(sVar4 == 4) & 2;
                  }
                  if ((bVar3 == 0) || ((node->type & 0xf8) != 0x28)) {
                    cVar5 = '\0';
                    mask = node->desc->pref_regs;
                    reg_mask = result_reg_exclusion_mask(node);
                    sVar4 = choose_general_register((ushort)reg_mask,mask,cVar5);
                    if (sVar4 == -1) {
                      sVar4 = choose_general_register(0,node->desc->pref_regs,'\0');
                    }
                  }
                  else {
                    mask = node->desc->fpref_regs;
                    reg_mask = result_reg_exclusion_mask(node);
                    sVar4 = choose_float_register((ushort)(reg_mask >> 0x10),mask);
                    if (sVar4 == -1) {
                      sVar4 = choose_float_register(0,node->desc->fpref_regs);
                    }
                  }
                }
                cVar5 = (char)sVar4;
                fill_ea(&then_node->desc->dest,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
                fill_ea(&else_node->desc->dest,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
                fill_ea(&node->desc->value,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
                node->desc->opnd_class = '\0';
              }
              else {
                if ((node->type & 0xf8) != 0x30) {
                  if (sVar4 == 4) goto LAB_0040e392;
                  goto LAB_0040e3d9;
                }
                puVar1 = &then_node->desc->flags2;
                *puVar1 = *puVar1 | 8;
                puVar1 = &else_node->desc->flags2;
                *puVar1 = *puVar1 | 8;
                puVar1 = &node->desc->flags2;
                *puVar1 = *puVar1 | 8;
                node->desc->opnd_class = '\x03';
              }
            }
            else {
              copy_ea_into(&then_node->desc->dest,operand);
              copy_ea_into(&else_node->desc->dest,&node->desc->dest);
              desc = node->desc;
              if (((desc->dest).type & 0x1f) == 1) {
                desc->opnd_class = '\x01';
              }
              else {
                desc->opnd_class = '\x03';
              }
            }
          }
          else {
            sVar4 = float_mask_to_register(desc->ftarget_regs);
            cVar5 = (char)sVar4;
            fill_ea(&then_node->desc->dest,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
            fill_ea(&else_node->desc->dest,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
            fill_ea(&node->desc->value,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
            node->desc->opnd_class = '\x01';
          }
        }
        else {
          sVar4 = mask_to_register((int)(short)desc->target_regs);
          cVar5 = (char)sVar4;
          fill_ea(&then_node->desc->dest,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
          fill_ea(&else_node->desc->dest,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
          fill_ea(&node->desc->value,'\x01',cVar5,-1,'\0',0,(label_ref *)0x0);
          node->desc->opnd_class = '\x01';
        }
      }
      else {
        puVar1 = &then_node->desc->flags3;
        *puVar1 = *puVar1 | 0x20;
        puVar1 = &else_node->desc->flags3;
        *puVar1 = *puVar1 | 0x20;
        copy_ea_into(&then_node->desc->dest,&node->desc->dest);
        copy_ea_into(&else_node->desc->dest,&node->desc->dest);
        puVar1 = &node->desc->flags3;
        *puVar1 = *puVar1 & 0xdf;
        operand = &node->desc->dest;
        operand->type = operand->type & 0xf0;
      }
    }
    else {
      puVar1 = &then_node->desc->flags2;
      *puVar1 = *puVar1 | 8;
      puVar1 = &else_node->desc->flags2;
      *puVar1 = *puVar1 | 8;
    }
  }
  sVar4 = make_new_label_number();
  cond->desc->false_label = sVar4;
  cond->desc->busy_regs = node->desc->busy_regs;
  cond->desc->fbusy_regs = node->desc->fbusy_regs;
  cond->desc->frame_top = node->desc->frame_top;
  puVar1 = &cond->desc->flags7;
  *puVar1 = *puVar1 | node->desc->flags7 & 0x40;
  desc = cond->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    cond->desc->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(cond);
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    push_fpscr_pr_state();
  }
  save_register_contents();
  then_node->desc->busy_regs = node->desc->busy_regs;
  then_node->desc->fbusy_regs = node->desc->fbusy_regs;
  then_node->desc->frame_top = node->desc->frame_top;
  puVar1 = &then_node->desc->flags7;
  *puVar1 = *puVar1 | node->desc->flags7 & 0x40;
  desc = then_node->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    then_node->desc->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(then_node);
  invalidate_register_contents(0xf000f);
  else_node->desc->busy_regs = node->desc->busy_regs;
  else_node->desc->fbusy_regs = node->desc->fbusy_regs;
  else_node->desc->frame_top = node->desc->frame_top;
  puVar1 = &else_node->desc->flags7;
  *puVar1 = *puVar1 | node->desc->flags7 & 0x40;
  desc = else_node->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    else_node->desc->fpref_regs = node->desc->fpref_regs;
  }
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    restore_fpscr_pr_state();
  }
  restore_register_contents();
  dispatch_and_finalize_code_node(else_node);
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    pop_fpscr_pr_state();
    g_fpscr_pr = '\x02';
  }
  drop_saved_register_contents();
  invalidate_register_contents(0xf000f);
  if ((((node->type & 0xe0) == 0x60) && (bVar3 = (node->desc->dest).type & 0x1f, bVar3 != 0)) &&
     (bVar3 == 1)) {
    operand = &then_node->desc->value;
    operand->type = operand->type | 0x40;
    operand = &else_node->desc->value;
    operand->type = operand->type | 0x40;
  }
  bVar3 = (node->desc->value).type;
  operand = &node->desc->value;
  if ((bVar3 & 0x1f) == 0) goto LAB_0040e82a;
  node_type = node->type;
  if ((((node_type & 0xe0) == 0x60) && (((node->desc->dest).type & 0x1f) == 0)) &&
     ((node->desc->flags2 & 8) == 0)) {
    operand->type = bVar3 & 0xf8 | 8;
    node->desc->opnd_class = '\x03';
    operand = &then_node->desc->value;
    operand->type = operand->type | 0x40;
    operand = &else_node->desc->value;
    operand->type = operand->type | 0x40;
    operand = &node->desc->value;
  }
  else {
    sVar4 = g_request->cpu;
    if ((sVar4 == 4) && ((node_type & 0xf8) == 0x30)) {
      reg_mask = ea_register_mask(operand);
      sVar4 = float_mask_to_register((ushort)(reg_mask >> 0x10));
      mask = 1 << ((char)sVar4 - 0x1fU & 0x1f);
      pair_mask = 1 << ((char)sVar4 - 0x20U & 0x1f);
      puVar2 = &node->desc->fbusy_regs;
      *puVar2 = *puVar2 | mask | pair_mask;
      g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
      puVar2 = &node->desc->ftemp_regs;
      *puVar2 = *puVar2 | mask | pair_mask;
      goto LAB_0040e82a;
    }
    if ((sVar4 == 2) && (g_request->fpu_mode == '\x03')) {
      bVar3 = 1;
    }
    else {
      bVar3 = -(sVar4 == 4) & 2;
    }
    if ((bVar3 != 0) && ((node_type & 0xf8) == 0x28)) {
      reg_mask = ea_register_mask(operand);
      sVar4 = float_mask_to_register((ushort)(reg_mask >> 0x10));
      mask = 1 << ((char)sVar4 - 0x10U & 0x1f);
      puVar2 = &node->desc->fbusy_regs;
      *puVar2 = *puVar2 | mask;
      g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
      puVar2 = &node->desc->ftemp_regs;
      *puVar2 = *puVar2 | mask;
      goto LAB_0040e82a;
    }
  }
  reg_mask = ea_register_mask(operand);
  sVar4 = mask_to_register(reg_mask);
  mask = 1 << ((byte)sVar4 & 0x1f);
  puVar2 = &node->desc->busy_regs;
  *puVar2 = *puVar2 | mask;
  g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
  puVar2 = &node->desc->temp_regs;
  *puVar2 = *puVar2 | mask;
LAB_0040e82a:
  sVar4 = choose_general_register(node->desc->busy_regs,0,'\0');
  if (sVar4 == -1) {
    cVar5 = '\0';
    mask = 0;
    reg_mask = ea_register_mask(&node->desc->value);
    sVar4 = choose_general_register((ushort)reg_mask,mask,cVar5);
  }
  node->desc->regs_2c[0] = (byte)sVar4;
  puVar2 = &node->desc->temp_regs;
  *puVar2 = *puVar2 | 1 << ((byte)sVar4 & 0x1f);
  return;
}



