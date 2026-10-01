#include "decls.h"
#include "imports.h"

// entry: 004366b0
// name : fold_bnot_unsigned
// size : 18
// sig  : uint fold_bnot_unsigned(uint * operand, uint * result)


uint __cdecl fold_bnot_unsigned(uint *operand,uint *result)

{
  *result = ~*operand;
  return (uint)result & 0xffff0000;
}



