#include "decls.h"
#include "imports.h"

// entry: 004362e0
// name : fold_int_mod
// size : 44
// sig  : int fold_int_mod(int * a, int * b, int * result)


int __cdecl fold_int_mod(int *a,int *b,int *result)

{
  uint truncated;
  int divisor;
  
  divisor = *b;
  if (divisor == 0) {
    return CONCAT22((short)((uint)b >> 0x10),6);
  }
  truncated = (*a / divisor) * divisor;
  *result = *a - truncated;
  return truncated & 0xffff0000;
}



