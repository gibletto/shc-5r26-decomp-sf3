#include "decls.h"
#include "imports.h"

// entry: 00417270
// name : alloc_node_blocks
// size : 88
// sig  : il_node * alloc_node_blocks(uint size, int count)


il_node * __cdecl alloc_node_blocks(uint size,int count)

{
  il_node *dst;
  int i;
  il_node **slot;
  
  i = 0;
  g_node_block_count = 0;
  if (0 < count) {
    slot = g_node_block_table;
    do {
      dst = stock_malloc(size);
      if (dst == (il_node *)0x0) {
        return (il_node *)0x0;
      }
      i = i + 1;
      clear_bytes((char *)dst,size);
      g_node_block_count = g_node_block_count + 1;
      *slot = dst;
      slot = slot + 1;
    } while (i < count);
  }
  return g_node_block_table[0];
}



