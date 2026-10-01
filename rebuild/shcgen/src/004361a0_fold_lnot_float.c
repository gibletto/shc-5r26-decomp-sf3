#include "decls.h"
#include "imports.h"

// entry: 004361a0
// name : fold_lnot_float
// size : 36
// sig  : int fold_lnot_float(uint * operand, int * result)


int __cdecl fold_lnot_float(uint *operand,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if ((*operand & 0x7fffffff) != 0) {
    *result = 0;
    return (uint)uVar1 << 0x10;
  }
  *result = 1;
  return (uint)uVar1 << 0x10;
}



