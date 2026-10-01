#include "decls.h"
#include "imports.h"

// entry: 00403b10
// name : cse_clear_value_number
// size : 21
// sig  : void cse_clear_value_number(il_node * node)


int __cdecl cse_clear_value_number(il_node *node)

{
  node->refcnt = 0;
  node->cse_head = (il_node *)0x0;
  node->pp = 0;
  node->cse_next = (il_node *)0x0;
  return;
}



