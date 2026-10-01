#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))


// entry: 00402040
// name : rebuild_cfg_and_leaves
// size : 91
// sig  : void rebuild_cfg_and_leaves(void)


int __cdecl rebuild_cfg_and_leaves(void)

{
  remove_unused_parameter_assignments();
  reset_symbol_leaf_numbers();
  free_all_bblocks();
  free_loop_tree(g_loop_tree);
  g_leaf_count = 0;
  g_loop_tree = (loop *)0x0;
  g_leafed_symbols = 0;
  g_leaf_cond_depth = 0;
  build_control_flow_graph(g_func_node->child);
  insert_parameter_self_assignments();
  assign_leaf_numbers(g_func_node);
  return;
}



