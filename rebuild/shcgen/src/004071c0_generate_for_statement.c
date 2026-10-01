#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 004071c0
// name : generate_for_statement
// size : 1150
// sig  : void generate_for_statement(gen_node * stmt)


int __cdecl generate_for_statement(gen_node *stmt)

{
  short sVar1;
  short sVar2;
  short labno;
  gen_node *init;
  ea *target;
  gen_node *pgVar3;
  gen_node *node;
  gen_node *body;
  ea *peVar4;
  int iVar5;
  byte tmp;
  byte jump_reg;
  short saved_continue;
  
  init = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (init == (gen_node *)0x0) {
    report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
  }
  if (init->op != IL_NULL) {
    generate_statement_expression(init,0,0);
  }
  init = stmt->child;
  pgVar3 = init->child;
  while (pgVar3 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar3);
    pgVar3 = init->child;
  }
  init->child = (gen_node *)0x0;
  init->op = IL_CONST;
  sVar1 = make_new_label_number();
  sVar2 = choose_general_register(0,0,'\0');
  tmp = (byte)sVar2;
  remove_serial_from_register_ranges(1 << (tmp & 0x1f),g_stmt_serial);
  iVar5 = 0;
  peVar4 = (ea *)0x0;
  target = make_label_operand(sVar1);
  fill_psd_record((psd *)&g_psd_scratch,OP_JUMP,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                  target,peVar4,iVar5,tmp);
  emit_psd_record((psd *)&g_psd_scratch,0);
  labno = make_new_label_number();
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  invalidate_register_contents(0xf000f);
  saved_continue = g_continue_label;
  sVar2 = g_break_label;
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    g_fpscr_pr = '\x02';
  }
  g_break_label = 0;
  g_continue_label = 0;
  pgVar3 = read_ilb_node(g_ilb_file);
  if (pgVar3 == (gen_node *)0x0) {
    report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
  }
  body = (gen_node *)0x0;
  generate_statement(pgVar3);
  if (stmt->child != (gen_node *)0x0) {
    body = stmt->child->next;
  }
  pgVar3 = body->child;
  while (pgVar3 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar3);
    pgVar3 = body->child;
  }
  body->child = (gen_node *)0x0;
  body->op = IL_NULL;
  if (g_continue_label != 0) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,g_continue_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
    invalidate_register_contents(0xf000f);
    if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
      g_fpscr_pr = '\x02';
    }
  }
  pgVar3 = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (pgVar3 == (gen_node *)0x0) {
    report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
  }
  if (pgVar3->op != IL_NULL) {
    generate_statement_expression(pgVar3,0,0);
  }
  node = nth_operand(stmt,3);
  pgVar3 = node->child;
  while (pgVar3 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar3);
    pgVar3 = node->child;
  }
  node->child = (gen_node *)0x0;
  node->op = IL_CONST;
  pgVar3 = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (pgVar3 == (gen_node *)0x0) {
    report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
  }
  invalidate_register_contents(0xf000f);
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    g_fpscr_pr = '\x02';
  }
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,sVar1,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  if (pgVar3->op == IL_NULL) {
    sVar1 = choose_general_register(0,0,'\0');
    jump_reg = (byte)sVar1;
    remove_serial_from_register_ranges(1 << (jump_reg & 0x1f),g_stmt_serial);
    iVar5 = 0;
    peVar4 = (ea *)0x0;
    target = make_label_operand(labno);
    fill_psd_record((psd *)&g_psd_scratch,OP_JUMP,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                    target,peVar4,iVar5,jump_reg);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  else {
    generate_statement_expression(pgVar3,labno,0);
  }
  if (g_break_label != 0) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,g_break_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  g_break_label = sVar2;
  g_continue_label = saved_continue;
  unlink_and_free_subtree(pgVar3);
  unlink_and_free_subtree(node);
  unlink_and_free_subtree(body);
  unlink_and_free_subtree(init);
  stmt->child = (gen_node *)0x0;
  return;
}



