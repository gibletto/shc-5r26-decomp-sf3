#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_il_node_pool
#define g_il_node_pool (*(il_node * *)(g_sd + 0x1e500))
#undef g_node_free_list
#define g_node_free_list (*(il_node * *)(g_sd + 0x26864))


// entry: 00404ef0
// name : reset_il_node_pool
// size : 15
// sig  : void reset_il_node_pool(void)


int __cdecl reset_il_node_pool(void)

{
  g_node_free_list = g_il_node_pool;
  link_node_blocks();
  return;
}



