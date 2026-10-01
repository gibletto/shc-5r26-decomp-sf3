#include "decls.h"
#include "imports.h"

// entry: 004209d0
// name : operand_index
// size : 62
// sig  : int operand_index(il_node * node)


int __cdecl operand_index(il_node *node)

{
  int index;
  il_node *sibling;
  
  if ((node == (il_node *)0x0) || (node->parent == (il_node *)0x0)) {
    fatal_error(0x1069);
  }
  sibling = node->parent->child;
  index = 1;
  while( true ) {
    if (sibling == (il_node *)0x0) {
      return -1;
    }
    if (sibling == node) break;
    sibling = sibling->next;
    index = index + 1;
  }
  return index;
}



