#include "decls.h"
#include "imports.h"

// entry: 00437150
// name : fold_sub_double
// size : 50
// sig  : uint fold_sub_double(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_sub_double(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_8[8];
#define neg_rhs (*(uint *)(_frec_8 + 0))
#define neg_rhs_1 (*(uint *)(_frec_8 + 4))
  uint uVar1;
  
  neg_rhs = *rhs ^ 0x80000000;
  neg_rhs_1 = rhs[1];
  uVar1 = fold_add_double(lhs,&neg_rhs,result);
  return uVar1;
#undef neg_rhs
#undef neg_rhs_1
}



