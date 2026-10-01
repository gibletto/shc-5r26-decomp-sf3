#include "decls.h"
#include "imports.h"

// entry: 0040f9f0
// name : const_out_of_range
// size : 127
// sig  : int const_out_of_range(il_node * cst)


int __cdecl const_out_of_range(il_node *cst)

{
  char kind;
  uint uVar1;
  int result;
  byte ty;
  
  result = 0;
  ty = cst->type;
  if ((ty & 0xf8) == 0) {
    kind = '\0';
    uVar1 = 0xffffff00;
  }
  else {
    if ((ty & 0xf8) != 8) {
      return 0;
    }
    kind = '\b';
    uVar1 = 0xffff0000;
  }
  if (((ty & 0xe0) == 0) && ((ty & 4) != 0)) {
    if ((cst->val & uVar1) != 0) {
      return 1;
    }
  }
  else {
    uVar1 = type_limit(0,(int)kind);
    if ((int)uVar1 < cst->val) {
      return 1;
    }
    uVar1 = type_limit(1,(int)kind);
    if (cst->val < (int)uVar1) {
      result = 2;
    }
  }
  return result;
}



