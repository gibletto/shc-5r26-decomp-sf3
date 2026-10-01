#include "decls.h"
#include "imports.h"

// entry: 0040a7c0
// name : clear_common_links
// size : 21
// sig  : void clear_common_links(il_node * node)


int __cdecl clear_common_links(il_node *node)

{
  node->refcnt = 0;
  node->cmnexp = (il_node *)0x0;
  node->pp = 0;
  node->refchn = (il_node *)0x0;
  return;
}



