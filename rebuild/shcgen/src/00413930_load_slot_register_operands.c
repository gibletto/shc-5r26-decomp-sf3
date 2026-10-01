#include "decls.h"
#include "imports.h"

// entry: 00413930
// name : load_slot_register_operands
// size : 449
// sig  : void load_slot_register_operands(short kind, gen_node * node, ea * * operands)


int __cdecl load_slot_register_operands(short kind,gen_node *node,ea **operands)

{
  ea *reg_opnd;
  char reg;
  
  operands[2] = (ea *)0x0;
  operands[3] = (ea *)0x0;
  operands[4] = (ea *)0x0;
  operands[5] = (ea *)0x0;
  operands[6] = (ea *)0x0;
  switch(kind) {
  case 1:
    reg = node->desc->regs_41[0];
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[2] = reg_opnd;
    }
    reg = node->desc->regs_41[1];
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[3] = reg_opnd;
    }
    reg = node->desc->regs_41[2];
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[4] = reg_opnd;
    }
    reg = node->desc->regs_44[0];
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[5] = reg_opnd;
    }
    reg = node->desc->regs_44[1];
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[6] = reg_opnd;
      return;
    }
    break;
  case 2:
    reg = node->desc->regs_3d[0];
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[2] = reg_opnd;
    }
    reg = node->desc->regs_3d[1];
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[3] = reg_opnd;
      return;
    }
    break;
  case 3:
    reg = node->desc->reg_47;
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[2] = reg_opnd;
      return;
    }
    break;
  case 4:
    reg = node->desc->addr_reg;
    if (reg != -1) {
      reg_opnd = new_ea_operand_with_flags('\x01',reg,-1,0,'\0',(label_ref *)0x0);
      operands[2] = reg_opnd;
    }
    break;
  default:
    report_codegen_message(0x1200,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return;
  }
  return;
}



