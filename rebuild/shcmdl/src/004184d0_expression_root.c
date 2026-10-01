#include "decls.h"
#include "imports.h"

// entry: 004184d0
// name : expression_root
// size : 23
// sig  : il_node * expression_root(il_node * node)


il_node * __cdecl expression_root(il_node *node)

{
  il_node *cur;
  il_node *parent;
  il_op parent_op;
  
  parent_op = node->parent->op;
  parent = node->parent;
  while (cur = parent, '\x1f' < (char)parent_op) {
    parent = cur->parent;
    parent_op = parent->op;
    node = cur;
  }
  return node;
}



