#include "decls.h"
#include "imports.h"

// entry: 004257e0
// name : fold_double_le
// size : 74
// sig  : char fold_double_le(uint * a, uint * b, int * result)


char __cdecl fold_double_le(uint *a,uint *b,int *result)

{
  short cmp;
  
  cmp = compare_double_constants(a,b);
  if ((cmp < 2) && (cmp != -1)) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == -1;
}



