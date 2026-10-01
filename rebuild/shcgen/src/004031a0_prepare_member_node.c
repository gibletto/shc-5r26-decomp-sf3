#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004031a0
// name : prepare_member_node
// size : 818
// sig  : void prepare_member_node(gen_node * node)


int __cdecl prepare_member_node(gen_node *node)

{
  byte bVar1;
  uint operand_regs;
  ea *operand;
  ushort reg_bit;
  node_desc *child_desc;
  gen_node *child_node;
  node_desc *desc;
  int *disp_p;
  uchar *flags_p;
  il_op parent_op;
  ushort *regs_p;
  
  child_node = node->child;
  child_node->desc->busy_regs = node->desc->busy_regs;
  child_node->desc->fbusy_regs = node->desc->fbusy_regs;
  child_node->desc->frame_top = node->desc->frame_top;
  flags_p = &child_node->desc->flags7;
  *flags_p = *flags_p | node->desc->flags7 & 0x40;
  desc = child_node->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    child_node->desc->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(child_node);
  if ((g_r0_variable == 0) && (desc = node->desc, desc->usage == '\x03')) {
    child_desc = child_node->desc;
    bVar1 = (child_desc->value).type & 0x1f;
    if ((((bVar1 == 2) || (bVar1 == 8)) &&
        (((parent_op = node->parent->op, '7' < (char)parent_op && ((char)parent_op < '>')) ||
         (('O' < (char)parent_op && ((char)parent_op < '`')))))) &&
       (((parent_op != IL_ASSIGN && ((child_desc->value).base != 'l')) &&
        ((bVar1 = node->type, (bVar1 & 0xe0) == 0 ||
         (((bVar1 & 0xf8) == 0x28 || ((bVar1 & 0xf8) == 0x40)))))))) {
      if ((((child_desc->value).labels != (label_ref *)0x0) ||
          ((bVar1 = bVar1 & 0xf8, bVar1 == 0 && (0xf < node->val2 + (child_desc->value).disp)))) ||
         ((bVar1 == 8 && (0x1e < node->val2 + (child_desc->value).disp)))) {
LAB_004032fd:
        if ((child_desc->value).base == '\0') {
          desc->tmpl = (tmpl_header *)&g_tmpl_aqual001;
          bVar1 = 0xff;
        }
        else {
          desc->tmpl = (tmpl_header *)&g_tmpl_aqual002;
          bVar1 = (child_node->desc->value).base;
        }
        child_node = node;
        operand_regs = result_reg_exclusion_mask(node);
        apply_template_to_node
                  (node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,operand_regs,child_node);
        if (bVar1 == 0xff) {
          bVar1 = node->desc->regs_2c[0];
        }
        fill_ea(&node->desc->value,'\x01',bVar1,-1,'\0',0,(label_ref *)0x0);
        (node->desc->value).index = '\0';
        (node->desc->value).type = (node->desc->value).type & 0xf9 | 9;
        node->desc->opnd_class = '\x03';
        reg_bit = 1 << (bVar1 & 0x1f);
        regs_p = &node->desc->busy_regs;
        *regs_p = *regs_p | reg_bit;
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
        regs_p = &node->desc->temp_regs;
        *regs_p = *regs_p | reg_bit;
        regs_p = &node->desc->busy_regs;
        *(byte *)regs_p = (byte)*regs_p | 1;
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
        regs_p = &node->desc->temp_regs;
        *(byte *)regs_p = (byte)*regs_p | 1;
        return;
      }
      if (bVar1 == 0x28) {
        if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
          bVar1 = 1;
        }
        else {
          bVar1 = -(g_request->cpu == 4) & 2;
        }
        if ((bVar1 != 0) && (0 < node->val2 + (child_desc->value).disp)) goto LAB_004032fd;
      }
      if (0x3c < node->val2 + (child_desc->value).disp) goto LAB_004032fd;
    }
  }
  if (child_node->desc->opnd_class == '\x02') {
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 8;
    if (node->desc->tmpl == (tmpl_header *)0x0) {
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p | 0x80;
    }
  }
  node->desc->busy_regs = child_node->desc->busy_regs;
  node->desc->fbusy_regs = child_node->desc->fbusy_regs;
  node->desc->frame_top = child_node->desc->frame_top;
  bVar1 = 0;
  desc = child_node->desc;
  operand = desc->mem_ea;
  if (operand != (ea *)0x0) {
    bVar1 = operand->type & 0x1f;
  }
  if (((bVar1 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
     (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    operand = &desc->value;
  }
  copy_ea_into(&node->desc->value,operand);
  node->desc->opnd_class = child_node->desc->opnd_class;
  disp_p = &(node->desc->value).disp;
  *disp_p = *disp_p + node->val2;
  if ((node->type & 0xe0) == 0x80) {
    if (((node->parent != (gen_node *)0x0) && (node->parent->op == IL_AMPER)) ||
       (node->desc->usage != '\x03')) {
      bVar1 = (node->desc->value).type;
      if ((bVar1 & 0x1f) == 0xd) {
        (node->desc->value).type = bVar1 & 0xf7 | 7;
        desc = node->desc;
        if ((desc->value).labels == (label_ref *)0x0) {
          desc->opnd_class = '\x02';
        }
        else {
          desc->opnd_class = '\x03';
        }
        goto LAB_004034c0;
      }
    }
    operand = &node->desc->value;
    operand->type = operand->type | 0x40;
  }
LAB_004034c0:
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 0x80;
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 8;
  return;
}



