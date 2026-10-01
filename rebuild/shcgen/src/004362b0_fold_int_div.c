#include "decls.h"
#include "imports.h"

// entry: 004362b0
// name : fold_int_div
// size : 44
// sig  : int fold_int_div(int * a, int * b, int * result)


int __cdecl fold_int_div(int *a,int *b,int *result)

{
  uint quotient;
  
  if (*b == 0) {
    *result = 0;
    return CONCAT22((short)((uint)b >> 0x10),6);
  }
  quotient = *a / *b;
  *result = quotient;
  return quotient & 0xffff0000;
}



