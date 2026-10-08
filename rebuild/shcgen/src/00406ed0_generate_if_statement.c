#include "decls.h"
#include "imports.h"
#include "remaprules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 00406ed0
// name : generate_if_statement
// size : 749
// sig  : void generate_if_statement(gen_node * stmt)


int __cdecl generate_if_statement(gen_node *stmt)

{
  short false_label;
  short labno;
  short reg;
  gen_node *cond;
  gen_node *pgVar1;
  gen_node *pgVar2;
  ea *ea1;
  ea *ea2;
  int sptravel;
  byte jump_reg;
  
  cond = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (cond == (gen_node *)0x0) {
    report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
  }
  false_label = make_new_label_number();
  generate_statement_expression(cond,0,false_label);
  save_register_contents();
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    push_fpscr_pr_state();
  }
  cond = stmt->child;
  pgVar1 = cond->child;
  while (pgVar1 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar1);
    pgVar1 = cond->child;
  }
  cond->child = (gen_node *)0x0;
  cond->op = IL_CONST;
  pgVar1 = read_ilb_node(g_ilb_file);
  if (pgVar1 == (gen_node *)0x0) {
    report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
  }
  generate_statement(pgVar1);
  pgVar1 = (gen_node *)0x0;
  if (stmt->child != (gen_node *)0x0) {
    pgVar1 = stmt->child->next;
  }
  pgVar2 = pgVar1->child;
  while (pgVar2 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar2);
    pgVar2 = pgVar1->child;
  }
  pgVar1->child = (gen_node *)0x0;
  pgVar1->op = IL_CONST;
  pgVar2 = read_ilb_node(g_ilb_file);
  if (pgVar2 == (gen_node *)0x0) {
    report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
  }
  if (pgVar2->op == IL_EMPTY) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,false_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  else {
    labno = make_new_label_number();
    reg = choose_general_register(0,0,'\0');
    jump_reg = (byte)reg;
    remove_serial_from_register_ranges(JUMP_TEMP_REGS(32,1 << (jump_reg & 0x1f)),g_stmt_serial);
    sptravel = 0;
    ea2 = (ea *)0x0;
    ea1 = make_label_operand(labno);
    fill_psd_record((psd *)&g_psd_scratch,OP_JUMP,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                    ea1,ea2,sptravel,jump_reg);
    emit_psd_record((psd *)&g_psd_scratch,0);
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,false_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
    invalidate_register_contents(0xf000f);
    restore_register_contents();
    if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
      restore_fpscr_pr_state();
    }
    generate_statement(pgVar2);
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
    pgVar2 = nth_operand(stmt,3);
  }
  drop_saved_register_contents();
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    pop_fpscr_pr_state();
  }
  unlink_and_free_subtree(pgVar2);
  unlink_and_free_subtree(pgVar1);
  unlink_and_free_subtree(cond);
  stmt->child = (gen_node *)0x0;
  return;
}



