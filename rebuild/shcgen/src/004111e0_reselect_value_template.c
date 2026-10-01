#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_late_handler_table
#define g_late_handler_table (*(unsigned char * *)(g_sd + 0x9848))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004111e0
// name : reselect_value_template
// size : 487
// sig  : void reselect_value_template(gen_node * node)


int __cdecl reselect_value_template(gen_node *node)

{
  unsigned char _frec_8[8];
#define unary_select (*(tmpl_select * *)(_frec_8 + 0))
#define binary_select (*(tmpl_select * *)(_frec_8 + 4))
  int iVar1;
  tmpl_header *tmpl;
  uint operand_regs;
  gen_node *account_node;
  char handler_kind;
  il_op node_op;
  byte node_type;
  
  node->desc->tmpl = (tmpl_header *)0x0;
  iVar1 = map_code_node_opcode_to_late_handler_index((short)(char)node->op);
  if ((iVar1 != -1) &&
     (((node_type = node->type, (node_type & 0xf8) == 0x30 || ((node_type & 0xe0) == 0x60)) ||
      ((node_type & 0xe0) == 0x80)))) {
    handler_kind = (&g_late_handler_kind)[iVar1];
    if (handler_kind == '\x01') {
      select_node_template
                (node,(tmpl_select *)(&g_late_handler_table)[iVar1],'\x01','\0',&node->desc->tmpl);
      goto LAB_00411399;
    }
    if (handler_kind == '\x02') {
      select_node_template
                (node,(tmpl_select *)(&g_late_handler_table)[iVar1],'\x02','\0',&node->desc->tmpl);
      goto LAB_00411399;
    }
    if (handler_kind == '\x04') {
      iVar1 = select_cpu_variant((&g_late_handler_table)[iVar1],&unary_select,&binary_select);
      if ((short)iVar1 == 0) {
        select_node_template(node,binary_select,'\x02','\0',&node->desc->tmpl);
      }
      else {
        select_node_template(node,unary_select,'\x01','\0',&node->desc->tmpl);
      }
      goto LAB_00411399;
    }
    node_op = node->op;
    if (node_op == IL_ASSIGN) {
      if (((node_type & 0xe0) == 0x60) || ((node_type & 0xe0) == 0x80)) {
        tmpl = select_aggregate_assign_template(node,1);
        node->desc->tmpl = tmpl;
      }
      else if (g_request->unknown_028[2] == '\0') {
        select_node_template
                  (node,(tmpl_select *)&g_assign_double_select,'\x01','\0',&node->desc->tmpl);
      }
      else {
        select_node_template
                  (node,(tmpl_select *)&g_assign_double_select_alt,'\x01','\0',&node->desc->tmpl);
      }
      goto LAB_00411399;
    }
    if (node_op == IL_CAST) {
      select_node_template(node,(tmpl_select *)&g_cast_select,'\x02','\0',&node->desc->tmpl);
      goto LAB_00411399;
    }
    if (node_op == IL_CALL) {
      choose_call_registers(node,-1,0);
      goto LAB_00411399;
    }
  }
  report_codegen_message(0x1222,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
LAB_00411399:
  tmpl = node->desc->tmpl;
  if (tmpl != (tmpl_header *)0x0) {
    account_node = node;
    operand_regs = result_reg_exclusion_mask(node);
    apply_template_to_node(node,tmpl,'\x10',(ea *)0x0,(ea *)0x0,operand_regs,account_node);
  }
  return;
#undef unary_select
#undef binary_select
}



