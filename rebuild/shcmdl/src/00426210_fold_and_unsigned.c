#include "decls.h"
#include "imports.h"

// entry: 00426210
// name : fold_and_unsigned
// size : 22
// sig  : uint fold_and_unsigned(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_and_unsigned(uint *lhs,uint *rhs,uint *result)

{
  *result = *rhs & *lhs;
  return (uint)result & 0xffff0000;
}



