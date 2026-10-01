#include "decls.h"
#include "imports.h"

// entry: 00426520
// name : fold_sub_float
// size : 42
// sig  : uint fold_sub_float(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_sub_float(uint *lhs,uint *rhs,uint *result)

{
  uint uVar1;
  uint neg_rhs;
  
  neg_rhs = *rhs ^ 0x80000000;
  uVar1 = fold_add_float(lhs,&neg_rhs,result);
  return uVar1;
}



