#include "decls.h"
#include "imports.h"

// entry: 0040f680
// name : simplify_negate
// size : 102
// sig  : il_node * simplify_negate(il_node * node)


il_node * __cdecl simplify_negate(il_node *node)

{
  il_node *operand;
  
  operand = node->child;
  if (operand->op == node->op) {
    operand = operand->child;
    replace_node(node,operand);
    free_node(node->child);
    free_node(node);
    return operand;
  }
  if ((node->op == IL_MINUS) && (operand->op == IL_SUB)) {
    swap_operands(operand);
    replace_node(node,operand);
    free_node(node);
    node = operand;
  }
  return node;
}



