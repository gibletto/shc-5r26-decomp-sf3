#include "decls.h"
#include "imports.h"

// entry: 00421190
// name : nth_operand
// size : 21
// sig  : il_node * nth_operand(int n, il_node * node)


il_node * __cdecl nth_operand(int n,il_node *node)

{
  il_node *operand;
  
  operand = node->child;
  while (n = n + -1, n != 0) {
    operand = operand->next;
  }
  return operand;
}



