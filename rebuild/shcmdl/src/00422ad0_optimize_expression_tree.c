#include "decls.h"
#include "imports.h"

// entry: 00422ad0
// name : optimize_expression_tree
// size : 64
// sig  : il_node * __cdecl optimize_expression_tree(il_node *node,node_list *stmt,bblock *block)


il_node * __cdecl optimize_expression_tree(il_node *node,node_list *stmt,bblock *block)

{
  il_node *piVar1;
  
  for (piVar1 = node->child; piVar1 != (il_node *)0x0; piVar1 = piVar1->next) {
    piVar1 = optimize_expression_tree(piVar1,stmt,block);
  }
  piVar1 = propagate_constants(node);
  piVar1 = common_expression_to_temp(piVar1,stmt,block);
  return piVar1;
}
