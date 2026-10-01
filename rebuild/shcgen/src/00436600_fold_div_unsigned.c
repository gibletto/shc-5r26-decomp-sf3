#include "decls.h"
#include "imports.h"

// entry: 00436600
// name : fold_div_unsigned
// size : 45
// sig  : int fold_div_unsigned(uint * lhs, uint * rhs, uint * result)


int __cdecl fold_div_unsigned(uint *lhs,uint *rhs,uint *result)

{
  ulonglong quotient;
  
  if (*rhs == 0) {
    *result = 0;
    return CONCAT22((short)((uint)rhs >> 0x10),6);
  }
  quotient = (ulonglong)*lhs / (ulonglong)*rhs;
  *result = (uint)quotient;
  return (uint)(ushort)(quotient >> 0x10) << 0x10;
}



