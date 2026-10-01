#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040efd0
// name : generate_logical_or_node
// size : 847
// sig  : void generate_logical_or_node(gen_node * node)


int __cdecl generate_logical_or_node(gen_node *node)

{
  uchar *puVar1;
  ushort *puVar2;
  byte bVar3;
  short sVar4;
  uint reg_mask;
  ushort mask;
  node_desc **left_desc_ptr;
  gen_node *right;
  char ascending;
  node_desc *desc;
  short false_label;
  gen_node *left;
  
  right = (gen_node *)0x0;
  left = node->child;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  if (node->desc->true_label == 0) {
    sVar4 = make_new_label_number();
    left->desc->true_label = sVar4;
    if ((node->desc->usage == '\x01') && (false_label = node->desc->false_label, false_label != 0))
    {
      right->desc->false_label = false_label;
      goto LAB_0040f054;
    }
  }
  else {
    left->desc->false_label = node->desc->false_label;
    left->desc->true_label = node->desc->true_label;
    right->desc->false_label = node->desc->false_label;
    sVar4 = node->desc->true_label;
  }
  right->desc->true_label = sVar4;
LAB_0040f054:
  left_desc_ptr = &left->desc;
  (*left_desc_ptr)->busy_regs = node->desc->busy_regs;
  (*left_desc_ptr)->fbusy_regs = node->desc->fbusy_regs;
  (*left_desc_ptr)->frame_top = node->desc->frame_top;
  (*left_desc_ptr)->flags7 = (*left_desc_ptr)->flags7 | node->desc->flags7 & 0x40;
  desc = *left_desc_ptr;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    (*left_desc_ptr)->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(left);
  right->desc->busy_regs = node->desc->busy_regs;
  right->desc->fbusy_regs = node->desc->fbusy_regs;
  right->desc->frame_top = node->desc->frame_top;
  puVar1 = &right->desc->flags7;
  *puVar1 = *puVar1 | node->desc->flags7 & 0x40;
  desc = right->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    right->desc->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(right);
  if (((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) &&
     (right->desc->fpscr_pr != (*left_desc_ptr)->fpscr_pr)) {
    g_fpscr_pr = '\x02';
  }
  if ((node->parent == (gen_node *)0x0) || (node->parent->op != IL_OR)) {
    invalidate_register_contents(0xf000f);
  }
  if (((*left_desc_ptr)->opnd_class == '\x02') && (right->desc->opnd_class == '\x02')) {
    fold_constant_node(node);
    return;
  }
  desc = node->desc;
  if (desc->usage == '\x02') {
    bVar3 = (desc->dest).type & 0x1f;
    if ((bVar3 == 0) || (bVar3 != 1)) {
      if (desc->target_regs == 0) {
        mask = desc->pref_regs;
        ascending = '\0';
        reg_mask = result_reg_exclusion_mask(node);
        sVar4 = choose_general_register((ushort)reg_mask,mask,ascending);
        if (sVar4 == -1) {
          sVar4 = choose_general_register
                            (0,right->desc->temp_regs | (*left_desc_ptr)->temp_regs,'\0');
        }
        bVar3 = (byte)sVar4;
        node->desc->opnd_class = '\0';
      }
      else {
        sVar4 = mask_to_register((int)(short)desc->target_regs);
        bVar3 = (byte)sVar4;
        node->desc->opnd_class = '\x01';
      }
    }
    else {
      bVar3 = (desc->dest).base;
      if (((((char)bVar3 < '\x0f') && ((1 << (bVar3 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)) ||
          (((char)bVar3 < ' ' &&
           (('\x0f' < (char)bVar3 &&
            (((int)(short)~g_var_fpr_mask & 1 << (bVar3 - 0x10 & 0x1f)) != 0)))))) ||
         (((char)bVar3 < '/' &&
          (('\x1f' < (char)bVar3 &&
           (((int)(short)g_var_fpr_mask & (1 << (bVar3 - 0x1f & 0x1f) | 1 << (bVar3 - 0x20 & 0x1f)))
            == 0)))))) {
        desc->opnd_class = '\0';
      }
      else {
        desc->opnd_class = '\x01';
      }
    }
    fill_ea(&node->desc->value,'\x01',bVar3,-1,'\0',0,(label_ref *)0x0);
    mask = 1 << (bVar3 & 0x1f);
    puVar2 = &node->desc->busy_regs;
    *puVar2 = *puVar2 | mask;
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    puVar2 = &node->desc->temp_regs;
    *puVar2 = *puVar2 | mask;
    sVar4 = choose_general_register(node->desc->busy_regs,0,'\0');
    if (sVar4 == -1) {
      ascending = '\0';
      mask = 0;
      reg_mask = ea_register_mask(&node->desc->value);
      sVar4 = choose_general_register((ushort)reg_mask,mask,ascending);
    }
    node->desc->regs_2c[0] = (byte)sVar4;
    puVar2 = &node->desc->temp_regs;
    *puVar2 = *puVar2 | 1 << ((byte)sVar4 & 0x1f);
  }
  return;
}



