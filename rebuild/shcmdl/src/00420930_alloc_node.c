#include "decls.h"
#include "imports.h"

// entry: 00420930
// name : alloc_node
// size : 21
// sig  : il_node * alloc_node(void)


il_node * alloc_node(void)

{
  il_node *node;
  
  node = alloc_node_or_null();
  if (node == (il_node *)0x0) {
    abort_function_optimization();
  }
  return node;
}



