#include "decls.h"
#include "imports.h"

// entry: 0041d8f0
// name : cse_new_class
// size : 46
// sig  : void cse_new_class(il_node * node, bblock * block)


int __cdecl cse_new_class(il_node *node,bblock *block)

{
  node->refcnt = 1;
  node->cse_block = block;
  node->cse_head = node;
  node->cse_next = (il_node *)0x0;
  g_value_number = g_value_number + 1;
  node->pp = g_value_number;
  return;
}



