#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00401c90
// name : prepare_comparison_node
// size : 658
// sig  : void prepare_comparison_node(gen_node * node)


int __cdecl prepare_comparison_node(gen_node *node)

{
  short reg;
  uint excluded;
  byte bVar1;
  ushort mask;
  ushort preferred;
  undefined **select;
  char cVar2;
  gen_node *child;
  node_desc *desc;
  il_op op;
  ushort *regs_p;
  
  child = node->child;
  op = node->op;
  if ((child->type & 0xe0) == 0x20) {
    if ((op == IL_EQ) || (op == IL_NE)) {
LAB_00401cca:
      select = &g_compare_eq_select;
    }
    else {
      select = &g_compare_rel_select;
    }
  }
  else {
    if ((op == IL_EQ) || (op == IL_NE)) goto LAB_00401cca;
    select = &g_compare_rel_select;
  }
  generate_operator_by_template(node,(tmpl_select *)select,'\x01');
  desc = node->desc;
  if (desc->usage != '\x01') {
    if (((desc->value).type & 0x1f) != 0) {
      return;
    }
    bVar1 = child->type & 0xf8;
    if ((bVar1 == 0x30) && (g_request->cpu != 4)) {
LAB_00401de1:
      bVar1 = 0;
    }
    else {
      if (bVar1 == 0x28) {
        if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
          bVar1 = 1;
        }
        else {
          bVar1 = -(g_request->cpu == 4) & 2;
        }
        if (bVar1 == 0) goto LAB_00401de1;
      }
      bVar1 = (desc->dest).type & 0x1f;
      if ((bVar1 == 0) || (bVar1 != 1)) {
        if (desc->target_regs == 0) {
          mask = desc->pref_regs;
          if (mask == 0) {
            mask = 1;
          }
          cVar2 = '\x01';
          preferred = mask;
          excluded = result_reg_exclusion_mask(node);
          reg = choose_general_register((ushort)excluded,preferred,cVar2);
          if (reg == -1) {
            reg = choose_general_register(0,mask,'\x01');
          }
          bVar1 = (byte)reg;
          node->desc->opnd_class = '\0';
        }
        else {
          reg = mask_to_register((int)(short)desc->target_regs);
          bVar1 = (byte)reg;
          node->desc->opnd_class = '\x01';
        }
      }
      else {
        bVar1 = (desc->dest).base;
        if (((((char)bVar1 < '\x0f') && ((1 << (bVar1 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0))
            || (((char)bVar1 < ' ' &&
                (('\x0f' < (char)bVar1 &&
                 ((1 << (bVar1 - 0x10 & 0x1f) & (int)(short)~g_var_fpr_mask) != 0)))))) ||
           (((char)bVar1 < '/' &&
            (('\x1f' < (char)bVar1 &&
             (((int)(short)g_var_fpr_mask &
              (1 << (bVar1 - 0x1f & 0x1f) | 1 << (bVar1 - 0x20 & 0x1f))) == 0)))))) {
          desc->opnd_class = '\0';
        }
        else {
          desc->opnd_class = '\x01';
        }
      }
    }
    fill_ea(&node->desc->value,'\x01',bVar1,-1,'\0',0,(label_ref *)0x0);
    mask = 1 << (bVar1 & 0x1f);
    regs_p = &node->desc->busy_regs;
    *regs_p = *regs_p | mask;
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    regs_p = &node->desc->temp_regs;
    *regs_p = *regs_p | mask;
    return;
  }
  bVar1 = child->type & 0xf8;
  if ((bVar1 == 0x30) && (g_request->cpu != 4)) {
LAB_00401d35:
    reg = 0;
  }
  else {
    if (bVar1 == 0x28) {
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(g_request->cpu == 4) & 2;
      }
      if (bVar1 == 0) goto LAB_00401d35;
    }
    mask = desc->pref_regs;
    cVar2 = '\0';
    excluded = result_reg_exclusion_mask(node);
    reg = choose_general_register((ushort)excluded,mask,cVar2);
    if (reg == -1) {
      reg = choose_general_register(0,node->desc->pref_regs,'\0');
    }
  }
  regs_p = &node->desc->temp_regs;
  *regs_p = *regs_p | 1 << ((byte)reg & 0x1f);
  node->desc->cond_regs[0] = (byte)reg;
  return;
}



