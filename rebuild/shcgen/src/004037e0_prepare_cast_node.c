#include "decls.h"
#include "imports.h"
int shcgen_knob_mul_l(void);
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004037e0
// name : prepare_cast_node
// size : 2775
// sig  : void prepare_cast_node(gen_node * node)


int __cdecl prepare_cast_node(gen_node *node)

{
  bool bVar1;
  short reg;
  int iVar2;
  int iVar3;
  int iVar4;
  gen_node *other_operand;
  uint operand_regs;
  byte bVar5;
  ea *peVar6;
  byte bVar7;
  ea *operand;
  int other_signed;
  int child_signed;
  gen_node *child_node;
  byte child_type;
  node_desc *desc;
  int *disp_p;
  uchar *flags_p;
  gen_node *parent;
  il_op parent_op;
  char usage;
  
  bVar1 = false;
  child_node = node->child;
  parent = node->parent;
  iVar2 = node_value_size(node);
  iVar3 = node_value_size(child_node);
  if ((parent != (gen_node *)0x0) && (parent->op == IL_MUL)) {
    bVar5 = parent->type & 0xf8;
    if (((bVar5 == 0x10) || ((bVar5 == 0x18 || ((parent->type & 0xe0) == 0x40)))) &&
       ((child_node->type & 0xf8) == 8)) {
      iVar4 = operand_position(node);
      other_operand = nth_operand(parent,(iVar4 == 1) + 1);
      if (other_operand->op == IL_CAST) {
        bVar5 = other_operand->child->type;
        bVar7 = bVar5 & 0xf8;
        if ((bVar7 != 0) && (bVar7 != 8)) goto LAB_00403953;
        child_type = child_node->type;
        if (((child_type & 4) == 0) &&
           (((child_type & 0xe0) != 0x80 && ((child_type & 0xe0) != 0x40)))) {
          child_signed = 0;
        }
        else {
          child_signed = 1;
        }
        if ((((bVar5 & 4) == 0) && ((bVar5 & 0xe0) != 0x80)) && ((bVar5 & 0xe0) != 0x40)) {
          other_signed = 0;
        }
        else {
          other_signed = 1;
        }
        if ((child_signed != other_signed) &&
           (((((child_type & 4) != 0 || ((child_type & 0xe0) == 0x80)) ||
             ((child_type & 0xe0) == 0x40)) ||
            ((bVar7 == 8 &&
             ((((bVar5 & 4) != 0 || ((bVar5 & 0xe0) == 0x80)) || ((bVar5 & 0xe0) == 0x40))))))))
        goto LAB_00403953;
      }
      else {
LAB_00403953:
        if ((((child_node->type & 4) != 0) || (bVar5 = child_node->type & 0xe0, bVar5 == 0x80)) ||
           (iVar4 = 0, bVar5 == 0x40)) {
          iVar4 = 1;
        }
        iVar4 = (shcgen_knob_mul_l() & 4) ? 0 : is_16bit_multiplier_constant(other_operand,iVar4);
        if (iVar4 == 0) goto LAB_0040398d;
      }
      bVar1 = true;
      node->type = child_node->type;
    }
  }
LAB_0040398d:
  desc = node->desc;
  usage = desc->usage;
  if (((usage != '\0') && ((node->type & 0xe0) != 0x20)) &&
     ((((child_node->type & 0xe0) != 0x20 &&
       ((iVar2 < iVar3 && (parent_op = parent->op, parent_op != IL_SR)))) &&
      ((parent_op != IL_A_SR && (((char)parent_op < '`' || ('g' < (char)parent_op)))))))) {
    bVar5 = (desc->dest).type & 0x1f;
    if ((bVar5 == 0) || (bVar5 != 1)) {
      if (desc->target_regs != 0) {
        reg = mask_to_register((int)(short)desc->target_regs);
        fill_ea(&child_node->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
      }
    }
    else {
      copy_ea_into(&child_node->desc->dest,&desc->dest);
    }
    child_node->desc->busy_regs = node->desc->busy_regs;
    child_node->desc->fbusy_regs = node->desc->fbusy_regs;
    child_node->desc->frame_top = node->desc->frame_top;
    flags_p = &child_node->desc->flags7;
    *flags_p = *flags_p | node->desc->flags7 & 0x40;
    child_node->desc->pref_regs = node->desc->pref_regs;
    child_node->desc->fpref_regs = node->desc->fpref_regs;
    dispatch_and_finalize_code_node(child_node);
    desc = child_node->desc;
    bVar5 = 0;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      bVar5 = operand->type & 0x1f;
    }
    if (((bVar5 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    switch(operand->type & 0x1f) {
    case 1:
      if (desc->opnd_class == '\x02') {
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
      bVar5 = 0;
      desc = child_node->desc;
      operand = desc->mem_ea;
      if (operand != (ea *)0x0) {
        bVar5 = operand->type & 0x1f;
      }
      if (((bVar5 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
         (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        operand = &desc->value;
      }
      copy_ea_into(&node->desc->value,operand);
      node->desc->opnd_class = child_node->desc->opnd_class;
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p | 0x80;
      goto LAB_00403d49;
    case 2:
    case 8:
    case 0xd:
      if ((operand->type & 0xc0) == 0) {
        copy_ea_into(&node->desc->value,operand);
        if (g_request->unknown_028[2] == '\0') {
          desc = node->desc;
          iVar2 = node_value_size(child_node);
          iVar3 = node_value_size(node);
          disp_p = &(desc->value).disp;
          *disp_p = *disp_p + (iVar2 - iVar3);
        }
        iVar2 = 0;
        bVar5 = operand->type & 0x1f;
        if (((bVar5 == 2) && (operand->base == 'l')) || ((bVar5 == 8 && (operand->base == 'l')))) {
          iVar2 = frame_operand_sp_displacement(operand);
        }
        else if ((bVar5 == 2) || (bVar5 == 8)) {
          iVar2 = operand->disp;
        }
        if (((operand->type & 0x1f) != 0xd) &&
           (((node->desc->pref_regs & 1) == 0 ||
            (iVar3 = operand_access_needs_r0(&node->desc->value,node->type), iVar3 == 0)))) {
          bVar5 = child_node->type;
          bVar7 = bVar5 & 0xe0;
          if ((((((bVar7 != 0x60) && (bVar7 != 0x80)) || ((child_node->type & 0x18) != 0x10)) &&
               (((((bVar5 & 0xf8) != 0x10 && ((bVar5 & 0xf8) != 0x18)) && (bVar7 != 0x20)) &&
                (bVar7 != 0x40)))) || ((-1 < iVar2 && (iVar2 < 0x3d)))) &&
             ((((bVar7 == 0x60 || (bVar7 == 0x80)) && ((child_node->type & 0x18) == 0x10)) ||
              ((((bVar5 & 0xf8) == 0x10 || ((bVar5 & 0xf8) == 0x18)) ||
               ((bVar7 == 0x20 ||
                ((bVar7 == 0x40 ||
                 (iVar2 = operand_access_needs_r0(operand,child_node->type), iVar2 != 0)))))))))) {
            peVar6 = &node->desc->value;
            peVar6->type = peVar6->type & 0xf0;
            break;
          }
        }
        node->desc->busy_regs = child_node->desc->busy_regs;
        node->desc->fbusy_regs = child_node->desc->fbusy_regs;
        node->desc->frame_top = child_node->desc->frame_top;
        node->desc->opnd_class = child_node->desc->opnd_class;
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
        goto LAB_00403d49;
      }
    }
    if (((operand->type & 0x1f) == 7) && (operand->labels == (label_ref *)0x0)) {
      fold_constant_node(node);
    }
    else {
      select_node_template(node,(tmpl_select *)&g_cast_select,'\x02','\0',&node->desc->tmpl);
      child_node = node;
      operand_regs = result_reg_exclusion_mask(node);
      apply_template_to_node
                (node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,operand_regs,child_node);
      flags_p = &node->desc->flags7;
      *flags_p = *flags_p | 2;
    }
LAB_00403d49:
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 8;
    return;
  }
  if ((usage == '\0') ||
     (((child_node->op == IL_B_QUALIFY && ((node->type & 0xe0) != 0x20)) && (iVar3 <= iVar2))))
  goto LAB_00403e9c;
  if (iVar3 == iVar2) {
    if ((node->type & 0xe0) == 0x20) {
      if ((child_node->type & 0xe0) != 0x20) goto LAB_00403dab;
    }
    else if ((child_node->type & 0xe0) == 0x20) goto LAB_00403dab;
  }
  else {
LAB_00403dab:
    if (!bVar1) {
      generate_operator_by_template(node,(tmpl_select *)&g_cast_select,'\x02');
      if ((node->type & 0xe0) == 0x20) {
        return;
      }
      bVar5 = child_node->type;
      bVar7 = bVar5 & 0xe0;
      if (bVar7 == 0x20) {
        return;
      }
      if (node->desc->usage != '\x01') {
        return;
      }
      if (iVar2 <= iVar3) {
        return;
      }
      if ((((bVar5 & 4) == 0) && (bVar7 != 0x80)) && (bVar7 != 0x40)) {
        return;
      }
      if (((bVar5 & 0xf8) != 0) && ((bVar5 & 0xf8) != 8)) {
        return;
      }
      desc = child_node->desc;
      bVar5 = 0;
      operand = desc->mem_ea;
      if (operand != (ea *)0x0) {
        bVar5 = operand->type & 0x1f;
      }
      peVar6 = operand;
      if (((bVar5 == 0) && (peVar6 = &desc->dest, ((desc->dest).type & 0x1f) == 0)) &&
         (peVar6 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        peVar6 = &desc->value;
      }
      if ((peVar6->type & 0x1f) == 1) {
        return;
      }
      bVar5 = 0;
      if (operand != (ea *)0x0) {
        bVar5 = operand->type & 0x1f;
      }
      if (((bVar5 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
         (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        operand = &desc->value;
      }
      if ((operand->type & 0x1f) == 7) {
        return;
      }
      flags_p = &node->desc->flags7;
      *flags_p = *flags_p | 2;
      return;
    }
  }
LAB_00403e9c:
  bVar1 = false;
  if ((iVar3 == iVar2) && ((desc->flags2 & 8) != 0)) {
    flags_p = &child_node->desc->flags2;
    *flags_p = *flags_p | 8;
    node->desc->opnd_class = '\x03';
  }
  else if ((desc->flags3 & 0x20) == 0) {
    operand = &desc->dest;
    bVar5 = operand->type & 0x1f;
    if (bVar5 == 0) {
LAB_00403fef:
      if (desc->target_regs != 0) {
        reg = mask_to_register((int)(short)desc->target_regs);
        fill_ea(&child_node->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
        fill_ea(&node->desc->value,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
        bVar1 = true;
        node->desc->opnd_class = '\x01';
        goto LAB_00404198;
      }
      if (desc->ftarget_regs != 0) {
        reg = float_mask_to_register(desc->ftarget_regs);
        fill_ea(&child_node->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
        fill_ea(&node->desc->value,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
        bVar1 = true;
        node->desc->opnd_class = '\x01';
        goto LAB_00404198;
      }
      if ((bVar5 == 0) ||
         ((iVar3 != iVar2 &&
          ((((bVar5 != 2 && (bVar5 != 8)) ||
            (((bVar5 = (desc->dest).base, '\x0e' < (char)bVar5 ||
              (((int)(short)~g_var_gpr_mask & 1 << (bVar5 & 0x1f)) == 0)) &&
             (((('\x1f' < (char)bVar5 || ((char)bVar5 < '\x10')) ||
               (((int)(short)~g_var_fpr_mask & 1 << (bVar5 - 0x10 & 0x1f)) == 0)) &&
              ((('.' < (char)bVar5 || ((char)bVar5 < ' ')) ||
               (((int)(short)g_var_fpr_mask &
                (1 << (bVar5 - 0x1f & 0x1f) | 1 << (bVar5 - 0x20 & 0x1f))) != 0)))))))) &&
           (iVar3 != iVar2)))))) {
        if (usage != '\0') goto LAB_00404198;
      }
      else {
        operand->type = operand->type & 0xf0;
        if ((g_request->cpu == 4) || ((node->type & 0xf8) != 0x30)) goto LAB_00404198;
        flags_p = &child_node->desc->flags2;
        *flags_p = *flags_p | 8;
        flags_p = &node->desc->flags2;
        *flags_p = *flags_p | 8;
        node->desc->opnd_class = '\x03';
      }
    }
    else {
      if (iVar3 == iVar2) {
LAB_00403f26:
        if (((bVar5 == 2) || (bVar5 == 8)) &&
           ((((desc->dest).base < '\x0f' &&
             ((1 << ((desc->dest).base & 0x1fU) & (int)(short)~g_var_gpr_mask) != 0)) ||
            (((((desc->dest).base < ' ' && ('\x0f' < (desc->dest).base)) &&
              ((1 << ((desc->dest).base - 0x10U & 0x1f) & (int)(short)~g_var_fpr_mask) != 0)) ||
             ((((desc->dest).base < '/' && ('\x1f' < (desc->dest).base)) &&
              (((int)(short)g_var_fpr_mask &
               (1 << ((desc->dest).base - 0x1fU & 0x1f) | 1 << ((desc->dest).base - 0x20U & 0x1f)))
               == 0)))))))) goto LAB_00403fef;
      }
      else if (bVar5 != 1) {
        if (iVar3 != iVar2) goto LAB_00403fef;
        goto LAB_00403f26;
      }
      copy_ea_into(&child_node->desc->dest,operand);
    }
  }
  else {
    flags_p = &child_node->desc->flags3;
    *flags_p = *flags_p | 0x20;
    copy_ea_into(&child_node->desc->dest,&node->desc->dest);
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p & 0xdf;
    operand = &node->desc->dest;
    operand->type = operand->type & 0xf0;
  }
  bVar1 = true;
LAB_00404198:
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
  if (!bVar1) {
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
    bVar5 = 0;
    desc = child_node->desc;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      bVar5 = operand->type & 0x1f;
    }
    if (((bVar5 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    copy_ea_into(&node->desc->value,operand);
    node->desc->opnd_class = child_node->desc->opnd_class;
  }
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 0x80;
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 8;
  return;
}



