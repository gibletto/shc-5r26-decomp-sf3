#include "decls.h"
#include "imports.h"

// entry: 00436760
// name : fold_le_unsigned
// size : 38
// sig  : int fold_le_unsigned(uint * lhs, uint * rhs, int * result)


int __cdecl fold_le_unsigned(uint *lhs,uint *rhs,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*lhs <= *rhs) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



