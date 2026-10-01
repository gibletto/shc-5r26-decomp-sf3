#include "decls.h"
#include "imports.h"

// entry: 00425fc0
// name : fold_mul_unsigned
// size : 23
// sig  : uint fold_mul_unsigned(int * lhs, int * rhs, int * result)


uint __cdecl fold_mul_unsigned(int *lhs,int *rhs,int *result)

{
  *result = *rhs * *lhs;
  return (uint)result & 0xffff0000;
}



