#include "decls.h"
#include "imports.h"

// entry: 00428690
// name : fold_lnot_ldouble
// size : 52
// sig  : uint fold_lnot_ldouble(uint * operand, int * result)


uint __cdecl fold_lnot_ldouble(uint *operand,int *result)

{
  if ((((*operand & 0x7fffffff) == 0) && (operand[1] == 0)) && (operand[2] == 0)) {
    *result = 1;
    return (uint)result & 0xffff0000;
  }
  *result = 0;
  return (uint)result & 0xffff0000;
}



