#include "decls.h"
#include "imports.h"

// entry: 00436220
// name : fold_lnot_double
// size : 46
// sig  : uint fold_lnot_double(uint * operand, int * result)


uint __cdecl fold_lnot_double(uint *operand,int *result)

{
  if (((*operand & 0x7fffffff) == 0) && (operand[1] == 0)) {
    *result = 1;
    return (uint)result & 0xffff0000;
  }
  *result = 0;
  return (uint)result & 0xffff0000;
}



