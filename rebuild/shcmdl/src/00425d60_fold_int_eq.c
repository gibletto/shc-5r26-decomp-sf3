#include "decls.h"
#include "imports.h"

// entry: 00425d60
// name : fold_int_eq
// size : 38
// sig  : int fold_int_eq(int * a, int * b, int * result)


int __cdecl fold_int_eq(int *a,int *b,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*b == *a) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



