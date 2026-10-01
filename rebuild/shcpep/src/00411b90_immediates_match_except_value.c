#include "decls.h"
#include "imports.h"

// entry: 00411b90
// name : immediates_match_except_value
// size : 70
// sig  : int immediates_match_except_value(ea * a, ea * b)


int __cdecl immediates_match_except_value(ea *a,ea *b)

{
  char equal;
  int iVar1;
  int b_disp;
  
  iVar1 = 0;
  if (((a->type & 0x1f) == 7) && ((b->type & 0x1f) == 7)) {
    iVar1 = a->disp;
    b_disp = b->disp;
    a->disp = 0;
    b->disp = 0;
    equal = operands_equal(a,b);
    a->disp = iVar1;
    iVar1 = (int)equal;
    b->disp = b_disp;
  }
  return iVar1;
}



