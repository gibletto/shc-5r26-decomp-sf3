#include "decls.h"
#include "imports.h"

// entry: 004361d0
// name : fold_neg_double
// size : 80
// sig  : uint fold_neg_double(uint * operand, uint * result)


uint __cdecl fold_neg_double(uint *operand,uint *result)

{
  uint in_EAX;
  uint hi;
  
  hi = *operand;
  if (((hi & 0x7ff00000) == 0x7ff00000) && (((hi & 0xfffff) != 0 || (operand[1] != 0)))) {
    *result = 0x7ff00000;
    result[1] = 1;
    return 1;
  }
  *result = hi ^ 0x80000000;
  result[1] = operand[1];
  return in_EAX & 0xffff0000;
}



