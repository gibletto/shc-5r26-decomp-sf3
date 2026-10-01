#include "decls.h"
#include "imports.h"

// entry: 00436630
// name : fold_mod_unsigned
// size : 45
// sig  : int fold_mod_unsigned(uint * lhs, uint * rhs, int * result)


int __cdecl fold_mod_unsigned(uint *lhs,uint *rhs,int *result)

{
  uint uVar1;
  
  uVar1 = *rhs;
  if (uVar1 == 0) {
    return CONCAT22((short)((uint)rhs >> 0x10),6);
  }
  uVar1 = (*lhs / uVar1) * uVar1;
  *result = *lhs - uVar1;
  return uVar1 & 0xffff0000;
}



