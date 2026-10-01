#include "decls.h"
#include "imports.h"

// entry: 00412160
// name : find_loop_induction_in_block
// size : 32
// sig  : void find_loop_induction_in_block(bblock * block)


int __cdecl find_loop_induction_in_block(bblock *block)

{
  node_list *item;
  
  for (item = block->ilnode; item != (node_list *)0x0; item = item->next) {
    find_loop_induction(item->node);
  }
  return;
}



