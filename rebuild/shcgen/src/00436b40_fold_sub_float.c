#include "decls.h"
#include "imports.h"

// entry: 00436b40
// name : fold_sub_float
// size : 42
// sig  : uint fold_sub_float(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_sub_float(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_4[4];
#define neg_rhs (*(uint *)(_frec_4 + 0))
  uint uVar1;
  
  neg_rhs = *rhs ^ 0x80000000;
  uVar1 = fold_add_float(lhs,&neg_rhs,result);
  return uVar1;
#undef neg_rhs
}



