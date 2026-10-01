#include "decls.h"
#include "imports.h"

// entry: 004059c0
// name : append_list_item
// size : 51
// sig  : void append_list_item(node_list * * head, il_node * item)


int __cdecl append_list_item(node_list **head,il_node *item)

{
  node_list *new_cell;
  node_list *cell;
  
  new_cell = pool_alloc(8);
  if (new_cell == (node_list *)0x0) {
    cfg_out_of_memory();
  }
  cell = *head;
  while (cell != (node_list *)0x0) {
    head = &(*head)->next;
    cell = *head;
  }
  *head = new_cell;
  new_cell->node = item;
  return;
}



