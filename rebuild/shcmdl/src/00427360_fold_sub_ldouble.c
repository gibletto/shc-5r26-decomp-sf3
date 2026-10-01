#include "decls.h"
#include "imports.h"

// entry: 00427360
// name : fold_sub_ldouble
// size : 56
// sig  : uint fold_sub_ldouble(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_sub_ldouble(uint *lhs,uint *rhs,uint *result)

{
  uint uVar1;
  uint neg_rhs;
  uint neg_rhs_1;
  uint neg_rhs_2;
  
  neg_rhs_1 = rhs[1];
  neg_rhs = *rhs ^ 0x80000000;
  neg_rhs_2 = rhs[2];
  uVar1 = fold_add_ldouble(lhs,&neg_rhs,result);
  return uVar1;
}



