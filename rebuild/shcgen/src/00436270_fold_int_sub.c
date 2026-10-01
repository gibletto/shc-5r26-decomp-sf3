#include "decls.h"
#include "imports.h"

// entry: 00436270
// name : fold_int_sub
// size : 22
// sig  : uint fold_int_sub(int * a, int * b, int * result)


uint __cdecl fold_int_sub(int *a,int *b,int *result)

{
  *result = *a - *b;
  return (uint)result & 0xffff0000;
}



