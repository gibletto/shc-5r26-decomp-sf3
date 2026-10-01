#include "decls.h"
#include "imports.h"

// entry: 0041c0e0
// name : count_matching_leaf_nodes
// size : 70
// sig  : int count_matching_leaf_nodes(il_node * tree, il_node * node)


int __cdecl count_matching_leaf_nodes(il_node *tree,il_node *node)

{
  int sub;
  int count;
  il_node *child;
  
  count = 0;
  if (((node->op == tree->op) && (tree->nleaf == node->nleaf)) && (tree != node)) {
    count = 1;
  }
  for (child = tree->child; child != (il_node *)0x0; child = child->next) {
    sub = count_matching_leaf_nodes(child,node);
    count = count + sub;
  }
  return count;
}



