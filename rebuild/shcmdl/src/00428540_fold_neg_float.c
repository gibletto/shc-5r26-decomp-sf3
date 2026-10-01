#include "decls.h"
#include "imports.h"

// entry: 00428540
// name : fold_neg_float
// size : 59
// sig  : uint fold_neg_float(uint * operand, uint * result)


uint __cdecl fold_neg_float(uint *operand,uint *result)

{
  uint bits;
  
  bits = *operand;
  if (((bits & 0x7f800000) == 0x7f800000) && ((bits & 0x7fffff) != 0)) {
    *result = 0x7f800001;
    return CONCAT22((short)((uint)result >> 0x10),1);
  }
  *result = bits ^ 0x80000000;
  return (uint)result & 0xffff0000;
}



