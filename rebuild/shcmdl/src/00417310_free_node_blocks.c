#include "decls.h"
#include "imports.h"

// entry: 00417310
// name : free_node_blocks
// size : 43
// sig  : void free_node_blocks(void)


int __cdecl free_node_blocks(void)

{
  il_node *ptr;
  int i;
  il_node **slot;
  
  i = 0;
  if (0 < g_node_block_count) {
    slot = g_node_block_table;
    do {
      ptr = *slot;
      slot = slot + 1;
      i = i + 1;
      stock_free(ptr);
    } while (i < g_node_block_count);
  }
  return;
}



