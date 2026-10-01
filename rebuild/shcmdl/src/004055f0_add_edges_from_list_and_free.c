#include "decls.h"
#include "imports.h"

// entry: 004055f0
// name : add_edges_from_list_and_free
// size : 49
// sig  : void add_edges_from_list_and_free(block_list * list, bblock * to)


int __cdecl add_edges_from_list_and_free(block_list *list,bblock *to)

{
  block_list *next_cell;
  
  while (list != (block_list *)0x0) {
    cfg_add_edge(list->block,to);
    next_cell = list->next;
    pool_free(list,8);
    list = next_cell;
  }
  return;
}



