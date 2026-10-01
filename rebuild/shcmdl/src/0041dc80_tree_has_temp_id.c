#include "decls.h"
#include "imports.h"

// entry: 0041dc80
// name : tree_has_temp_id
// size : 55
// sig  : int tree_has_temp_id(il_node * node)


int __cdecl tree_has_temp_id(il_node *node)

{
  int found;
  il_node *child;
  
  child = node->child;
  while( true ) {
    found = 0;
    if (child == (il_node *)0x0) {
      if ((node->op == IL_ID) && (node->symx < 0)) {
        found = 1;
      }
      return found;
    }
    found = tree_has_temp_id(child);
    if (found != 0) break;
    child = child->next;
  }
  return found;
}



