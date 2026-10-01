#include "decls.h"
#include "imports.h"

// entry: 00422700
// name : strip_operand_casts
// size : 79
// sig  : void strip_operand_casts(il_node * left, il_node * right)


int __cdecl strip_operand_casts(il_node *left,il_node *right)

{
  if (left->op == IL_CAST) {
    replace_node(left,left->child);
    left->child = (il_node *)0x0;
    free_node(left);
  }
  if (right->op == IL_CAST) {
    replace_node(right,right->child);
    right->child = (il_node *)0x0;
    free_node(right);
  }
  return;
}



