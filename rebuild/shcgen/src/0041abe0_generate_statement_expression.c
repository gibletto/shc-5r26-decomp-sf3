#include "decls.h"
#include "imports.h"
#include "r0varrules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041abe0
// name : generate_statement_expression
// size : 498
// sig  : void generate_statement_expression(gen_node * stmt, short true_label, short false_label)


int __cdecl generate_statement_expression(gen_node *stmt,short true_label,short false_label)

{
  byte has_fpu;
  short reg;
  int ofs;
  ushort saved_fpr_mask;
  ushort saved_gpr_mask;
  
  saved_gpr_mask = g_used_gpr_mask;
  saved_fpr_mask = g_used_fpr_mask;
  g_msg_filn = stmt->filn;
  g_msg_line = stmt->line;
  g_msg_listno = stmt->listno;
  g_used_gpr_mask = g_used_gpr_mask & 0xfff0;
  g_stmt_serial = g_stmt_serial + 1;
  g_sptravel = 0;
  g_used_fpr_mask = g_used_fpr_mask & 0xfff0;
  reset_r0_variable_candidates();
  initialize_node_descriptor_and_operand_slots(stmt);
  if (R0VAR_DROP(g_r0_variable != 0 ? *(byte *)(g_r0_variable + 4) : -1, g_r0_variable != 0 ? *(short *)g_r0_variable : 0)) {
    g_r0_variable = 0;
  }
  if (g_r0_variable != 0) {
    if ((int)(g_deref_total - (uint)*(byte *)(g_r0_variable + 4)) <
        (int)((uint)*(byte *)(g_r0_variable + 4) * 2 + -1)) {
      reg = find_lreg_register(*(short *)(g_r0_variable + 2));
      if (-1 < reg) goto LAB_0041ac86;
    }
    g_r0_variable = 0;
  }
LAB_0041ac86:
  if (stmt->desc->usage == '\x01') {
    stmt->desc->true_label = true_label;
    stmt->desc->false_label = false_label;
  }
  stmt->desc->busy_regs = g_var_gpr_mask;
  stmt->desc->fbusy_regs = g_var_fpr_mask;
  stmt->desc->frame_top = g_frame_end;
  ofs = 0;
  g_stmt_pushed_operand = '\0';
  do {
    g_gpr_contents[0].unknown_0a[ofs + -1] = g_gpr_contents[0].unknown_0a[ofs + -1] & 0x7f;
    g_fpr_contents[0].unknown_0a[ofs + -1] = g_fpr_contents[0].unknown_0a[ofs + -1] & 0x7f;
    ofs = ofs + 0x18;
  } while (ofs < 0x60);
  g_stmt_invalidate_mask = 0;
  g_content_hit = 0;
  dispatch_and_finalize_code_node(stmt);
  g_stmt_temp_regs = g_stmt_temp_regs | stmt->desc->temp_regs;
  if ((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) {
    if (g_r0_variable != 0) {
      record_r0_variable_use_serial();
    }
    update_register_ranges_after_statement(g_used_gpr_mask,g_gpr_contents);
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      has_fpu = 1;
    }
    else {
      has_fpu = -(g_request->cpu == 4) & 2;
    }
    if (has_fpu != 0) {
      update_register_ranges_after_statement(g_used_fpr_mask,g_fpr_contents);
    }
  }
  if (g_r0_variable != 0) {
    invalidate_register_contents(1);
  }
  emit_node_code(stmt);
  invalidate_register_contents((int)g_stmt_invalidate_mask);
  free_node_descriptor_tree(stmt);
  g_used_gpr_mask = g_used_gpr_mask | saved_gpr_mask;
  g_used_fpr_mask = g_used_fpr_mask | saved_fpr_mask;
  return;
}



