#include "decls.h"
#include "imports.h"

// entry: 00425740
// name : fold_double_eq
// size : 48
// sig  : int fold_double_eq(uint * a, uint * b, int * result)


int __cdecl fold_double_eq(uint *a,uint *b,int *result)

{
  short cmp;
  ushort uVar1;
  
  cmp = compare_double_constants(a,b);
  uVar1 = (ushort)((uint)result >> 0x10);
  if (cmp == 1) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



