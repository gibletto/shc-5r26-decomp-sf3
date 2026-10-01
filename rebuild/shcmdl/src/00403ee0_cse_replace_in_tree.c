#include "decls.h"
#include "imports.h"

// entry: 00403ee0
// name : cse_replace_in_tree
// size : 55
// sig  : il_node * __cdecl cse_replace_in_tree(il_node *node,node_list *stmt,bblock *block)


il_node * __cdecl cse_replace_in_tree(il_node *node,node_list *stmt,bblock *block)

{
  il_node *piVar1;
  
  for (piVar1 = node->child; piVar1 != (il_node *)0x0; piVar1 = piVar1->next) {
    piVar1 = cse_replace_in_tree(piVar1,stmt,block);
  }
  piVar1 = cse_check_common_expression(node,stmt,block);
  return piVar1;
}
