#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))


// entry: 004035f0
// name : common_subexpression_elimination
// size : 57
// sig  : void common_subexpression_elimination(void)


int __cdecl common_subexpression_elimination(void)

{
  g_value_number = 0;
  g_cse_nesting = '\0';
  g_cse_cond_depth = '\0';
  g_cse_has_goto_or_label = '\0';
  g_in_builtin_call = '\0';
  cse_mark_unchained_blocks();
  cse_number_statements(g_func_node);
  cse_replace_in_blocks();
  cse_free_hash_tables();
  return;
}



