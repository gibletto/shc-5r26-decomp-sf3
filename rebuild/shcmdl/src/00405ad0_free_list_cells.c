#include "decls.h"
#include "imports.h"

// entry: 00405ad0
// name : free_list_cells
// size : 31
// sig  : void free_list_cells(node_list * list)


int __cdecl free_list_cells(node_list *list)

{
  node_list *next_cell;
  
  while (list != (node_list *)0x0) {
    next_cell = list->next;
    pool_free(list,8);
    list = next_cell;
  }
  return;
}



