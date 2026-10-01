#include "decls.h"
#include "imports.h"

// entry: 00428630
// name : fold_neg_ldouble
// size : 91
// sig  : uint fold_neg_ldouble(uint * operand, uint * result)


uint __cdecl fold_neg_ldouble(uint *operand,uint *result)

{
  uint in_EAX;
  
  if (((*operand & 0x7fff0000) == 0x7fff0000) && ((operand[1] != 0 || (operand[2] != 0)))) {
    *result = 0x7fff0000;
    result[1] = 0x80000000;
    result[2] = 1;
    return 1;
  }
  *result = *operand ^ 0x80000000;
  result[1] = operand[1];
  result[2] = operand[2];
  return in_EAX & 0xffff0000;
}



