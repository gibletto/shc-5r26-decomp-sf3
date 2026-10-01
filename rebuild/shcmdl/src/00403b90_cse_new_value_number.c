#include "decls.h"
#include "imports.h"

// entry: 00403b90
// name : cse_new_value_number
// size : 39
// sig  : void cse_new_value_number(il_node * node)


int __cdecl cse_new_value_number(il_node *node)

{
  node->refcnt = 1;
  node->cse_next = (il_node *)0x0;
  node->cse_head = node;
  g_value_number = g_value_number + 1;
  node->pp = g_value_number;
  return;
}



