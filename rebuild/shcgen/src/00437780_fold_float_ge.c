#include "decls.h"
#include "imports.h"

// entry: 00437780
// name : fold_float_ge
// size : 64
// sig  : char fold_float_ge(uint * a, uint * b, int * result)


char __cdecl fold_float_ge(uint *a,uint *b,int *result)

{
  short cmp;
  
  cmp = compare_float_constants(a,b);
  if (0 < cmp) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == -1;
}



