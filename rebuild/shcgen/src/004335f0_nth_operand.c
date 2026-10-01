#include "decls.h"
#include "imports.h"

// entry: 004335f0
// name : nth_operand
// size : 70
// sig  : gen_node * nth_operand(gen_node * node, int n)


gen_node * __cdecl nth_operand(gen_node *node,int n)

{
  short i;
  gen_node *found;
  gen_node *operand;
  
  if (n < 1) {
    return (gen_node *)0x0;
  }
  if (n != 1) {
    operand = node->child;
    for (i = 1; (operand != (gen_node *)0x0 && (i < n)); i = i + 1) {
      operand = operand->next;
    }
    found = (gen_node *)0x0;
    if (n <= i) {
      found = operand;
    }
    return found;
  }
  return node->child;
}



