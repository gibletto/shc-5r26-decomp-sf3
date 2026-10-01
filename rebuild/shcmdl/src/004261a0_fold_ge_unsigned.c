#include "decls.h"
#include "imports.h"

// entry: 004261a0
// name : fold_ge_unsigned
// size : 38
// sig  : int fold_ge_unsigned(uint * lhs, uint * rhs, int * result)


int __cdecl fold_ge_unsigned(uint *lhs,uint *rhs,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*rhs <= *lhs) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



