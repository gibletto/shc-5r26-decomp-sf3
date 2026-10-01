#include "decls.h"
#include "imports.h"

// entry: 004364a0
// name : fold_or_signed
// size : 22
// sig  : uint fold_or_signed(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_or_signed(uint *lhs,uint *rhs,uint *result)

{
  *result = *rhs | *lhs;
  return (uint)result & 0xffff0000;
}



