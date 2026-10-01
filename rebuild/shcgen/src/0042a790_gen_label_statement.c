#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 0042a790
// name : gen_label_statement
// size : 413
// sig  : void gen_label_statement(gen_node * node)


int __cdecl gen_label_statement(gen_node *node)

{
  gen_node *stmt;
  psd_op op;
  short labno;
  il_op node_op;
  
  node_op = node->op;
  if (node_op == IL_GLABEL) {
    op = OP_LABEL;
    if (node->symx < 0) {
      labno = make_new_label_number();
      g_last_goto_label = labno;
    }
    else {
      labno = node->symx + 0xb6;
    }
  }
  else if (node_op == IL_CLABEL) {
    op = OP_CLABEL;
    labno = node->symx + *(short *)g_request->unknown_0b0 + 0xb6;
    g_last_case_label = labno;
  }
  else if (node_op == IL_DLABEL) {
    op = OP_DLABEL;
    labno = node->symx + *(short *)g_request->unknown_0b0 + 0xb6;
    g_last_case_label = labno;
  }
  else {
    op = (psd_op)labno;
  }
  fill_label_record((psd *)&g_psd_scratch,op,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  stmt = read_ilb_node(g_ilb_file);
  if (stmt == (gen_node *)0x0) {
    report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
  }
  if ((node->op != IL_CLABEL) || (node->parent->op != IL_CLABEL)) {
    invalidate_register_contents(0xf000f);
    if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
      g_fpscr_pr = '\x02';
    }
  }
  if ((node->op == IL_CLABEL) || (node->op == IL_DLABEL)) {
    node_op = node->parent->op;
    if (((node_op == IL_SWITCH) ||
        ((node_op == IL_BLOCK && (node->parent->parent->op == IL_SWITCH)))) &&
       (g_case_restores_contents != '\0')) {
      restore_register_contents();
      if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
        restore_fpscr_pr_state();
      }
    }
  }
  g_case_restores_contents = '\0';
  generate_statement(stmt);
  unlink_and_free_subtree(node->child);
  return;
}



