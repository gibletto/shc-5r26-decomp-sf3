#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 004013c0
// name : process_function_op0_inline
// size : 179
// sig  : void process_function_op0_inline(il_node * func)


int __cdecl process_function_op0_inline(il_node *func)

{
  il_node *node;
  
  node = read_il_operands(func);
  if (node == (il_node *)0x0) {
    abort_function_optimization();
  }
  if (((byte)g_debug_flags & 2) != 0) {
    dump_tree(node,0,s_op0inline_read_tree_004334a0);
  }
  g_pool_bytes_in_use = 0;
  prepare_function_for_optimization(node);
  if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 8) == 0) {
    g_suppress_no_effect_warning = '\0';
    opt_exp_all_blocks();
  }
  mark_referenced_functions();
  if (((byte)g_debug_flags & 2) != 0) {
    dump_tree(node,0,s_op0inline_write_tree_00433488);
  }
  write_function_and_free(node);
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x10) == 0) {
    if (0 < g_pool_bytes_in_use) {
      fatal_error(0x1091);
      return;
    }
    if (g_pool_bytes_in_use < 0) {
      fatal_error(0x1092);
    }
  }
  return;
}



