#include "decls.h"
#include "imports.h"

// entry: 00422fd0
// name : overwrite_with_constant
// size : 57
// sig  : il_node * overwrite_with_constant(il_node * node, il_node * constant)


il_node * __cdecl overwrite_with_constant(il_node *node,il_node *constant)

{
  node->op = constant->op;
  node->type = constant->type;
  node->val = constant->val;
  node->val2 = constant->val2;
  node->val3 = constant->val3;
  if (node->child != (il_node *)0x0) {
    free_tree(node->child);
  }
  return node;
}



