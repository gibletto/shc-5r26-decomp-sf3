#include "decls.h"
#include "imports.h"

// entry: 00436290
// name : fold_int_mul
// size : 23
// sig  : uint fold_int_mul(int * a, int * b, int * result)


uint __cdecl fold_int_mul(int *a,int *b,int *result)

{
  *result = *b * *a;
  return (uint)result & 0xffff0000;
}



