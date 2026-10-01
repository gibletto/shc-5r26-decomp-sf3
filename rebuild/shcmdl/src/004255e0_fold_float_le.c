#include "decls.h"
#include "imports.h"

// entry: 004255e0
// name : fold_float_le
// size : 74
// sig  : char fold_float_le(uint * a, uint * b, int * result)


char __cdecl fold_float_le(uint *a,uint *b,int *result)

{
  short cmp;
  
  cmp = compare_float_constants(a,b);
  if ((cmp < 2) && (cmp != -1)) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == -1;
}



