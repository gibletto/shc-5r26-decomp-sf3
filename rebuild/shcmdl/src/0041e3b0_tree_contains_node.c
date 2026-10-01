#include "decls.h"
#include "imports.h"

// entry: 0041e3b0
// name : tree_contains_node
// size : 47
// sig  : il_node * tree_contains_node(il_node * tree, il_node * node)


il_node * __cdecl tree_contains_node(il_node *tree,il_node *node)

{
  il_node *found;
  il_node *child;
  
  if (node != tree) {
    for (child = tree->child; child != (il_node *)0x0; child = child->next) {
      found = tree_contains_node(child,node);
      if (found != (il_node *)0x0) {
        return found;
      }
    }
    tree = (il_node *)0x0;
  }
  return tree;
}



