#include "decls.h"
#include "imports.h"

// entry: 00436310
// name : fold_int_neg
// size : 18
// sig  : uint fold_int_neg(int * a, int * result)


uint __cdecl fold_int_neg(int *a,int *result)

{
  *result = -*a;
  return (uint)result & 0xffff0000;
}



