#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00407af0
// name : generate_block_statement
// size : 649
// sig  : void generate_block_statement(gen_node * node)


int __cdecl generate_block_statement(gen_node *node)

{
  uint uVar1;
  int sym;
  gen_node *stmt;
  ushort fpr_bits;
  uint uVar2;
  short i;
  ushort saved_fpr_mask;
  ushort saved_gpr_mask;
  undefined4 *scope_block;
  short scope_symx;
  il_op stmt_op;
  byte var_reg;
  
  if ((*(short *)g_request->unknown_004 == 0) && ((node->val & 1) == 0)) {
    fill_psd_record((psd *)&g_psd_scratch,OP_BBGN,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                    (ea *)0x0,(ea *)0x0,0,'\0');
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  saved_fpr_mask = g_var_fpr_mask;
  saved_gpr_mask = g_var_gpr_mask;
  uVar1 = (int)node->symx + 0xb6;
  uVar2 = (int)uVar1 >> 0x1f;
  scope_block = g_symbol_table[(uVar1 ^ uVar2) - uVar2].list_10;
  do {
    if (scope_block == (undefined4 *)0x0) {
      stmt = read_ilb_node(g_ilb_file);
      if (stmt == (gen_node *)0x0) {
        report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
      }
      stmt_op = stmt->op;
      while (stmt_op != IL_E_BLOCK) {
        generate_statement(stmt);
        unlink_and_free_subtree(node->child);
        stmt = read_ilb_node(g_ilb_file);
        if (stmt == (gen_node *)0x0) {
          report_codegen_message(0xce6,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
        }
        stmt_op = stmt->op;
      }
      if (stmt->parent->parent->op == IL_FUNC) {
        fill_line_record((psd *)&g_psd_scratch,OP_LINE,stmt->filn,stmt->line,'\0');
        emit_psd_record((psd *)&g_psd_scratch,0);
        g_msg_filn = stmt->filn;
        g_msg_line = stmt->line;
      }
      unlink_and_free_subtree(stmt);
      node->child = (gen_node *)0x0;
      g_var_gpr_mask = saved_gpr_mask;
      g_var_fpr_mask = saved_fpr_mask;
      if ((*(short *)g_request->unknown_004 == 0) && ((node->val & 1) == 0)) {
        fill_psd_record((psd *)&g_psd_scratch,OP_BEND,'\x02','\0',g_stmt_serial,g_msg_filn,
                        g_msg_line,(ea *)0x0,(ea *)0x0,0,'\0');
        emit_psd_record((psd *)&g_psd_scratch,0);
      }
      return;
    }
    i = 0;
    do {
      scope_symx = *(short *)((int)scope_block + i * 2 + 8);
      if (scope_symx == -1) break;
      uVar1 = (int)scope_symx >> 0x1f;
      sym = ((int)scope_symx ^ uVar1) - uVar1;
      if ((g_symbol_table[sym].sclass == '\x06') && ((g_symbol_table[sym].storage.type & 0xf) == 1))
      {
        var_reg = g_symbol_table[sym].storage.base;
        if ((char)var_reg < '\x10') {
          g_var_gpr_mask = g_var_gpr_mask | 1 << (var_reg & 0x1f);
        }
        else {
          if ((char)var_reg < ' ') {
            fpr_bits = 1 << (var_reg - 0x10 & 0x1f);
          }
          else {
            fpr_bits = 1 << (var_reg - 0x1f & 0x1f) | 1 << (var_reg - 0x20 & 0x1f);
          }
          g_var_fpr_mask = g_var_fpr_mask | fpr_bits;
        }
      }
      i = i + 1;
    } while (i < 4);
    scope_block = (undefined4 *)*scope_block;
  } while( true );
}



