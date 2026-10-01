#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00402d90
// name : prepare_address_of_node
// size : 1036
// sig  : void prepare_address_of_node(gen_node * node)


int __cdecl prepare_address_of_node(gen_node *node)

{
  byte bVar1;
  uint uVar2;
  ea *src;
  ea *operand;
  gen_node *account_node;
  gen_node *child;
  node_desc *desc;
  uchar *flags_p;
  
  child = node->child;
  child->desc->busy_regs = node->desc->busy_regs;
  child->desc->fbusy_regs = node->desc->fbusy_regs;
  child->desc->frame_top = node->desc->frame_top;
  flags_p = &child->desc->flags7;
  *flags_p = *flags_p | node->desc->flags7 & 0x40;
  desc = child->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    child->desc->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(child);
  desc = child->desc;
  bVar1 = 0;
  operand = desc->mem_ea;
  if (operand != (ea *)0x0) {
    bVar1 = operand->type & 0x1f;
  }
  if (((bVar1 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
     (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    operand = &desc->value;
  }
  if ((child->type & 0xe0) == 0x80) {
    if (desc->opnd_class == '\x02') {
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p | 8;
      if (node->desc->tmpl == (tmpl_header *)0x0) {
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
      }
    }
    node->desc->busy_regs = child->desc->busy_regs;
    node->desc->fbusy_regs = child->desc->fbusy_regs;
    node->desc->frame_top = child->desc->frame_top;
    bVar1 = 0;
    desc = child->desc;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      bVar1 = operand->type & 0x1f;
    }
    if (((bVar1 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    copy_ea_into(&node->desc->value,operand);
    node->desc->opnd_class = child->desc->opnd_class;
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 0x80;
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 8;
  }
  else {
    bVar1 = operand->type & 0x1f;
    if (bVar1 == 0xd) {
      if (operand->labels == (label_ref *)0x0) {
        uVar2 = 0;
      }
      else {
        uVar2 = (uint)operand->labels->labno1;
      }
      if ((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 1) == 0) {
        if (desc->opnd_class == '\x02') {
          flags_p = &node->desc->flags3;
          *flags_p = *flags_p | 8;
          if (node->desc->tmpl == (tmpl_header *)0x0) {
            flags_p = &node->desc->flags3;
            *flags_p = *flags_p | 0x80;
          }
        }
        node->desc->busy_regs = child->desc->busy_regs;
        node->desc->fbusy_regs = child->desc->fbusy_regs;
        node->desc->frame_top = child->desc->frame_top;
        bVar1 = 0;
        desc = child->desc;
        operand = desc->mem_ea;
        if (operand != (ea *)0x0) {
          bVar1 = operand->type & 0x1f;
        }
        if (((bVar1 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
           (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          operand = &desc->value;
        }
        copy_ea_into(&node->desc->value,operand);
        node->desc->opnd_class = child->desc->opnd_class;
        operand = &node->desc->value;
        operand->type = operand->type & 0xbf;
        (node->desc->value).type = (node->desc->value).type & 0xf7 | 7;
        desc = node->desc;
        if ((((desc->value).type & 0x1f) == 7) && ((desc->value).labels != (label_ref *)0x0)) {
          desc->opnd_class = '\x03';
        }
        else {
          desc->opnd_class = '\x02';
        }
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 8;
        goto LAB_0040318a;
      }
      node->desc->tmpl = (tmpl_header *)&g_tmpl_aamper002;
    }
    else {
      if (((bVar1 == 2) ||
          (((bVar1 == 8 && (operand->disp == 0)) && (operand->labels == (label_ref *)0x0)))) &&
         (operand->base != 'l')) {
        if (desc->opnd_class == '\x02') {
          flags_p = &node->desc->flags3;
          *flags_p = *flags_p | 8;
          if (node->desc->tmpl == (tmpl_header *)0x0) {
            flags_p = &node->desc->flags3;
            *flags_p = *flags_p | 0x80;
          }
        }
        node->desc->busy_regs = child->desc->busy_regs;
        node->desc->fbusy_regs = child->desc->fbusy_regs;
        node->desc->frame_top = child->desc->frame_top;
        bVar1 = 0;
        desc = child->desc;
        src = desc->mem_ea;
        if (src != (ea *)0x0) {
          bVar1 = src->type & 0x1f;
        }
        if (((bVar1 == 0) && (src = &desc->dest, (src->type & 0x1f) == 0)) &&
           (src = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          src = &desc->value;
        }
        copy_ea_into(&node->desc->value,src);
        node->desc->opnd_class = child->desc->opnd_class;
        src = &node->desc->value;
        src->type = src->type & 0xf1 | 1;
        bVar1 = operand->base;
        if ((((char)bVar1 < '\x0f') && ((1 << (bVar1 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0))
           || ((((char)bVar1 < ' ' &&
                (('\x0f' < (char)bVar1 &&
                 ((1 << (bVar1 - 0x10 & 0x1f) & (int)(short)~g_var_fpr_mask) != 0)))) ||
               (((char)bVar1 < '/' &&
                (('\x1f' < (char)bVar1 &&
                 (((int)(short)g_var_fpr_mask &
                  (1 << (bVar1 - 0x1f & 0x1f) | 1 << (bVar1 - 0x20 & 0x1f))) == 0)))))))) {
          node->desc->opnd_class = '\0';
        }
        else {
          node->desc->opnd_class = '\x01';
        }
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 8;
        goto LAB_0040318a;
      }
      node->desc->tmpl = (tmpl_header *)&g_tmpl_aamper001;
    }
    account_node = node;
    uVar2 = result_reg_exclusion_mask(node);
    apply_template_to_node(node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,uVar2,account_node);
  }
LAB_0040318a:
  if (child->op == IL_ID) {
    forget_register_copies_of_variable(child);
  }
  return;
}



