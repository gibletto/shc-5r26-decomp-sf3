#include "decls.h"
#include "imports.h"

// entry: 00426230
// name : fold_shr_unsigned
// size : 43
// sig  : uint fold_shr_unsigned(uint * lhs, uint * count, uint * result)


uint __cdecl fold_shr_unsigned(uint *lhs,uint *count,uint *result)

{
  if (0x1f < *count) {
    *result = 0;
    return (uint)result & 0xffff0000;
  }
  *result = *lhs >> ((byte)*count & 0x1f);
  return (uint)result & 0xffff0000;
}



