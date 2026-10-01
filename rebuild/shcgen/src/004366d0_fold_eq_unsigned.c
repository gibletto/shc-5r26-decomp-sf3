#include "decls.h"
#include "imports.h"

// entry: 004366d0
// name : fold_eq_unsigned
// size : 38
// sig  : int fold_eq_unsigned(int * lhs, int * rhs, int * result)


int __cdecl fold_eq_unsigned(int *lhs,int *rhs,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*rhs == *lhs) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



