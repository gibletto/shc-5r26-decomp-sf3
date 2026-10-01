#include "decls.h"
#include "imports.h"

// entry: 004229f0
// name : cast_operands_to_node_type
// size : 71
// sig  : void cast_operands_to_node_type(il_node * node)


int __cdecl cast_operands_to_node_type(il_node *node)

{
  il_node *parent;
  il_node *operand;
  
  operand = node->child;
  while (operand != (il_node *)0x0) {
    if (operand->op == IL_CAST) {
      operand->type = node->type & 0xfc;
      parent = operand;
    }
    else {
      parent = new_node(IL_CAST,node->type & 0xfc);
      insert_parent(operand,parent);
    }
    operand = parent->next;
  }
  return;
}



