#include "decls.h"
#include "imports.h"

// entry: 0041c0e0
// name : classify_indexed_address_operands
// size : 59
// sig  : int classify_indexed_address_operands(gen_node * left, gen_node * right)


int __cdecl classify_indexed_address_operands(gen_node *left,gen_node *right)

{
  int shape;
  il_op op;
  
  if (right->op != IL_ID) {
    return 0;
  }
  op = left->op;
  if ((op == IL_CAST) || (op == IL_ASSIGN)) {
    shape = 2;
    if (left->child->op != IL_ID) {
      return 0;
    }
  }
  else {
    if (op != IL_ID) {
      return 0;
    }
    shape = 1;
  }
  return shape;
}



