#include "decls.h"
#include "imports.h"

// entry: 004100b0
// name : common_bitop_pair
// size : 39
// sig  : il_op common_bitop_pair(il_node * a, il_node * b)


il_op __cdecl common_bitop_pair(il_node *a,il_node *b)

{
  if ((a->op == IL_B_AND) && (b->op == IL_B_AND)) {
    return IL_B_AND;
  }
  if ((a->op == IL_B_OR) && (b->op == IL_B_OR)) {
    return IL_B_OR;
  }
  return IL_FILE;
}



