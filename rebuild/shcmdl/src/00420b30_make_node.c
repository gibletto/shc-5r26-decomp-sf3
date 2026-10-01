#include "decls.h"
#include "imports.h"

// entry: 00420b30
// name : make_node
// size : 219
// sig  : il_node * make_node(il_op op, uchar type, il_node * op1, il_node * op2, il_node * op3)


il_node * __cdecl make_node(il_op op,uchar type,il_node *op1,il_node *op2,il_node *op3)

{
  il_node *node;
  ushort flags;
  il_op new_op;
  il_node *operand;
  
  node = alloc_node_or_null();
  if (node == (il_node *)0x0) {
    abort_function_optimization();
  }
  node->op = op;
  node->type = type;
  node->child = op1;
  if (op1 != (il_node *)0x0) {
    op1->parent = node;
    node->child->next = op2;
    if (op2 != (il_node *)0x0) {
      node->child->next->next = op3;
      op2->parent = node;
      if (op3 != (il_node *)0x0) {
        op3->parent = node;
      }
    }
  }
  new_op = node->op;
  if ((((char)new_op < '0') || ('=' < (char)new_op)) &&
     (((char)new_op < 'P' || ('_' < (char)new_op)))) {
    flags = 0;
  }
  else {
    flags = 2;
  }
  flags = node->flag | flags;
  node->flag = flags;
  node->flag = ((node->type & 2) == 0) - 1 & 0x40 | flags;
  for (operand = node->child; operand != (il_node *)0x0; operand = operand->next) {
    node->nodes = node->nodes + operand->nodes;
    flags = (byte)operand->flag & 2 | node->flag;
    node->flag = flags;
    flags = (byte)operand->flag & 0x40 | flags;
    node->flag = flags;
    node->flag = operand->flag & 0x800 | flags;
  }
  return node;
}



