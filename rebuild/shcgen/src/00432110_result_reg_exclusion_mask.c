#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00432110
// name : result_reg_exclusion_mask
// size : 381
// sig  : uint result_reg_exclusion_mask(gen_node * node)


uint __cdecl result_reg_exclusion_mask(gen_node *node)

{
  byte kind;
  uint symno;
  gen_node *right;
  ea *operand;
  uint right_abs;
  uint left_abs;
  uint left_temps;
  uint right_temps;
  node_desc *desc;
  gen_node *left;
  
  right_abs = 0;
  left_temps = 0;
  left_abs = 0;
  right_temps = 0;
  left = node->child;
  if (left == (gen_node *)0x0) goto LAB_00432260;
  desc = left->desc;
  kind = 0;
  operand = desc->mem_ea;
  if (operand != (ea *)0x0) {
    kind = operand->type & 0x1f;
  }
  if (((kind == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
     (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    operand = &desc->value;
  }
  left_temps = CONCAT22(desc->ftemp_regs,desc->temp_regs);
  if ((operand == (ea *)0x0) ||
     ((kind = operand->type & 0x1f, kind != 0xd &&
      ((kind != 7 || (operand->labels == (label_ref *)0x0)))))) {
LAB_004321c3:
    left_abs = 0;
  }
  else {
    if (operand->labels == (label_ref *)0x0) {
      symno = 0;
    }
    else {
      symno = (uint)operand->labels->labno1;
    }
    left_abs = 1;
    if ((g_symbol_table[(symno ^ (int)symno >> 0x1f) - ((int)symno >> 0x1f)].attr & 3) == 0)
    goto LAB_004321c3;
  }
  right = (gen_node *)0x0;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  if (right != (gen_node *)0x0) {
    desc = right->desc;
    kind = 0;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      kind = operand->type & 0x1f;
    }
    if (((kind == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    right_temps = CONCAT22(desc->ftemp_regs,desc->temp_regs);
    if ((operand != (ea *)0x0) &&
       ((kind = operand->type & 0x1f, kind == 0xd ||
        ((kind == 7 && (operand->labels != (label_ref *)0x0)))))) {
      if (operand->labels == (label_ref *)0x0) {
        symno = 0;
      }
      else {
        symno = (uint)operand->labels->labno1;
      }
      right_abs = 1;
      if ((g_symbol_table[(symno ^ (int)symno >> 0x1f) - ((int)symno >> 0x1f)].attr & 3) != 0)
      goto LAB_00432260;
    }
    right_abs = 0;
  }
LAB_00432260:
  return CONCAT22(node->desc->fbusy_regs,node->desc->busy_regs) &
         ~(right_abs | right_temps | left_abs | left_temps) |
         CONCAT22(g_var_fpr_mask,g_var_gpr_mask);
}



