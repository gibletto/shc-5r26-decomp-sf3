#include "decls.h"
#include "imports.h"

// entry: 0040bf20
// name : block_has_no_other_var_ref
// size : 59
// sig  : char block_has_no_other_var_ref(bblock * block, il_node * def1, il_node * def2, il_node * var)


char __cdecl block_has_no_other_var_ref(bblock *block,il_node *def1,il_node *def2,il_node *var)

{
  char ok;
  node_list *item;
  
  ok = '\x01';
  item = block->ilnode;
  while ((item != (node_list *)0x0 &&
         (ok = tree_has_no_other_var_ref(item->node,def1,def2,var), ok != '\0'))) {
    item = item->next;
  }
  return ok;
}



