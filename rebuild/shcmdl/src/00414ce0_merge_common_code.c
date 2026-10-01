#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))


// entry: 00414ce0
// name : merge_common_code
// size : 61
// sig  : void merge_common_code(void)


int __cdecl merge_common_code(void)

{
  group_blocks_by_successor();
  find_common_tails();
  find_identical_predecessor_blocks();
  merge_identical_blocks();
  merge_common_tails();
  free_merge_tables();
  if (g_debug_flags == 2) {
    dump_tree(g_func_node,0,s_after_merge_tree_00435988);
  }
  return;
}



