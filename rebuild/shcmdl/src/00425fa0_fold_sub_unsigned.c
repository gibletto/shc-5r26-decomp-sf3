#include "decls.h"
#include "imports.h"

// entry: 00425fa0
// name : fold_sub_unsigned
// size : 22
// sig  : uint fold_sub_unsigned(int * lhs, int * rhs, int * result)


uint __cdecl fold_sub_unsigned(int *lhs,int *rhs,int *result)

{
  *result = *lhs - *rhs;
  return (uint)result & 0xffff0000;
}



