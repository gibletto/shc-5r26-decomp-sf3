#include "decls.h"
#include "imports.h"

// entry: 004257a0
// name : fold_double_lt
// size : 63
// sig  : char fold_double_lt(uint * a, uint * b, int * result)


char __cdecl fold_double_lt(uint *a,uint *b,int *result)

{
  short cmp;
  
  cmp = compare_double_constants(a,b);
  if (cmp == 0) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == -1;
}



