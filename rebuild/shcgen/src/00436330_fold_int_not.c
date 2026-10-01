#include "decls.h"
#include "imports.h"

// entry: 00436330
// name : fold_int_not
// size : 33
// sig  : int fold_int_not(int * a, int * result)


int __cdecl fold_int_not(int *a,int *result)

{
  ushort uVar1;
  
  uVar1 = (ushort)((uint)result >> 0x10);
  if (*a == 0) {
    *result = 1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



