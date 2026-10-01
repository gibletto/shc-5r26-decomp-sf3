#include "decls.h"
#include "imports.h"

// entry: 00437980
// name : fold_double_ge
// size : 64
// sig  : char fold_double_ge(uint * a, uint * b, int * result)


char __cdecl fold_double_ge(uint *a,uint *b,int *result)

{
  short cmp;
  
  cmp = compare_double_constants(a,b);
  if (0 < cmp) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == -1;
}



