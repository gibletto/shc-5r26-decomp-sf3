#include "decls.h"
#include "imports.h"

// entry: 0041e350
// name : cse_find_using_stmt
// size : 82
// sig  : il_node * cse_find_using_stmt(bblock * block, il_node * node)


il_node * __cdecl cse_find_using_stmt(bblock *block,il_node *node)

{
  char not_cond;
  il_node *found;
  undefined3 extraout_var = 0;
  node_list *item;
  
  item = block->ilnode;
  while( true ) {
    if (item == (node_list *)0x0) {
      return (il_node *)0x0;
    }
    found = tree_contains_node(item->node,node);
    if (found != (il_node *)0x0) break;
    item = item->next;
  }
  if ((item->next == (node_list *)0x0) &&
     (not_cond = is_not_control_condition(item->node), CONCAT31(extraout_var,not_cond) == 0)) {
    return (il_node *)0x0;
  }
  return found;
}



