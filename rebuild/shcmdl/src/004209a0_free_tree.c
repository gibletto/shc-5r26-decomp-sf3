#include "decls.h"
#include "imports.h"

// entry: 004209a0
// name : free_tree
// size : 44
// sig  : void free_tree(il_node * node)


int __cdecl free_tree(il_node *node)

{
  if (node != (il_node *)0x0) {
    free_tree(node->next);
    free_tree(node->child);
    free_node(node);
  }
  return;
}



