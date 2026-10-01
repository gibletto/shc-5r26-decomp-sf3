#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041e280
// name : resolve_operand_register_conflicts
// size : 1179
// sig  : short resolve_operand_register_conflicts(gen_node * node, gen_node * left, gen_node * right)


short __cdecl resolve_operand_register_conflicts(gen_node *node,gen_node *left,gen_node *right)

{
  ea *op;
  byte bVar1;
  short sVar2;
  ushort taken;
  uint ea_mask;
  int n_free;
  ushort uVar3;
  ushort right_excluded;
  bool saved_conflict;
  ushort right_ftemp;
  ushort addr_reloaded;
  ushort right_fregs;
  ushort tmpl_spill;
  ushort left_fregs;
  ushort right_temp;
  ushort left_regs;
  ushort tmpl_left_fexcl;
  ushort tmpl_right_fexcl;
  ushort moved;
  ushort left_saved_regs;
  ushort right_regs;
  ushort tmpl_excluded;
  bool addr_moved;
  tmpl_header *tmpl;
  
  uVar3 = 0;
  addr_moved = false;
  addr_reloaded = 0;
  if ((left == (gen_node *)0x0) || ((left->desc->flags2 & 8) != 0)) {
    left_regs = 0;
  }
  else {
    ea_mask = ea_register_mask(&left->desc->value);
    left_regs = (ushort)ea_mask;
  }
  if ((right == (gen_node *)0x0) || ((right->desc->flags2 & 8) != 0)) {
    right_regs = 0;
  }
  else {
    ea_mask = ea_register_mask(&right->desc->value);
    right_regs = (ushort)ea_mask;
  }
  if (left == (gen_node *)0x0) {
LAB_0041e31b:
    left_saved_regs = 0;
  }
  else {
    op = left->desc->saved_ea;
    bVar1 = 0;
    if (op != (ea *)0x0) {
      bVar1 = op->type & 0x1f;
    }
    if (bVar1 == 0) goto LAB_0041e31b;
    ea_mask = ea_register_mask(op);
    left_saved_regs = (ushort)ea_mask;
  }
  tmpl = node->desc->tmpl;
  if (tmpl == (tmpl_header *)0x0) {
    tmpl_excluded = 0;
    tmpl_spill = 0;
  }
  else {
    tmpl_excluded = (ushort)tmpl->excluded;
    tmpl_spill = (ushort)tmpl->spill_mask;
  }
  if (right == (gen_node *)0x0) {
    right_temp = 0;
  }
  else {
    right_temp = right->desc->temp_regs;
  }
  if ((left == (gen_node *)0x0) || ((left->desc->flags2 & 8) != 0)) {
    left_fregs = 0;
  }
  else {
    ea_mask = ea_register_mask(&left->desc->value);
    left_fregs = (ushort)(ea_mask >> 0x10);
  }
  if ((right == (gen_node *)0x0) || ((right->desc->flags2 & 8) != 0)) {
    right_fregs = 0;
  }
  else {
    ea_mask = ea_register_mask(&right->desc->value);
    right_fregs = (ushort)(ea_mask >> 0x10);
  }
  tmpl = node->desc->tmpl;
  if (tmpl == (tmpl_header *)0x0) {
    tmpl_left_fexcl = 0;
    tmpl_right_fexcl = 0;
  }
  else {
    tmpl_left_fexcl = (ushort)tmpl->unknown_40[0];
    tmpl_right_fexcl = (ushort)tmpl->unknown_40[1];
  }
  if (right == (gen_node *)0x0) {
    right_ftemp = 0;
  }
  else {
    right_ftemp = right->desc->ftemp_regs;
  }
  if (left != (gen_node *)0x0) {
    left->desc->busy_regs = node->desc->busy_regs | left_saved_regs | left_regs;
    left->desc->fbusy_regs = node->desc->fbusy_regs | left_fregs;
    if (right != (gen_node *)0x0) {
      right->desc->busy_regs = node->desc->busy_regs | right_regs;
      right->desc->fbusy_regs = node->desc->fbusy_regs | right_fregs;
    }
  }
  saved_conflict = (left_saved_regs & right_temp) != 0;
  if (saved_conflict) {
    left_saved_regs = move_saved_value_to_new_register(node,left,right,right_temp);
  }
  moved = (ushort)saved_conflict;
  if (((tmpl_left_fexcl & left_fregs) == 0) && ((left_fregs & ~g_var_fpr_mask & right_ftemp) == 0))
  {
    if (((left_regs & tmpl_excluded) != 0) ||
       (((~g_var_gpr_mask & right_temp & left_regs & 0x7fff) != 0 &&
        (((tmpl_spill & right_regs) != 0 ||
         (sVar2 = try_evaluate_right_operand_first(node,left,right), sVar2 == 0)))))) {
      if (left->desc->usage == '\x03') {
        addr_reloaded = load_operand_address_into_new_register(node,left,right,tmpl_excluded);
        addr_moved = true;
      }
      else {
        sVar2 = g_request->cpu;
        if ((sVar2 != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
          bVar1 = -(sVar2 == 4) & 2;
        }
        if (((bVar1 == 0) || ((left->type & 0xf8) != 0x28)) &&
           ((sVar2 != 4 || ((left->type & 0xf8) != 0x30)))) {
          move_operand_to_new_general_register(node,left,right,0,tmpl_excluded);
        }
        else {
          move_operand_to_new_float_register(node,left,right,0,tmpl_left_fexcl);
        }
      }
      goto LAB_0041e5aa;
    }
  }
  else {
    move_operand_to_new_float_register(node,left,right,0,tmpl_left_fexcl);
LAB_0041e5aa:
    moved = 1;
  }
  right_excluded = uVar3;
  if ((addr_moved) && (addr_reloaded == 0)) {
    taken = g_var_gpr_mask | tmpl_excluded | left_saved_regs | right_regs;
    if (taken == 0x7fff) {
      right_excluded = right_regs;
      if ((right_regs & (tmpl_excluded | left_saved_regs)) != 0) {
        report_codegen_message(0x1229,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        right_excluded = uVar3;
      }
    }
    else {
      n_free = count_clear_mask_bits(taken | 0x8000);
      if (n_free == 1) {
        right_excluded = ~(g_var_gpr_mask | tmpl_excluded | left_saved_regs | right_regs) & 0x7fff;
      }
    }
  }
  else {
    addr_moved = false;
  }
  if ((right_fregs & tmpl_right_fexcl) == 0) {
    if ((right_regs & (right_excluded | tmpl_spill)) == 0) goto LAB_0041e6f6;
    sVar2 = g_request->cpu;
    if ((sVar2 != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
      bVar1 = -(sVar2 == 4) & 2;
    }
    if (((bVar1 == 0) || ((right->type & 0xf8) != 0x28)) &&
       ((sVar2 != 4 || ((right->type & 0xf8) != 0x30)))) {
      move_operand_to_new_general_register(node,left,right,1,right_excluded | tmpl_spill);
    }
    else {
      move_operand_to_new_float_register(node,left,right,1,tmpl_right_fexcl);
    }
  }
  else {
    move_operand_to_new_float_register(node,left,right,1,tmpl_right_fexcl);
  }
  moved = 1;
LAB_0041e6f6:
  if (addr_moved) {
    reload_operand_address_into_register(node,left,right,tmpl_excluded);
  }
  return moved;
}



