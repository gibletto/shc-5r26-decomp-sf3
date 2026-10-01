#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))
#undef g_switch_cases
#define g_switch_cases (*(void * *)(g_sd + 0x1fee0))


// entry: 00420220
// name : generate_switch_statement
// size : 978
// sig  : void generate_switch_statement(gen_node * sw)


int __cdecl generate_switch_statement(gen_node *sw)

{
  int iVar1;
  short filno;
  uint serial;
  ushort uVar2;
  gen_node *selector;
  gen_node *pgVar3;
  request_entry *swi_entry;
  uint case_range;
  short default_label;
  short saved_break_label;
  short saved_case_label;
  bool use_compare_chain;
  
  saved_case_label = g_last_case_label;
  saved_break_label = g_break_label;
  use_compare_chain = true;
  g_break_label = 0;
  g_last_case_label = 0;
  selector = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (selector == (gen_node *)0x0) {
    report_codegen_message(0xce6,sw->filn,(uint)sw->line,(int)sw->listno,(char *)0x0);
  }
  generate_statement_expression(selector,0,0);
  serial = g_stmt_serial;
  filno = selector->filn;
  uVar2 = selector->line;
  selector = sw->child;
  pgVar3 = selector->child;
  while (pgVar3 != (gen_node *)0x0) {
    unlink_and_free_subtree(pgVar3);
    pgVar3 = selector->child;
  }
  selector->child = (gen_node *)0x0;
  selector->op = IL_CONST;
  read_switch_case_table(sw);
  default_label = g_switch_default_label;
  case_range = g_switch_max_case - g_switch_min_case;
  if ((case_range == 0) || (case_range != 0xffffffff)) {
    case_range = case_range + 1;
  }
  if (g_request->switch_density_rule == 0) {
    if ((g_switch_case_count < 8) ||
       (iVar1 = g_switch_case_count * 0xb + -0x51,
       (uint)((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) < case_range)) goto LAB_0042034f;
  }
  else if ((g_switch_case_count < 10) || ((uint)(g_switch_case_count * 3) <= case_range))
  goto LAB_0042034f;
  use_compare_chain = false;
LAB_0042034f:
  if (g_break_label == 0) {
    g_break_label = make_new_label_number();
  }
  if (g_switch_default_label == 0) {
    g_switch_default_label = g_break_label;
  }
  if (use_compare_chain) {
    uVar2 = emit_switch_compare_chain(serial,filno,uVar2);
  }
  else {
    uVar2 = emit_switch_jump_table(serial,sw);
  }
  if (uVar2 != 0) {
    remove_serial_from_register_ranges(uVar2,serial);
    g_used_gpr_mask = g_used_gpr_mask | uVar2;
    invalidate_register_contents((int)(short)uVar2);
  }
  save_register_contents();
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    push_fpscr_pr_state();
  }
  if (g_switch_cases != (void *)0x0) {
    stock_free(g_switch_cases);
  }
  fill_psd_record((psd *)&g_psd_scratch,OP_SWBGN,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                  (ea *)0x0,(ea *)0x0,0,'\0');
  emit_psd_record((psd *)&g_psd_scratch,0);
  invalidate_register_contents(0xf000f);
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    g_fpscr_pr = '\x02';
  }
  pgVar3 = read_ilb_node(g_ilb_file);
  if (pgVar3 == (gen_node *)0x0) {
    report_codegen_message(0xce6,sw->filn,(uint)sw->line,(int)sw->listno,(char *)0x0);
  }
  g_case_restores_contents = '\x01';
  generate_statement(pgVar3);
  if (sw->child == (gen_node *)0x0) {
    pgVar3 = (gen_node *)0x0;
  }
  else {
    pgVar3 = sw->child->next;
  }
  unlink_and_free_subtree(pgVar3);
  fill_psd_record((psd *)&g_psd_scratch,OP_SWEND,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                  (ea *)0x0,(ea *)0x0,0,'\0');
  emit_psd_record((psd *)&g_psd_scratch,0);
  drop_saved_register_contents();
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    pop_fpscr_pr_state();
  }
  if (g_break_label != 0) {
    fill_label_record((psd *)&g_psd_scratch,OP_LABEL,g_break_label,(short)g_sptravel);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  swi_entry = find_keyed_entry(g_request,(int)sw->symx);
  if (swi_entry == (request_entry *)0x0) {
    report_codegen_message(0x1218,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  if (default_label != 0) {
    g_break_label = g_last_case_label;
  }
  *(int *)swi_entry->c = (int)g_break_label;
  g_break_label = saved_break_label;
  g_last_case_label = saved_case_label;
  unlink_and_free_subtree(selector);
  sw->child = (gen_node *)0x0;
  return;
}



