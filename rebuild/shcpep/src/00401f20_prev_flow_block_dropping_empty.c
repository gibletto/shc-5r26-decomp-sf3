#include "decls.h"
#include "imports.h"

// entry: 00401f20
// name : prev_flow_block_dropping_empty
// size : 142
// sig  : flow_block * prev_flow_block_dropping_empty(flow_block * block)


flow_block * __cdecl prev_flow_block_dropping_empty(flow_block *block)

{
  char unlinked;
  psd *rec;
  int i;
  flow_block *neighbour;
  code_node *node;
  psd_op op;
  
  if ((block == (flow_block *)0x0) || (block->prev == (flow_block *)0x0)) {
    return (flow_block *)0x0;
  }
  while ((((neighbour = block->prev, neighbour != (flow_block *)0x0 &&
           (node = neighbour->code, node->labno == 0)) && (node->target_labno == 0)) &&
         (neighbour->flags == '\0'))) {
    for (; node != (code_node *)0x0; node = node->next) {
      rec = node->psd;
      i = 0;
      do {
        if (rec == (psd *)0x0) break;
        op = rec->op;
        if (((op != OP_DUMMY) && (op != OP_LINE)) && ((op != OP_BBGN && (op != OP_BEND)))) {
          return neighbour;
        }
        i = i + 1;
        rec = rec + 1;
      } while (i < 0xf);
    }
    unlinked = unlink_unreferenced_flow_block(neighbour);
    if ((unlinked == '\0') || (free_flow_block(neighbour), block->prev == (flow_block *)0x0)) break;
  }
  return block->prev;
}



