#include "decls.h"
#include "imports.h"

// entry: 004363b0
// name : fold_int_ne
// size : 38
// sig  : int fold_int_ne(int * a, int * b, int * result)


int __cdecl fold_int_ne(int *a,int *b,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*b != *a) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



