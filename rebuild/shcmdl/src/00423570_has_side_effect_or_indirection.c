#include "decls.h"
#include "imports.h"

// entry: 00423570
// name : has_side_effect_or_indirection
// size : 100
// sig  : int has_side_effect_or_indirection(il_node * tree)


int __cdecl has_side_effect_or_indirection(il_node *tree)

{
  int effect;
  il_node *child;
  il_op op;
  
  if (tree == (il_node *)0x0) {
    return 0;
  }
  for (child = tree->child; child != (il_node *)0x0; child = child->next) {
    effect = has_side_effect_or_indirection(child);
    if (effect == 1) {
      return 1;
    }
  }
  op = tree->op;
  if (((op == IL_QUALIFY) ||
      ((((char)op < '0' || ('=' < (char)op)) && (((char)op < 'P' || ('_' < (char)op)))))) &&
     ((((tree->type & 2) == 0 && (op != IL_AMPER)) && (op != IL_ASTER)))) {
    return 0;
  }
  return 1;
}



