#include "decls.h"
#include "imports.h"

// entry: 00420c10
// name : swap_operands
// size : 59
// sig  : int swap_operands(il_node * node)


int __cdecl swap_operands(il_node *node)

{
  il_node *first;
  il_node *second;
  
  if ((((node != (il_node *)0x0) && (first = node->child, first != (il_node *)0x0)) &&
      (second = first->next, second != (il_node *)0x0)) && (second->next == (il_node *)0x0)) {
    second->next = first;
    first = node->child->next;
    node->child = first;
    first->next->next = (il_node *)0x0;
    return 0;
  }
  return -1;
}



