#include "decls.h"
#include "imports.h"

// entry: 00405a00
// name : push_list_item
// size : 41
// sig  : void push_list_item(node_list * * head, il_node * item)


int __cdecl push_list_item(node_list **head,il_node *item)

{
  node_list *cell;
  
  cell = pool_alloc(8);
  if (cell == (node_list *)0x0) {
    cfg_out_of_memory();
  }
  cell->next = *head;
  *head = cell;
  cell->node = item;
  return;
}



