#include "decls.h"
#include "imports.h"

// entry: 00421020
// name : new_node
// size : 34
// sig  : il_node * new_node(il_op op, uchar type)


il_node * __cdecl new_node(il_op op,uchar type)

{
  il_node *node;
  
  node = alloc_node_or_null();
  if (node == (il_node *)0x0) {
    abort_function_optimization();
  }
  node->op = op;
  node->type = type;
  return node;
}



