#include "decls.h"
#include "imports.h"

// entry: 00426260
// name : fold_shl_unsigned
// size : 43
// sig  : uint fold_shl_unsigned(int * lhs, uint * count, int * result)


uint __cdecl fold_shl_unsigned(int *lhs,uint *count,int *result)

{
  if (0x1f < *count) {
    *result = 0;
    return (uint)result & 0xffff0000;
  }
  *result = *lhs << ((byte)*count & 0x1f);
  return (uint)result & 0xffff0000;
}



