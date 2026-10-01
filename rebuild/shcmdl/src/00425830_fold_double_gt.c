#include "decls.h"
#include "imports.h"

// entry: 00425830
// name : fold_double_gt
// size : 64
// sig  : char fold_double_gt(uint * a, uint * b, int * result)


char __cdecl fold_double_gt(uint *a,uint *b,int *result)

{
  short cmp;
  
  cmp = compare_double_constants(a,b);
  if (cmp == 2) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == -1;
}



