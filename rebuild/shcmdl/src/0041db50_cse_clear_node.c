#include "decls.h"
#include "imports.h"

// entry: 0041db50
// name : cse_clear_node
// size : 24
// sig  : void cse_clear_node(il_node * node)


int __cdecl cse_clear_node(il_node *node)

{
  node->refcnt = 0;
  node->cse_block = (bblock *)0x0;
  node->pp = 0;
  node->cse_head = (il_node *)0x0;
  node->cse_next = (il_node *)0x0;
  return;
}



