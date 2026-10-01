#include "decls.h"
#include "imports.h"

// entry: 00425a10
// name : fold_long_double_le
// size : 74
// sig  : char fold_long_double_le(uint * a, uint * b, int * result)


char __cdecl fold_long_double_le(uint *a,uint *b,int *result)

{
  ushort cmp;
  
  cmp = compare_long_double_constants(a,b);
  if (((short)cmp < 2) && (cmp != 0xffff)) {
    *result = 1;
    return '\0';
  }
  *result = 0;
  return cmp == 0xffff;
}



