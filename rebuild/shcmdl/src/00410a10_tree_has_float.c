#include "decls.h"
#include "imports.h"

// entry: 00410a10
// name : tree_has_float
// size : 55
// sig  : int tree_has_float(il_node * node)


int __cdecl tree_has_float(il_node *node)

{
  int result;
  il_node *sub;
  
  result = 0;
  sub = node->child;
  while( true ) {
    if (sub == (il_node *)0x0) {
      if ((node->type & 0xe0) == 0x20) {
        result = 1;
      }
      return result;
    }
    result = tree_has_float(sub);
    if (result == 1) break;
    sub = sub->next;
  }
  return 1;
}



