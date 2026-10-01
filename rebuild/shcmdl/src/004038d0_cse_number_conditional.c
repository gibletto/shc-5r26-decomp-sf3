#include "decls.h"
#include "imports.h"

// entry: 004038d0
// name : cse_number_conditional
// size : 65
// sig  : void cse_number_conditional(il_node * node)


int __cdecl cse_number_conditional(il_node *node)

{
  il_node *operand;
  
  operand = node->child;
  cse_number_expression(operand);
  g_cse_cond_depth = g_cse_cond_depth + '\x01';
  for (operand = operand->next; operand != (il_node *)0x0; operand = operand->next) {
    cse_number_expression(operand);
  }
  g_cse_cond_depth = g_cse_cond_depth + -1;
  cse_clear_value_number(node);
  return;
}



