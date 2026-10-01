#include "decls.h"
#include "imports.h"

// entry: 0041f220
// name : reload_operand_address_into_register
// size : 545
// sig  : void reload_operand_address_into_register(gen_node * node, gen_node * left, gen_node * right, ushort excluded)


int __cdecl reload_operand_address_into_register(gen_node *node,gen_node *left,gen_node *right,ushort excluded)

{
  byte ea_kind;
  short new_reg;
  ea *op;
  uint excl32;
  uint mask32;
  ea *peVar1;
  ushort uVar2;
  ushort right_regs;
  ushort saved_value_regs;
  node_desc *desc;
  ushort *mask_ptr;
  
  ea_kind = 0;
  desc = left->desc;
  peVar1 = desc->saved_ea;
  if (peVar1 != (ea *)0x0) {
    ea_kind = peVar1->type & 0x1f;
  }
  if (ea_kind == 0) {
    saved_value_regs = 0;
  }
  else {
    op = desc->saved_reg_ea;
    ea_kind = 0;
    if (op != (ea *)0x0) {
      ea_kind = op->type & 0x1f;
    }
    if ((ea_kind == 0) && (op = &g_ea_pop, (desc->flags3 & 0x10) == 0)) {
      op = peVar1;
    }
    excl32 = ea_register_mask(op);
    saved_value_regs = (ushort)excl32;
  }
  excl32 = result_reg_exclusion_mask(node);
  if (left->op == IL_B_QUALIFY) {
    uVar2 = left->child->desc->pref_regs;
  }
  else {
    uVar2 = left->desc->pref_regs;
  }
  if (node->op == IL_ASSIGN) {
    if (right == (gen_node *)0x0) {
LAB_0041f302:
      right_regs = 0;
      goto LAB_0041f305;
    }
    peVar1 = &right->desc->value;
  }
  else {
    if (right == (gen_node *)0x0) goto LAB_0041f302;
    desc = right->desc;
    ea_kind = 0;
    peVar1 = desc->mem_ea;
    if (peVar1 != (ea *)0x0) {
      ea_kind = peVar1->type & 0x1f;
    }
    if (((ea_kind == 0) && (peVar1 = &desc->dest, (peVar1->type & 0x1f) == 0)) &&
       (peVar1 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      peVar1 = &desc->value;
    }
  }
  mask32 = ea_register_mask(peVar1);
  right_regs = (ushort)mask32;
LAB_0041f305:
  new_reg = choose_general_register
                      (excluded | (ushort)excl32 | saved_value_regs | right_regs,uVar2,'\0');
  if ((new_reg == -1) &&
     (new_reg = choose_general_register(excluded | saved_value_regs | right_regs,uVar2,'\0'),
     new_reg == -1)) {
    report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  uVar2 = 1 << ((byte)new_reg & 0x1f);
  mask_ptr = &left->desc->busy_regs;
  *mask_ptr = *mask_ptr | uVar2;
  g_used_gpr_mask = g_used_gpr_mask | left->desc->busy_regs;
  mask_ptr = &left->desc->temp_regs;
  *mask_ptr = *mask_ptr | uVar2;
  peVar1 = alloc_zeroed(0xc);
  left->desc->addr_reg_ea = peVar1;
  fill_ea(left->desc->addr_reg_ea,'\x01',(byte)new_reg,-1,'\0',0,(label_ref *)0x0);
  desc = left->desc;
  peVar1 = &g_ea_pop;
  if ((desc->flags2 & 8) == 0) {
    peVar1 = &desc->dest;
  }
  emit_operand_transfer
            (peVar1,desc->addr_reg_ea,'P',left,0xc00,'@',
             (int)(short)((ushort)excl32 | saved_value_regs | right_regs),
             (int)(short)(saved_value_regs | right_regs),(int)left);
  desc = left->desc;
  peVar1 = copy_ea(desc->addr_reg_ea);
  desc->mem_ea = peVar1;
  peVar1 = left->desc->mem_ea;
  peVar1->type = peVar1->type & 0xf8 | 8;
  return;
}



