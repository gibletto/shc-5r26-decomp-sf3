#include "decls.h"
#include "imports.h"

// entry: 00436500
// name : fold_shr_signed
// size : 81
// sig  : uint fold_shr_signed(int * lhs, uint * count, int * result)


uint __cdecl fold_shr_signed(int *lhs,uint *count,int *result)

{
  ushort uVar1;
  uint shift;
  
  shift = *count;
  if (shift < 0x20) {
    if ((int)shift < 0) {
      *result = *lhs << (-(byte)shift & 0x1f);
      return (uint)result & 0xffff0000;
    }
    *result = *lhs >> ((byte)shift & 0x1f);
    return (uint)result & 0xffff0000;
  }
  uVar1 = (ushort)((uint)result >> 0x10);
  if ((int)(*lhs & -0x80000000) != 0) {
    *result = -1;
    return (uint)uVar1 << 0x10;
  }
  *result = 0;
  return (uint)uVar1 << 0x10;
}



