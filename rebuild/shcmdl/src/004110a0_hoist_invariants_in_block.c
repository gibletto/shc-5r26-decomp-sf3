#include "decls.h"
#include "imports.h"

// entry: 004110a0
// name : hoist_invariants_in_block
// size : 32
// sig  : void hoist_invariants_in_block(bblock * block)


int __cdecl hoist_invariants_in_block(bblock *block)

{
  node_list *item;
  
  for (item = block->ilnode; item != (node_list *)0x0; item = item->next) {
    hoist_invariants_in_tree(item->node);
  }
  return;
}



