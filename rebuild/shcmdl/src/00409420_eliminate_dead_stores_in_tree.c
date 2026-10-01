#include "decls.h"
#include "imports.h"

// entry: 00409420
// name : eliminate_dead_stores_in_tree
// size : 48
// sig  : il_node * __cdecl eliminate_dead_stores_in_tree(il_node *node)


il_node * __cdecl eliminate_dead_stores_in_tree(il_node *node)

{
  il_node *piVar1;
  
  set_value_used_flag(node);
  for (piVar1 = node->child; piVar1 != (il_node *)0x0; piVar1 = piVar1->next) {
    piVar1 = eliminate_dead_stores_in_tree(piVar1);
  }
  piVar1 = eliminate_dead_store(node);
  return piVar1;
}
