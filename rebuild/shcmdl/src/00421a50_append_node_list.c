#include "decls.h"
#include "imports.h"

// entry: 00421a50
// name : append_node_list
// size : 39
// sig  : node_list * append_node_list(node_list * list, node_list * tail)


node_list * __cdecl append_node_list(node_list *list,node_list *tail)

{
  node_list *head;
  node_list *next;
  
  head = list;
  if (list != (node_list *)0x0) {
    next = list->next;
    while (next != (node_list *)0x0) {
      list = list->next;
      next = list->next;
    }
    list->next = tail;
    return head;
  }
  return tail;
}



