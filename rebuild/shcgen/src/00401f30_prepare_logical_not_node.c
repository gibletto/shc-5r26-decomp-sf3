#include "decls.h"
#include "imports.h"

// entry: 00401f30
// name : prepare_logical_not_node
// size : 711
// sig  : void prepare_logical_not_node(gen_node * node)


int __cdecl prepare_logical_not_node(gen_node *node)

{
  char cVar1;
  byte ea_kind;
  short sVar2;
  uint operand_regs;
  ea *src;
  char builtin;
  char child_class;
  gen_node *child_node;
  il_op child_op;
  node_desc *desc;
  uchar *flags_p;
  ushort *regs_p;
  tmpl_header *tmpl;
  
  child_node = node->child;
  desc = node->desc;
  if (((desc->usage != '\x01') && (node->parent != (gen_node *)0x0)) && (node->parent->op != IL_NOT)
     ) {
    sVar2 = make_new_label_number();
    desc->true_label = sVar2;
  }
  child_node->desc->true_label = node->desc->false_label;
  child_node->desc->false_label = node->desc->true_label;
  desc = node->desc;
  if (desc->usage != '\0') {
    child_op = child_node->op;
    if (((child_op == IL_NOT) || (('_' < (char)child_op && ((char)child_op < 'j')))) ||
       ((child_op == IL_CALL &&
        ((cVar1 = child_node->desc->builtin, cVar1 == '\x10' || (cVar1 == '\x14')))))) {
      if (desc->usage == '\x02') {
        ea_kind = (desc->dest).type & 0x1f;
        if ((ea_kind == 0) || (ea_kind != 1)) {
          if (desc->target_regs != 0) {
            sVar2 = mask_to_register((int)(short)desc->target_regs);
            fill_ea(&child_node->desc->dest,'\x01',(char)sVar2,-1,'\0',0,(label_ref *)0x0);
          }
        }
        else {
          copy_ea_into(&child_node->desc->dest,&desc->dest);
        }
      }
    }
    else {
      select_node_template(node,(tmpl_select *)&g_not_select,'\x01','\x01',&desc->tmpl);
      apply_template_operand_constraints(node);
    }
  }
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
  tmpl = node->desc->tmpl;
  if (tmpl != (tmpl_header *)0x0) {
    regs_p = &child_node->desc->busy_regs;
    *regs_p = *regs_p & ~(ushort)tmpl->clobbers;
  }
  dispatch_and_finalize_code_node(child_node);
  if ((child_node->desc->flags2 & 0x20) != 0) {
    flags_p = &node->desc->flags2;
    *flags_p = *flags_p | 0x20;
  }
  desc = node->desc;
  cVar1 = desc->usage;
  if (cVar1 == '\x01') {
    desc->flags3 = desc->flags3 | 0x80;
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 8;
    return;
  }
  child_class = child_node->desc->opnd_class;
  if (child_class == '\x02') {
    fold_constant_node(node);
    return;
  }
  if ((((cVar1 != '\0') && (child_op = child_node->op, child_op != IL_NOT)) &&
      (((char)child_op < '`' || ('i' < (char)child_op)))) &&
     ((child_op != IL_CALL ||
      ((builtin = child_node->desc->builtin, builtin != '\x10' && (builtin != '\x14')))))) {
    select_node_template(node,(tmpl_select *)&g_not_select,'\x01','\0',&desc->tmpl);
    child_node = node;
    operand_regs = result_reg_exclusion_mask(node);
    apply_template_to_node(node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,operand_regs,child_node)
    ;
    return;
  }
  if (cVar1 == '\x02') {
    if (child_class == '\x02') {
      desc->flags3 = desc->flags3 | 8;
      if (node->desc->tmpl == (tmpl_header *)0x0) {
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
      }
    }
    node->desc->busy_regs = child_node->desc->busy_regs;
    node->desc->fbusy_regs = child_node->desc->fbusy_regs;
    node->desc->frame_top = child_node->desc->frame_top;
    ea_kind = 0;
    desc = child_node->desc;
    src = desc->mem_ea;
    if (src != (ea *)0x0) {
      ea_kind = src->type & 0x1f;
    }
    if (((ea_kind == 0) && (src = &desc->dest, (src->type & 0x1f) == 0)) &&
       (src = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      src = &desc->value;
    }
    copy_ea_into(&node->desc->value,src);
    node->desc->opnd_class = child_node->desc->opnd_class;
  }
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 0x80;
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 8;
  return;
}



