#include "decls.h"
#include "imports.h"

// entry: 004034e0
// name : prepare_bit_field_node
// size : 759
// sig  : void prepare_bit_field_node(gen_node * node)


int __cdecl prepare_bit_field_node(gen_node *node)

{
  tmpl_header *tmpl;
  uint excluded;
  ea *operand;
  byte bVar1;
  byte ea_kind;
  node_desc *child_desc;
  gen_node *child_node;
  node_desc *desc;
  int *disp_p;
  uchar *flags_p;
  gen_node *parent_node;
  ushort *regs_p;
  
  child_node = node->child;
  parent_node = node->parent;
  node->desc->bit_offset = node->bit_offset;
  node->desc->bit_width = node->bit_width;
  tmpl = select_bit_field_load_template(node);
  node->desc->tmpl = tmpl;
  apply_template_operand_constraints(node);
  child_node->desc->busy_regs = node->desc->busy_regs;
  child_node->desc->fbusy_regs = node->desc->fbusy_regs;
  child_node->desc->frame_top = node->desc->frame_top;
  flags_p = &child_node->desc->flags7;
  *flags_p = *flags_p | node->desc->flags7 & 0x40;
  tmpl = node->desc->tmpl;
  if (tmpl != (tmpl_header *)0x0) {
    regs_p = &child_node->desc->busy_regs;
    *regs_p = *regs_p & ~(ushort)tmpl->clobbers;
  }
  child_node->desc->pref_regs = 4;
  dispatch_and_finalize_code_node(child_node);
  flags_p = &node->desc->flags2;
  *flags_p = *flags_p | 0x10;
  desc = node->desc;
  if (desc->usage != '\x03') {
    tmpl = select_bit_field_load_template(node);
    desc->tmpl = tmpl;
    child_node = node;
    excluded = result_reg_exclusion_mask(node);
    apply_template_to_node(node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,excluded,child_node);
    return;
  }
  parent_node->desc->bit_offset = desc->bit_offset;
  parent_node->desc->bit_width = node->desc->bit_width;
  flags_p = &parent_node->desc->flags2;
  *flags_p = *flags_p | 0x10;
  if (parent_node->op == IL_ASSIGN) {
    node->desc->tmpl = (tmpl_header *)0x0;
    flags_p = &node->next->desc->flags2;
    *flags_p = *flags_p | 0x10;
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
    bVar1 = (node->desc->value).type;
    ea_kind = bVar1 & 0x1f;
    if ((ea_kind == 2) || (ea_kind == 8)) {
      (node->desc->value).type = bVar1 & 0xf8 | 8;
    }
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 0x80;
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 8;
    return;
  }
  tmpl = select_bit_field_load_template(node);
  node->desc->tmpl = tmpl;
  parent_node = node;
  excluded = result_reg_exclusion_mask(node);
  apply_template_to_node(node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,excluded,parent_node);
  desc = node->desc;
  operand = copy_ea(&desc->value);
  desc->saved_ea = operand;
  desc = node->desc;
  if ((desc->tmpl->flags & 0x20) == 0) {
    child_desc = child_node->desc;
    bVar1 = 0;
    operand = child_desc->mem_ea;
    if (operand != (ea *)0x0) {
      bVar1 = operand->type & 0x1f;
    }
    if (((bVar1 == 0) && (operand = &child_desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (child_desc->flags2 & 8) == 0)) {
      operand = &child_desc->value;
    }
    copy_ea_into(&desc->value,operand);
    regs_p = &node->desc->busy_regs;
    *regs_p = *regs_p | child_node->desc->busy_regs;
    node->desc->frame_top = child_node->desc->frame_top;
    node->desc->opnd_class = child_node->desc->opnd_class;
    disp_p = &(node->desc->value).disp;
    *disp_p = *disp_p + node->val2;
  }
  else {
    fill_ea(&desc->value,'\b','\x02',-1,'\0',0,(label_ref *)0x0);
    regs_p = &node->desc->busy_regs;
    *(byte *)regs_p = (byte)*regs_p | 4;
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    regs_p = &node->desc->temp_regs;
    *(byte *)regs_p = (byte)*regs_p | 4;
  }
  node->desc->opnd_class = '\x03';
  return;
}



