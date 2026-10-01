#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00406bc0
// name : generate_statement
// size : 609
// sig  : void generate_statement(gen_node * stmt)


int __cdecl generate_statement(gen_node *stmt)

{
  int line_kind;
  gen_node *tree;
  
  g_msg_filn = stmt->filn;
  g_msg_line = stmt->line;
  switch(stmt->op) {
  case IL_BLOCK:
    line_kind = 0;
    break;
  default:
    line_kind = 10;
    break;
  case IL_EMPTY:
    line_kind = -1;
    break;
  case IL_SWITCH:
    line_kind = 5;
    break;
  case IL_IF:
    line_kind = 1;
    break;
  case IL_FOR:
    line_kind = 3;
    break;
  case IL_WHILE:
    line_kind = 2;
    break;
  case IL_DO:
    line_kind = 4;
    break;
  case IL_RETURN:
    line_kind = 9;
    break;
  case IL_BREAK:
    line_kind = 7;
    break;
  case IL_CONTINUE:
    line_kind = 8;
    break;
  case IL_GOTO:
    line_kind = 6;
    break;
  case IL_GLABEL:
    line_kind = 0xb;
    break;
  case IL_CLABEL:
    line_kind = 0xc;
    break;
  case IL_DLABEL:
    line_kind = 0xd;
  }
  if (line_kind != -1) {
    fill_line_record((psd *)&g_psd_scratch,OP_LINE,stmt->filn,stmt->line,(char)line_kind);
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  switch(stmt->op) {
  case IL_BLOCK:
    generate_block_statement(stmt);
    break;
  default:
    tree = read_ilb_tree(stmt,g_ilb_file);
    if (tree == (gen_node *)0x0) {
      report_codegen_message(0xce6,stmt->filn,(uint)stmt->line,(int)stmt->listno,(char *)0x0);
    }
    generate_statement_expression(stmt,0,0);
    g_last_stmt_jumps = 0;
    break;
  case IL_EMPTY:
    g_last_stmt_jumps = 0;
    break;
  case IL_SWITCH:
    generate_switch_statement(stmt);
    g_last_stmt_jumps = 0;
    break;
  case IL_IF:
    generate_if_statement(stmt);
    g_last_stmt_jumps = 0;
    break;
  case IL_FOR:
    generate_for_statement(stmt);
    g_last_stmt_jumps = 0;
    break;
  case IL_WHILE:
    generate_while_statement(stmt);
    g_last_stmt_jumps = 0;
    break;
  case IL_DO:
    generate_do_statement(stmt);
    g_last_stmt_jumps = 0;
    break;
  case IL_RETURN:
    gen_return_statement(stmt);
    g_last_stmt_jumps = 1;
    break;
  case IL_BREAK:
    gen_break_statement();
    g_last_stmt_jumps = 1;
    break;
  case IL_CONTINUE:
    gen_continue_statement();
    g_last_stmt_jumps = 1;
    break;
  case IL_GOTO:
    gen_goto_statement(stmt);
    g_last_stmt_jumps = 1;
    break;
  case IL_GLABEL:
  case IL_CLABEL:
  case IL_DLABEL:
    gen_label_statement(stmt);
  }
  if (((('\x0f' < (char)stmt->op) && ((char)stmt->op < '\x1c')) &&
      (invalidate_register_contents(0xf000f), g_request->cpu == 4)) &&
     (g_request->unknown_155[2] == '\0')) {
    g_fpscr_pr = '\x02';
  }
  if (stmt->op == IL_BREAK) {
    g_case_restores_contents = '\x01';
    return;
  }
  if (stmt->op != IL_BLOCK) {
    g_case_restores_contents = '\0';
  }
  return;
}



