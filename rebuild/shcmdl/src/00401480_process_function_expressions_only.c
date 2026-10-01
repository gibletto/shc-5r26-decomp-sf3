#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_tree_in_file
#define g_tree_in_file (*(FILE * *)(g_sd + 0x26eec))


// entry: 00401480
// name : process_function_expressions_only
// size : 337
// sig  : void process_function_expressions_only(void)


int __cdecl process_function_expressions_only(void)

{
  il_node *holder;
  il_node *stmt;
  int depth;
  short filn;
  ushort line;
  short listno;
  il_op op;
  
  stock_fseek(g_tree_in_file,g_function_file_pos,0);
  holder = read_il_node();
  write_il_node(holder);
  free_node(holder);
  holder = read_il_node();
  depth = 0;
  write_il_node(holder);
  free_node(holder);
  holder = alloc_node_or_null();
  holder->op = IL_IF;
  while( true ) {
    stmt = read_il_node();
    op = stmt->op;
    if ((op == IL_E_BLOCK) && (depth == 0)) break;
    if ((char)op < ' ') {
      if (op == IL_BLOCK) {
        depth = depth + 1;
      }
      else if (op == IL_E_BLOCK) {
        depth = depth + -1;
      }
      write_il_node(stmt);
      free_node(stmt);
    }
    else {
      stmt = read_il_operands(stmt);
      if (stmt == (il_node *)0x0) {
        fatal_error(0xce6);
      }
      holder->child = stmt;
      stmt->parent = holder;
      if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 8) == 0) {
        filn = stmt->filn;
        line = stmt->line;
        listno = stmt->listno;
        g_suppress_no_effect_warning = '\0';
        stmt = opt_exp(stmt);
        stmt->filn = filn;
        stmt->line = line;
        stmt->listno = listno;
        report_fold_warnings(stmt);
      }
      mark_referenced_functions_in_tree(stmt);
      write_il_tree(stmt);
      free_tree(stmt);
    }
  }
  write_il_node(stmt);
  free_node(stmt);
  free_node(holder);
  return;
}



