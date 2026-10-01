#include "decls.h"
#include "imports.h"

// entry: 00401930
// name : unlink_unreferenced_flow_block
// size : 221
// sig  : char unlink_unreferenced_flow_block(flow_block * block)


char __cdecl unlink_unreferenced_flow_block(flow_block *block)

{
  flow_block *pfVar1;
  char removable;
  flow_edge *ptr;
  flow_block *next;
  flow_edge *prev_edge;
  
  if ((((block == (flow_block *)0x0) || (block->prev == (flow_block *)0x0)) ||
      (block->preds != (flow_edge *)0x0)) || ((block->flags & 8) != 0)) {
    return '\0';
  }
  pfVar1 = block->target;
  if (pfVar1 != (flow_block *)0x0) {
    ptr = pfVar1->preds;
    if (ptr != (flow_edge *)0x0) {
      if (ptr->block == block) {
        pfVar1->preds = ptr->next;
      }
      else {
        do {
          prev_edge = ptr;
          if (prev_edge == (flow_edge *)0x0) goto LAB_004019a2;
          ptr = prev_edge->next;
        } while ((ptr == (flow_edge *)0x0) || (ptr->block != block));
        ptr = prev_edge->next;
        prev_edge->next = ptr->next;
      }
      pool_free(ptr,8);
    }
LAB_004019a2:
    decrement_label_ref_count(pfVar1->code->labno);
    block->target = (flow_block *)0x0;
    if (pfVar1->preds == (flow_edge *)0x0) {
      while ((pfVar1 != block && (removable = simplify_flow_block(pfVar1), removable != '\0'))) {
        next = pfVar1->next;
        free_flow_block(pfVar1);
        pfVar1 = next;
      }
    }
  }
  pfVar1 = block->prev;
  pfVar1->next = block->next;
  pfVar1->code->next_block = block->code->next_block;
  if (block->next != (flow_block *)0x0) {
    block->next->prev = block->prev;
  }
  return '\x01';
}



