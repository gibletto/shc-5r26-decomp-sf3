#include "decls.h"
#include "imports.h"

// entry: 00420cf0
// name : replace_and_free_node
// size : 53
// sig  : void replace_and_free_node(il_node * old_node, il_node * new_node)


int __cdecl replace_and_free_node(il_node *old_node,il_node *new_node)

{
  if ((old_node == (il_node *)0x0) || (new_node == (il_node *)0x0)) {
    fatal_error(0x106e);
  }
  replace_node(old_node,new_node);
  free_tree(old_node);
  return;
}



