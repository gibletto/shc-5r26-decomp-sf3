#include "decls.h"
#include "imports.h"

// entry: 00417f60
// name : add_induction_factor
// size : 74
// sig  : void add_induction_factor(il_node * node, il_node * factor)


int __cdecl add_induction_factor(il_node *node,il_node *factor)

{
  node_list *item;
  il_node *factor_copy;
  iv_use *use;
  
  use = g_iv_table[node->ivno].uses;
  item = pool_alloc(8);
  if (item == (node_list *)0x0) {
    free_induction_tables();
    abort_function_optimization();
  }
  factor_copy = copy_tree(0,factor);
  item->node = factor_copy;
  item->next = use->factors;
  use->factors = item;
  return;
}



