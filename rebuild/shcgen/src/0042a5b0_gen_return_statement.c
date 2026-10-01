#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))
#undef g_used_gpr_mask
#define g_used_gpr_mask (*(unsigned char *)(g_sd + 0x1ff60))


// entry: 0042a5b0
// name : gen_return_statement
// size : 466
// sig  : void gen_return_statement(gen_node * node)


int __cdecl gen_return_statement(gen_node *node)

{
  byte type_class;
  gen_node *stmt;
  ea *peVar1;
  ea *peVar2;
  ea *ea1;
  uint sign_mask;
  psd_op op;
  int iVar3;
  char cVar4;
  byte result_type;
  
  g_return_record_dropped = '\0';
  stmt = read_ilb_tree((gen_node *)0x0,g_ilb_file);
  if (stmt == (gen_node *)0x0) {
    report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
  }
  if (stmt->op != IL_NULL) {
    generate_statement_expression(stmt,0,0);
    stmt = node->child;
  }
  if (g_return_label == 0) {
    g_return_label = make_new_label_number();
    g_return_label_used = '\0';
  }
  if (g_request->unknown_155[1] != '\0') {
    sign_mask = (int)g_current_function >> 0x1f;
    result_type = g_symbol_table[((int)g_current_function ^ sign_mask) - sign_mask].ret_type;
    type_class = result_type & 0xf8;
    if ((type_class == 0) || (type_class == 8)) {
      peVar1 = new_ea_operand_with_flags('\x01','\0',-1,0,'\0',(label_ref *)0x0);
      if (((result_type & 4) != 0) ||
         (((result_type & 0xe0) == 0x80 || (op = OP_EXTS, (result_type & 0xe0) == 0x40)))) {
        op = OP_EXTU;
      }
      cVar4 = -1;
      iVar3 = 0;
      peVar2 = copy_ea(peVar1);
      ea1 = copy_ea(peVar1);
      fill_psd_record((psd *)&g_psd_scratch,op,type_class != 0,'\0',g_stmt_serial,g_msg_filn,
                      g_msg_line,ea1,peVar2,iVar3,cVar4);
      emit_psd_record((psd *)&g_psd_scratch,0);
      free_ea(peVar1);
    }
  }
  cVar4 = '\0';
  iVar3 = 0;
  peVar2 = (ea *)0x0;
  peVar1 = make_label_operand(g_return_label);
  fill_psd_record((psd *)&g_psd_scratch,OP_RETURN,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                  peVar1,peVar2,iVar3,cVar4);
  emit_psd_record((psd *)&g_psd_scratch,0);
  if (g_return_record_dropped == '\0') {
    g_return_label_used = '\x01';
    (*(unsigned char *)((char *)&g_used_gpr_mask + 0)) = (byte)g_used_gpr_mask | 2;
  }
  unlink_and_free_subtree(stmt);
  node->child = (gen_node *)0x0;
  return;
}



