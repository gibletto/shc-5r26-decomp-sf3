#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040e880
// name : generate_comma_node
// size : 996
// sig  : void generate_comma_node(gen_node * node)


int __cdecl generate_comma_node(gen_node *node)

{
  uchar *puVar1;
  byte ea_kind;
  short reg;
  ea *operand;
  gen_node *right;
  byte base_reg;
  node_desc *desc;
  bool dest_passed;
  gen_node *left;
  
  dest_passed = false;
  right = (gen_node *)0x0;
  left = node->child;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  desc = node->desc;
  if (desc->usage == '\x01') {
    right->desc->false_label = desc->false_label;
    right->desc->true_label = node->desc->true_label;
  }
  else if ((desc->flags2 & 8) == 0) {
    if ((desc->flags3 & 0x20) != 0) {
      puVar1 = &right->desc->flags3;
      *puVar1 = *puVar1 | 0x20;
      copy_ea_into(&right->desc->dest,&node->desc->dest);
      puVar1 = &node->desc->flags3;
      *puVar1 = *puVar1 & 0xdf;
      operand = &node->desc->dest;
      operand->type = operand->type & 0xf0;
      goto LAB_0040ead9;
    }
    if (desc->target_regs != 0) {
      reg = mask_to_register((int)(short)desc->target_regs);
      fill_ea(&right->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
      fill_ea(&node->desc->value,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
      node->desc->opnd_class = '\x01';
      goto LAB_0040eae1;
    }
    if (desc->ftarget_regs != 0) {
      reg = float_mask_to_register(desc->ftarget_regs);
      fill_ea(&right->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
      fill_ea(&node->desc->value,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
      node->desc->opnd_class = '\x01';
      goto LAB_0040eae1;
    }
    operand = &desc->dest;
    ea_kind = operand->type & 0x1f;
    if ((((ea_kind != 0) && ((node->type & 0xe0) == 0x60)) && (ea_kind == 1)) || (ea_kind == 0))
    goto LAB_0040eae1;
    if ((ea_kind == 2) || (ea_kind == 8)) {
      base_reg = (desc->dest).base;
      if ((char)base_reg < '\x0f') {
        if (((int)(short)~g_var_gpr_mask & 1 << (base_reg & 0x1f)) == 0) goto LAB_0040ea25;
LAB_0040eaa2:
        if (((ea_kind == 0) || (operand->type = operand->type & 0xf0, g_request->cpu == 4)) ||
           ((node->type & 0xf8) != 0x30)) goto LAB_0040eae1;
        puVar1 = &right->desc->flags2;
        *puVar1 = *puVar1 | 8;
        puVar1 = &node->desc->flags2;
        *puVar1 = *puVar1 | 8;
        goto LAB_0040ead2;
      }
LAB_0040ea25:
      if (((char)base_reg < ' ') && ('\x0f' < (char)base_reg)) {
        if ((1 << (base_reg - 0x10 & 0x1f) & (int)(short)~g_var_fpr_mask) != 0) goto LAB_0040eaa2;
      }
      if (((char)base_reg < '/') && ('\x1f' < (char)base_reg)) {
        if (((int)(short)g_var_fpr_mask &
            (1 << (base_reg - 0x1f & 0x1f) | 1 << (base_reg - 0x20 & 0x1f))) == 0)
        goto LAB_0040eaa2;
      }
    }
    copy_ea_into(&right->desc->dest,operand);
  }
  else {
    puVar1 = &right->desc->flags2;
    *puVar1 = *puVar1 | 8;
LAB_0040ead2:
    node->desc->opnd_class = '\x03';
  }
LAB_0040ead9:
  dest_passed = true;
LAB_0040eae1:
  left->desc->busy_regs = node->desc->busy_regs;
  left->desc->fbusy_regs = node->desc->fbusy_regs;
  left->desc->frame_top = node->desc->frame_top;
  puVar1 = &left->desc->flags7;
  *puVar1 = *puVar1 | node->desc->flags7 & 0x40;
  desc = left->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    left->desc->fpref_regs = node->desc->fpref_regs;
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
  if ((node->desc->usage != '\0') && (!dest_passed)) {
    if (right->desc->opnd_class == '\x02') {
      puVar1 = &node->desc->flags3;
      *puVar1 = *puVar1 | 8;
      if (node->desc->tmpl == (tmpl_header *)0x0) {
        puVar1 = &node->desc->flags3;
        *puVar1 = *puVar1 | 0x80;
      }
    }
    node->desc->busy_regs = right->desc->busy_regs;
    node->desc->fbusy_regs = right->desc->fbusy_regs;
    node->desc->frame_top = right->desc->frame_top;
    desc = right->desc;
    ea_kind = 0;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      ea_kind = operand->type & 0x1f;
    }
    if (((ea_kind == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    copy_ea_into(&node->desc->value,operand);
    node->desc->opnd_class = right->desc->opnd_class;
  }
  return;
}



