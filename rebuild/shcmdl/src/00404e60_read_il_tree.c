#include "decls.h"
#include "imports.h"

// entry: 00404e60
// name : read_il_tree
// size : 19
// sig  : il_node * read_il_tree(void)


il_node * read_il_tree(void)

{
  il_node *node;
  il_node *tree;
  
  node = read_il_node();
  tree = (il_node *)0x0;
  if (node != (il_node *)0x0) {
    tree = read_il_operands(node);
  }
  return tree;
}
