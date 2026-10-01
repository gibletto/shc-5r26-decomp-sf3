#include "decls.h"
#include "imports.h"

// entry: 00404e00
// name : read_il_operands
// size : 96
// sig  : il_node * read_il_operands(il_node * node)


il_node * __cdecl read_il_operands(il_node *node)

{
  il_node *operand;
  short remaining;
  short sVar1;
  il_node *prev;
  
  prev = (il_node *)0x0;
  remaining = *(short *)(&g_il_op_operand_count + (char)node->op * 2);
  while( true ) {
    sVar1 = remaining + -1;
    if (remaining == 0) {
      return node;
    }
    operand = read_il_tree();
    if (operand == (il_node *)0x0) break;
    if (prev == (il_node *)0x0) {
      node->child = operand;
    }
    else {
      prev->next = operand;
    }
    operand->parent = node;
    if ((node->op == IL_BLOCK) && (operand->op == IL_E_BLOCK)) {
      return node;
    }
    prev = operand;
    remaining = sVar1;
    if ((node->op == IL_ARG) && (operand->op == IL_E_ARG)) {
      return node;
    }
  }
  return (il_node *)0x0;
}



