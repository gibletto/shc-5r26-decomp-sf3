#include "decls.h"
#include "imports.h"

// entry: 00404e80
// name : write_il_tree
// size : 39
// sig  : void write_il_tree(il_node * node)


int __cdecl write_il_tree(il_node *node)

{
  for (; node != (il_node *)0x0; node = node->next) {
    write_il_node(node);
    write_il_tree(node->child);
  }
  return;
}



