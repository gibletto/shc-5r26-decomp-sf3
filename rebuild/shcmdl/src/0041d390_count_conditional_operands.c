#include "decls.h"
#include "imports.h"

// entry: 0041d390
// name : count_conditional_operands
// size : 73
// sig  : void count_conditional_operands(il_node * node, bblock * block)


int __cdecl count_conditional_operands(il_node *node,bblock *block)

{
  il_node *operand;
  
  operand = node->child;
  count_expression_tree(operand,block);
  g_cse_cond_depth = g_cse_cond_depth + '\x01';
  for (operand = operand->next; operand != (il_node *)0x0; operand = operand->next) {
    count_expression_tree(operand,block);
  }
  g_cse_cond_depth = g_cse_cond_depth + -1;
  cse_clear_node(node);
  return;
}



