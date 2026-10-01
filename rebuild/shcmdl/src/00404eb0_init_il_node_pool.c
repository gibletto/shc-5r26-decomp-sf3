#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_il_node_pool
#define g_il_node_pool (*(il_node * *)(g_sd + 0x1e500))


// entry: 00404eb0
// name : init_il_node_pool
// size : 51
// sig  : void init_il_node_pool(int count)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl init_il_node_pool(int count)

{
  g_il_node_pool = alloc_node_blocks(0x68,count);
  if (g_il_node_pool == (il_node *)0x0) {
    fatal_error(0xbcd);
  }
  _g_il_node_pool_count = count;
  reset_il_node_pool();
  return;
}



