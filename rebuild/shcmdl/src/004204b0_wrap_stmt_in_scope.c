#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004204b0
// name : wrap_stmt_in_scope
// size : 108
// sig  : void wrap_stmt_in_scope(il_node * stmt)


int __cdecl wrap_stmt_in_scope(il_node *stmt)

{
  uint symx;
  scope_info *info;
  il_node *block_node;
  
  wrap_in_block_pair(stmt);
  block_node = stmt->parent;
  symx = new_symbol(0,'\n');
  block_node->symx = (short)symx;
  info = stock_calloc(1,0x14);
  if (info == (scope_info *)0x0) {
    abort_function_optimization();
  }
  g_symtab[block_node->symx].new_info = info;
  g_inline_scopes_changed = '\x01';
  collect_nested_block_scopes(block_node,info);
  add_scope_to_enclosing_block(block_node);
  return;
}



