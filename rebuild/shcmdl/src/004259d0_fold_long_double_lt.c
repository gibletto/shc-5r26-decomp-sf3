#include "decls.h"
#include "imports.h"

// entry: 004259d0
// name : fold_long_double_lt
// size : 63
// sig  : char fold_long_double_lt(uint * a, uint * b, int * result)


char __cdecl fold_long_double_lt(uint *a,uint *b,int *result)

{
  ushort cmp;
  
  cmp = compare_long_double_constants(a,b);
  if (cmp == 0) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == 0xffff;
}



