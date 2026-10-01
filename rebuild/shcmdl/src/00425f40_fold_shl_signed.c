#include "decls.h"
#include "imports.h"

// entry: 00425f40
// name : fold_shl_signed
// size : 61
// sig  : uint fold_shl_signed(int * lhs, uint * count, int * result)


uint __cdecl fold_shl_signed(int *lhs,uint *count,int *result)

{
  uint shift;
  
  shift = *count;
  if (0x1f < shift) {
    *result = 0;
    return (uint)result & 0xffff0000;
  }
  if ((int)shift < 0) {
    *result = *lhs >> (-(byte)shift & 0x1f);
    return (uint)result & 0xffff0000;
  }
  *result = *lhs << ((byte)shift & 0x1f);
  return (uint)result & 0xffff0000;
}



