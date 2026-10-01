#include "decls.h"
#include "imports.h"

// entry: 00433640
// name : count_operands
// size : 22
// sig  : int count_operands(gen_node * node)


int __cdecl count_operands(gen_node *node)

{
  int count;
  gen_node *operand;
  
  count = 0;
  for (operand = node->child; operand != (gen_node *)0x0; operand = operand->next) {
    count = count + 1;
  }
  return count;
}



