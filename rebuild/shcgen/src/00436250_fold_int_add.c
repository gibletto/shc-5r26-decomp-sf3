#include "decls.h"
#include "imports.h"

// entry: 00436250
// name : fold_int_add
// size : 22
// sig  : uint fold_int_add(int * a, int * b, int * result)


uint __cdecl fold_int_add(int *a,int *b,int *result)

{
  *result = *b + *a;
  return (uint)result & 0xffff0000;
}



