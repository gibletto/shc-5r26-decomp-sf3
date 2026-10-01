#include "decls.h"
#include "imports.h"

// entry: 00413330
// name : make_empty_block
// size : 39
// sig  : il_node * make_empty_block(void)


il_node * make_empty_block(void)

{
  il_node *parent;
  il_node *node;
  
  parent = alloc_node();
  parent->op = IL_BLOCK;
  node = alloc_node();
  node->op = IL_E_BLOCK;
  parent->child = node;
  node->parent = parent;
  insert_parent(node,parent);
  return parent;
}



