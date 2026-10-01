#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_flow_blocks
#define g_flow_blocks (*(flow_block * *)(g_sd + 0x6e08))


// entry: 00401100
// name : free_flow_block
// size : 142
// sig  : void __cdecl free_flow_block(flow_block *block)


int __cdecl free_flow_block(flow_block *block)

{
  flow_block *ptr;
  flow_edge *edge;
  flow_block *next;
  flow_edge *next_edge;
  
  if (block == (flow_block *)0x0) {
    ptr = g_flow_blocks;
    if (g_flow_blocks != (flow_block *)0x0) {
      do {
        next = ptr->next;
        edge = ptr->preds;
        while (edge != (flow_edge *)0x0) {
          next_edge = edge->next;
          pool_free(edge,8);
          edge = next_edge;
        }
        pool_free(ptr,0x28);
        ptr = next;
      } while (next != (flow_block *)0x0);
      g_flow_blocks = (flow_block *)0x0;
    }
    return;
  }
  edge = block->preds;
  while (edge != (flow_edge *)0x0) {
    next_edge = edge->next;
    pool_free(edge,8);
    edge = next_edge;
  }
  if (block->code != (code_node *)0x0) {
    free_node_list(block->code);
  }
  pool_free(block,0x28);
  return;
}
