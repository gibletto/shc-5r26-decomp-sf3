#include "decls.h"
#include "imports.h"

// entry: 00425e50
// name : fold_ge_signed
// size : 38
// sig  : int fold_ge_signed(int * lhs, int * rhs, int * result)


int __cdecl fold_ge_signed(int *lhs,int *rhs,int *result)

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



