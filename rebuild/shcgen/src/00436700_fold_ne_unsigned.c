#include "decls.h"
#include "imports.h"

// entry: 00436700
// name : fold_ne_unsigned
// size : 38
// sig  : int fold_ne_unsigned(int * lhs, int * rhs, int * result)


int __cdecl fold_ne_unsigned(int *lhs,int *rhs,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*lhs != *rhs) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



