#include "decls.h"
#include "imports.h"

// entry: 004138d0
// name : sort_block_statics_by_refcnt
// size : 83
// sig  : void sort_block_statics_by_refcnt(bblock * block)


int __cdecl sort_block_statics_by_refcnt(bblock *block)

{
  node_list *cur;
  node_list *next;
  node_list *pred;
  node_list *prev;
  bool swapped;
  
  do {
    swapped = false;
    pred = (node_list *)0x0;
    next = block->statics;
    prev = block->statics;
    while (cur = next, cur != (node_list *)0x0) {
      if (prev->node->refcnt < cur->node->refcnt) {
        swapped = true;
        if (block->statics == prev) {
          block->statics = cur;
        }
        else {
          pred->next = cur;
        }
        prev->next = cur->next;
        cur->next = prev;
      }
      pred = prev;
      prev = cur;
      next = cur->next;
    }
  } while (swapped);
  return;
}



