#include "decls.h"
#include "imports.h"

// entry: 00426040
// name : fold_neg_unsigned
// size : 18
// sig  : uint fold_neg_unsigned(int * operand, int * result)


uint __cdecl fold_neg_unsigned(int *operand,int *result)

{
  *result = -*operand;
  return (uint)result & 0xffff0000;
}



