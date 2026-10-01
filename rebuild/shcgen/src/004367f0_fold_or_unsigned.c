#include "decls.h"
#include "imports.h"

// entry: 004367f0
// name : fold_or_unsigned
// size : 22
// sig  : uint fold_or_unsigned(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_or_unsigned(uint *lhs,uint *rhs,uint *result)

{
  *result = *lhs | *rhs;
  return (uint)result & 0xffff0000;
}



