#include "decls.h"
#include "imports.h"

// entry: 004172d0
// name : link_node_blocks
// size : 57
// sig  : void link_node_blocks(void)


int __cdecl link_node_blocks(void)

{
  il_node **slot;
  int i;
  
  i = 0;
  if (g_node_block_count != 1 && -1 < g_node_block_count + -1) {
    slot = g_node_block_table;
    do {
      i = i + 1;
      (*slot)->next = slot[1];
      slot = slot + 1;
    } while (i < g_node_block_count + -1);
  }
  g_node_block_table[i]->next = (il_node *)0x0;
  return;
}



