#include "decls.h"
#include "imports.h"

// entry: 00426b30
// name : fold_sub_double
// size : 50
// sig  : uint fold_sub_double(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_sub_double(uint *lhs,uint *rhs,uint *result)

{
  uint uVar1;
  uint neg_rhs;
  uint neg_rhs_1;
  
  neg_rhs = *rhs ^ 0x80000000;
  neg_rhs_1 = rhs[1];
  uVar1 = fold_add_double(lhs,&neg_rhs,result);
  return uVar1;
}



