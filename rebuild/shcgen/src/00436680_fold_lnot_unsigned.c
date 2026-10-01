#include "decls.h"
#include "imports.h"

// entry: 00436680
// name : fold_lnot_unsigned
// size : 33
// sig  : int fold_lnot_unsigned(int * operand, int * result)


int __cdecl fold_lnot_unsigned(int *operand,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*operand == 0) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



