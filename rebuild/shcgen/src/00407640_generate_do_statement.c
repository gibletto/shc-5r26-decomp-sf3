#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 00407640
// name : generate_do_statement
// size : 531
// sig  : void generate_do_statement(gen_node * node)


int __cdecl generate_do_statement(gen_node *node)

{
  short labno;
  gen_node *pgVar1;
  gen_node *pgVar2;
  gen_node *cond_next;
  short saved_break_label;
  short saved_continue_label;
  
  labno = make_new_label_number();
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  saved_continue_label = g_continue_label;
  saved_break_label = g_break_label;
  g_break_label = 0;
  g_continue_label = 0;
  invalidate_register_contents(0xf000f);
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    g_fpscr_pr = '\x02';
  }
  pgVar1 = read_ilb_node(g_ilb_file);
  if (pgVar1 == (gen_node *)0x0) {
    report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
  }
  generate_statement(pgVar1);
  pgVar1 = node->child;
  pgVar2 = pgVar1->child;
  while (pgVar2 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar2);
    pgVar2 = pgVar1->child;
  }
  pgVar1->child = (gen_node *)0x0;
  pgVar1->op = IL_CONST;
  pgVar2 = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (pgVar2 == (gen_node *)0x0) {
    report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
  }
  if (g_continue_label != 0) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,g_continue_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
    if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
      g_fpscr_pr = '\x02';
    }
    invalidate_register_contents(0xf000f);
  }
  cond_next = (gen_node *)0x0;
  generate_statement_expression(pgVar2,labno,0);
  if (node->child != (gen_node *)0x0) {
    cond_next = node->child->next;
  }
  if (g_break_label != 0) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,g_break_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  g_break_label = saved_break_label;
  g_continue_label = saved_continue_label;
  unlink_and_free_subtree(cond_next);
  unlink_and_free_subtree(pgVar1);
  node->child = (gen_node *)0x0;
  return;
}



