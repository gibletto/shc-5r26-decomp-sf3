#include "decls.h"
#include "imports.h"

// entry: 00409d60
// name : dag_conditional
// size : 65
// sig  : void dag_conditional(il_node * node)


int __cdecl dag_conditional(il_node *node)

{
  il_node *operand;
  
  operand = node->child;
  build_dag(operand);
  g_cse_cond_depth = g_cse_cond_depth + '\x01';
  for (operand = operand->next; operand != (il_node *)0x0; operand = operand->next) {
    build_dag(operand);
  }
  g_cse_cond_depth = g_cse_cond_depth + -1;
  clear_common_links(node);
  return;
}



