#include "decls.h"
#include "imports.h"

// entry: 00436ce0
// name : fold_mul_float
// size : 358
// sig  : uint fold_mul_float(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_mul_float(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_2c[44];
#define b_exp (*(ushort *)(_frec_2c + 0))
#define a_exp (*(ushort *)(_frec_2c + 2))
#define product (*(uint *)(_frec_2c + 4))
#define product_1 (*(uint *)(_frec_2c + 8))
#define result_sign (*(uint *)(_frec_2c + 12))
#define action (*(uint *)(_frec_2c + 16))
#define a_mant (*(uint *)(_frec_2c + 20))
#define b_class (*(int *)(_frec_2c + 24))
#define b_sign (*(uint *)(_frec_2c + 28))
#define a_class (*(int *)(_frec_2c + 32))
#define a_sign (*(uint *)(_frec_2c + 36))
#define b_mant (*(uint *)(_frec_2c + 40))
  short bits;
  uint uVar1;
  
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
#undef b_exp
#undef a_exp
#undef product
#undef product_1
#undef result_sign
#undef action
#undef a_mant
#undef b_class
#undef b_sign
#undef a_class
#undef a_sign
#undef b_mant
}



