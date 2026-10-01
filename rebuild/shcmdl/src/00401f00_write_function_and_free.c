#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))


// entry: 00401f00
// name : write_function_and_free
// size : 101
// sig  : void write_function_and_free(il_node * func)


int __cdecl write_function_and_free(il_node *func)

{
  write_il_tree(func);
  free_tree(func);
  reset_symbol_leaf_numbers();
  free_all_bblocks();
  free_loop_tree(g_loop_tree);
  g_loop_tree = (loop *)0x0;
  if (((g_inline_flags & 6) == 6) && (g_inline_scopes_changed == '\x01')) {
    commit_updated_symbol_info();
    g_inline_scopes_changed = '\0';
  }
  write_switch_tables();
  free_switch_tables();
  return;
}



