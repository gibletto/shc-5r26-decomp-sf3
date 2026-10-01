#include "decls.h"
#include "imports.h"

// entry: 004266c0
// name : fold_mul_float
// size : 358
// sig  : uint fold_mul_float(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_mul_float(uint *lhs,uint *rhs,uint *result)

{
  short bits;
  uint uVar1;
  ushort b_exp;
  ushort a_exp;
  uint product;
  uint product_1;
  uint result_sign;
  uint action;
  uint a_mant;
  int b_class;
  uint b_sign;
  int a_class;
  uint a_sign;
  uint b_mant;
  
  unpack_float(lhs,&a_sign,&a_exp,&a_mant,&a_class);
  unpack_float(rhs,&b_sign,&b_exp,&b_mant,&b_class);
  classify_mul_operands(a_sign,a_class,b_sign,b_class,(int *)&action,&result_sign);
  if (action == 0) {
    product_1 = 0;
    product = 0;
    bits = 0x18;
    do {
      if ((a_mant & 1) != 0) {
        product = product + b_mant;
      }
      if ((product & 1) == 0) {
        product_1 = (int)product_1 >> 1 & 0x7fffffff;
      }
      else {
        product_1 = (int)product_1 >> 1 | 0x80000000;
      }
      product = (int)product >> 1;
      a_mant = (int)a_mant >> 1;
      bits = bits + -1;
    } while (bits != 0);
    a_exp = a_exp + (b_exp - 0x7e);
    uVar1 = pack_round_float(result_sign,a_exp,&product,result);
    return uVar1;
  }
  if (action == 1) {
    *result = 0;
    *result = result_sign;
    return result_sign & 0xffff0000;
  }
  if (action == 2) {
    *result = 0x7f800000;
    *result = result_sign | 0x7f800000;
    return result_sign & 0xffff0000 | 0x7f800000;
  }
  if (action != 3) {
    return action & 0xffff0000;
  }
  *result = 0x7f800001;
  return 1;
}



