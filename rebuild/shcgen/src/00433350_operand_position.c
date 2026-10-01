#include "decls.h"
#include "imports.h"

// entry: 00433350
// name : operand_position
// size : 57
// sig  : int operand_position(gen_node * node)


int __cdecl operand_position(gen_node *node)

{
  gen_node *sibling;
  int position;
  bool not_found;
  
  if ((node != (gen_node *)0x0) && (node->parent != (gen_node *)0x0)) {
    sibling = node->parent->child;
    position = 1;
    not_found = sibling == (gen_node *)0x0;
    if (!not_found) {
      do {
        if (sibling == node) break;
        sibling = sibling->next;
        position = position + 1;
      } while (sibling != (gen_node *)0x0);
      not_found = sibling == (gen_node *)0x0;
    }
    if (!not_found) {
      return position;
    }
  }
  return -1;
}



