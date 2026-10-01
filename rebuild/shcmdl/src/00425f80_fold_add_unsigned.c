#include "decls.h"
#include "imports.h"

// entry: 00425f80
// name : fold_add_unsigned
// size : 22
// sig  : uint fold_add_unsigned(int * lhs, int * rhs, int * result)


uint __cdecl fold_add_unsigned(int *lhs,int *rhs,int *result)

{
  *result = *rhs + *lhs;
  return (uint)result & 0xffff0000;
}



