#include "decls.h"
#include "imports.h"

// entry: 00420fa0
// name : delete_operand
// size : 122
// sig  : void delete_operand(il_node * parent, int pos)


int __cdecl delete_operand(il_node *parent,int pos)

{
  il_node *node;
  int index;
  il_node *prev;
  
  if ((parent == (il_node *)0x0) || (parent->child == (il_node *)0x0)) {
    fatal_error(0x1074);
  }
  if (pos != 1) {
    index = 2;
    prev = parent->child;
    node = parent->child->next;
    while( true ) {
      if (node == (il_node *)0x0) {
        fatal_error(0x1075);
        return;
      }
      if (index == pos) break;
      index = index + 1;
      prev = node;
      node = node->next;
    }
    prev->next = node->next;
    free_node(node);
    return;
  }
  prev = parent->child;
  parent->child = prev->next;
  free_node(prev);
  return;
}



