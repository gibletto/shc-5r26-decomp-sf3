#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040d9e0
// name : generate_assign_node
// size : 1645
// sig  : void generate_assign_node(gen_node * node)


int __cdecl generate_assign_node(gen_node *node)

{
  byte bVar1;
  short sVar2;
  tmpl_header *tmpl;
  int needs_r0;
  ushort *mask_ptr;
  ea *operand;
  byte type_class;
  uint uVar3;
  uint uVar4;
  gen_node *right;
  gen_node *account_node;
  node_desc *desc;
  uchar *flags_ptr;
  gen_node *left;
  bool left_reg_handed_over;
  node_desc *right_desc;
  ushort saved_var_gpr_mask;
  char value_reg;
  
  left = node->child;
  right = (gen_node *)0x0;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  if (left->op == IL_B_QUALIFY) {
    tmpl = select_bit_field_assign_template(node,'\x01');
LAB_0040da60:
    node->desc->tmpl = tmpl;
  }
  else {
    bVar1 = left->type & 0xe0;
    if ((bVar1 == 0x60) || (bVar1 == 0x80)) {
      tmpl = select_aggregate_assign_template(node,0);
      goto LAB_0040da60;
    }
    if (g_request->unknown_028[2] == '\0') {
      select_node_template
                (node,(tmpl_select *)&g_assign_double_select,'\x01','\x01',&node->desc->tmpl);
    }
    else {
      select_node_template
                (node,(tmpl_select *)&g_assign_double_select_alt,'\x01','\x01',&node->desc->tmpl);
    }
  }
  apply_template_operand_constraints(node);
  left->desc->busy_regs = node->desc->busy_regs;
  left->desc->fbusy_regs = node->desc->fbusy_regs;
  left->desc->frame_top = node->desc->frame_top;
  flags_ptr = &left->desc->flags7;
  *flags_ptr = *flags_ptr | node->desc->flags7 & 0x40;
  desc = left->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    left->desc->fpref_regs = node->desc->fpref_regs;
  }
  tmpl = node->desc->tmpl;
  if (tmpl != (tmpl_header *)0x0) {
    mask_ptr = &left->desc->busy_regs;
    *mask_ptr = *mask_ptr & ~(ushort)tmpl->clobbers;
  }
  dispatch_and_finalize_code_node(left);
  if (left->op != IL_B_QUALIFY) {
    bVar1 = (left->desc->value).type & 0x1f;
    if ((bVar1 != 9) &&
       (((((g_request->cpu != 4 && ((node->type & 0xf8) == 0x30)) ||
          (type_class = node->type & 0xe0, type_class == 0x60)) ||
         ((type_class == 0x80 || ((left->type & 0xe0) == 0x60)))) || (bVar1 == 1)))) {
      copy_ea_into(&right->desc->dest,&left->desc->value);
    }
  }
  right->desc->busy_regs = left->desc->busy_regs;
  right->desc->fbusy_regs = left->desc->fbusy_regs;
  right->desc->frame_top = left->desc->frame_top;
  flags_ptr = &right->desc->flags7;
  *flags_ptr = *flags_ptr | left->desc->flags7 & 0x40;
  needs_r0 = operand_access_needs_r0(&left->desc->value,node->type);
  if (needs_r0 != 0) {
    right->desc->pref_regs = 1;
    mask_ptr = &node->desc->pref_regs;
    if (*mask_ptr == 0) {
      *mask_ptr = 1;
    }
  }
  desc = right->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    right->desc->fpref_regs = node->desc->fpref_regs;
  }
  saved_var_gpr_mask = g_var_gpr_mask;
  left_reg_handed_over = false;
  if (((left->desc->value).type & 0x1f) == 1) {
    bVar1 = (left->desc->value).base;
    uVar4 = 1 << (bVar1 & 0x1f);
    if (((uVar4 & (int)(short)right->desc->need_regs) == 0) &&
       ((uVar3 = (int)g_current_function >> 0x1f,
        (g_symbol_table[((int)g_current_function ^ uVar3) - uVar3].attr & 0x18) == 0 ||
        ((uVar4 & 0x7f00) == 0)))) {
      right->desc->pref_regs = 1 << (bVar1 & 0x1f);
      mask_ptr = &right->desc->busy_regs;
      *mask_ptr = *mask_ptr ^ 1 << ((left->desc->value).base & 0x1fU);
      left_reg_handed_over = true;
      g_var_gpr_mask = g_var_gpr_mask ^ 1 << ((left->desc->value).base & 0x1fU);
    }
  }
  dispatch_and_finalize_code_node(right);
  g_var_gpr_mask = saved_var_gpr_mask;
  if (left->op == IL_B_QUALIFY) {
    tmpl = select_bit_field_assign_template(node,'\0');
    node->desc->tmpl = tmpl;
  }
  sVar2 = resolve_operand_register_conflicts(node,left,right);
  if (sVar2 != 0) {
    if ((((g_request->cpu != 4) && ((right->type & 0xf8) == 0x30)) || ((right->type & 0xe0) == 0x60)
        ) && (((right->desc->dest).type & 0x1f) != 0)) {
      release_node_registers(right);
    }
    operand = &right->desc->dest;
    operand->type = operand->type & 0xf0;
    if ((((g_request->cpu != 4) && ((right->type & 0xf8) == 0x30)) || ((right->type & 0xe0) == 0x60)
        ) && ((right->desc->tmpl != (tmpl_header *)0x0 || (right->op == IL_CALL)))) {
      right->desc->busy_regs = left->desc->busy_regs;
      right->desc->fbusy_regs = left->desc->fbusy_regs;
      right->desc->frame_top = left->desc->frame_top;
      flags_ptr = &right->desc->flags7;
      *flags_ptr = *flags_ptr | left->desc->flags7 & 0x40;
      right->desc->pref_regs = node->desc->tmpl->pref_right;
      right->desc->fpref_regs = node->desc->tmpl->fpref_right;
      mask_ptr = &right->desc->pref_regs;
      if (*mask_ptr == 0) {
        *mask_ptr = node->desc->pref_regs;
        right->desc->fpref_regs = node->desc->fpref_regs;
      }
      g_chooser_extra_excluded = '\0';
      desc = left->desc;
      bVar1 = (desc->dest).type & 0x1f;
      if ((bVar1 != 0) && (right_desc = right->desc, ((right_desc->value).type & 0x1f) == 0)) {
        if (bVar1 == 1) {
          copy_ea_into(&right_desc->dest,desc->mem_ea);
          g_chooser_extra_excluded = '\x01' << ((left->desc->dest).base & 0x1fU);
        }
        else if (((bVar1 == 2) && ((desc->dest).base == 'l')) ||
                ((bVar1 == 8 && ((desc->dest).base == 'l')))) {
          copy_ea_into(&right_desc->dest,&desc->dest);
          flags_ptr = &right->desc->flags3;
          *flags_ptr = *flags_ptr | 0x20;
        }
      }
      reselect_value_template(right);
      g_chooser_extra_excluded = '\0';
    }
  }
  if (((right->desc->dest).type & 0x1f) != 0) {
LAB_0040dfb3:
    set_assignment_result_value(node);
    node->desc->tmpl = (tmpl_header *)0x0;
    flags_ptr = &node->desc->flags3;
    *flags_ptr = *flags_ptr | 0x80;
    flags_ptr = &node->desc->flags3;
    *flags_ptr = *flags_ptr | 8;
    goto LAB_0040dfd7;
  }
  if (left->op == IL_B_QUALIFY) {
LAB_0040de62:
    tmpl = select_bit_field_assign_template(node,'\0');
LAB_0040df81:
    node->desc->tmpl = tmpl;
  }
  else {
    if (((left->desc->dest).type & 0x1f) == 0) {
      sVar2 = ea_operands_equal(&left->desc->value,&right->desc->value);
      if (sVar2 != 0) goto LAB_0040dfb3;
    }
    if (left->op == IL_B_QUALIFY) goto LAB_0040de62;
    bVar1 = left->type & 0xe0;
    if ((bVar1 == 0x60) || (bVar1 == 0x80)) {
      tmpl = select_aggregate_assign_template(node,1);
      goto LAB_0040df81;
    }
    if ((((node->type & 0xe0) == 0) || (bVar1 = node->type & 0xf8, bVar1 == 0x28)) ||
       (bVar1 == 0x40)) {
      needs_r0 = operand_access_needs_r0(&right->desc->value,right->type);
      if (needs_r0 != 0) {
        desc = left->desc;
        if (((desc->flags2 & 8) == 0) && (((desc->dest).type & 0x1f) == 0)) {
          uVar4 = ea_register_mask(&desc->value);
          if (((uVar4 & 1) != 0) &&
             (bVar1 = node->desc->tmpl->excluded,
             (ushort)((right->desc->temp_regs | right->desc->reused_regs | (ushort)bVar1 | 0x8001) &
                      ~g_var_gpr_mask ^ g_var_gpr_mask) != 0xffff)) {
            load_operand_address_into_new_register(node,left,right,(ushort)(bVar1 | 1));
          }
        }
        node->desc->pref_regs = 1;
      }
    }
    if (g_request->unknown_028[2] == '\0') {
      select_node_template
                (node,(tmpl_select *)&g_assign_double_select,'\x01','\0',&node->desc->tmpl);
    }
    else {
      select_node_template
                (node,(tmpl_select *)&g_assign_double_select_alt,'\x01','\0',&node->desc->tmpl);
    }
  }
  account_node = node;
  uVar4 = result_reg_exclusion_mask(node);
  apply_template_to_node(node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,uVar4,account_node);
LAB_0040dfd7:
  if (left_reg_handed_over) {
    sVar2 = ea_operands_equal(&left->desc->value,&node->desc->value);
    if (sVar2 != 0) {
      node->desc->opnd_class = left->desc->opnd_class;
    }
  }
  if (left->op == IL_ID) {
    forget_register_copies_of_variable(left);
    operand = &right->desc->value;
    if (((operand != (ea *)0x0) && ((operand->type & 0x1f) == 1)) &&
       (((value_reg = (right->desc->value).base, value_reg < '\x04' && (-1 < value_reg)) ||
        ((value_reg < '\x14' && ('\x0f' < value_reg)))))) {
      record_variable_in_register(left,(short)value_reg);
    }
  }
  return;
}



