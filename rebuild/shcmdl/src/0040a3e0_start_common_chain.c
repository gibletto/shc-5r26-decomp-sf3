#include "decls.h"
#include "imports.h"

// entry: 0040a3e0
// name : start_common_chain
// size : 39
// sig  : void start_common_chain(il_node * node)


int __cdecl start_common_chain(il_node *node)

{
  node->refcnt = 1;
  node->refchn = (il_node *)0x0;
  node->cmnexp = node;
  g_value_number = g_value_number + 1;
  node->pp = g_value_number;
  return;
}



