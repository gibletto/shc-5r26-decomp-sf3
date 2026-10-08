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


// entry: 00407860
// name : generate_while_statement
// size : 646
// sig  : void generate_while_statement(gen_node * node)


int __cdecl generate_while_statement(gen_node *node)

{
  short labno;
  short sVar1;
  short top_label;
  gen_node *pgVar2;
  ea *ea1;
  gen_node *pgVar3;
  ea *ea2;
  int sptravel;
  byte jump_reg;
  short saved_continue_label;
  
  pgVar2 = read_ilb_node(g_ilb_file);
  if (pgVar2 == (gen_node *)0x0) {
    report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
  }
  labno = make_new_label_number();
  sVar1 = choose_general_register(0,0,'\0');
  jump_reg = (byte)sVar1;
  remove_serial_from_register_ranges(JUMP_TEMP_REGS(64,1 << (jump_reg & 0x1f)),g_stmt_serial);
  sptravel = 0;
  ea2 = (ea *)0x0;
  ea1 = make_label_operand(labno);
  fill_psd_record((psd *)&g_psd_scratch,OP_JUMP,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,ea1,
                  ea2,sptravel,jump_reg);
  emit_psd_record((psd *)&g_psd_scratch,0);
  saved_continue_label = g_continue_label;
  sVar1 = g_break_label;
  g_break_label = 0;
  g_continue_label = labno;
  top_label = make_new_label_number();
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,top_label,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  invalidate_register_contents(0xf000f);
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    g_fpscr_pr = '\x02';
  }
  generate_statement(pgVar2);
  pgVar2 = node->child;
  pgVar3 = pgVar2->child;
  while (pgVar3 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar3);
    pgVar3 = pgVar2->child;
  }
  pgVar2->child = (gen_node *)0x0;
  pgVar2->op = IL_NULL;
  pgVar3 = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (pgVar3 == (gen_node *)0x0) {
    report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
  }
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  invalidate_register_contents(0xf000f);
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    g_fpscr_pr = '\x02';
  }
  generate_statement_expression(pgVar3,top_label,0);
  if (g_break_label != 0) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,g_break_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  g_break_label = sVar1;
  g_continue_label = saved_continue_label;
  unlink_and_free_subtree(pgVar3);
  unlink_and_free_subtree(pgVar2);
  node->child = (gen_node *)0x0;
  return;
}



