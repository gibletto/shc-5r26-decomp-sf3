#include "decls.h"
#include "imports.h"

// entry: 0041dbb0
// name : cse_global_block
// size : 35
// sig  : void cse_global_block(bblock * block)


int __cdecl cse_global_block(bblock *block)

{
  node_list *item;
  
  for (item = block->ilnode; item != (node_list *)0x0; item = item->next) {
    cse_global_tree(item->node,block);
  }
  return;
}



