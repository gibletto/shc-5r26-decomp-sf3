#include "decls.h"
#include "imports.h"

// entry: 004364e0
// name : fold_and_signed
// size : 22
// sig  : uint fold_and_signed(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_and_signed(uint *lhs,uint *rhs,uint *result)

{
  *result = *rhs & *lhs;
  return (uint)result & 0xffff0000;
}



