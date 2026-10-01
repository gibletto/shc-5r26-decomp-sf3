#include "decls.h"
#include "imports.h"

// entry: 00425ea0
// name : fold_xor_signed
// size : 22
// sig  : uint fold_xor_signed(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_xor_signed(uint *lhs,uint *rhs,uint *result)

{
  *result = *rhs ^ *lhs;
  return (uint)result & 0xffff0000;
}



