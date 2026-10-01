#include "decls.h"
#include "imports.h"

// entry: 00437190
// name : fold_mul_double
// size : 469
// sig  : uint fold_mul_double(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_mul_double(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_3c[60];
#define b_exp (*(ushort *)(_frec_3c + 0))
#define a_exp (*(ushort *)(_frec_3c + 2))
#define result_sign (*(uint *)(_frec_3c + 4))
#define a_mant (*(uint *)(_frec_3c + 8))
#define a_mant_1 (*(uint *)(_frec_3c + 12))
#define local_2c (*(uint (*)[6])(_frec_3c + 16))
#define b_sign (*(uint *)(_frec_3c + 40))
#define a_class (*(int *)(_frec_3c + 44))
#define a_sign (*(uint *)(_frec_3c + 48))
#define b_mant (*(uint (*)[2])(_frec_3c + 52))
  uint uVar1;
  short w;
  short bits;
  uint *word_ptr;
  
  unpack_double(lhs,&a_sign,&a_exp,&a_mant,&a_class);
  unpack_double(rhs,&b_sign,&b_exp,b_mant,(int *)(local_2c + 5));
  classify_mul_operands(a_sign,a_class,b_sign,local_2c[5],(int *)local_2c,&result_sign);
  if (local_2c[0] == 0) {
    bits = 0x35;
    local_2c[4] = 0;
    local_2c[3] = 0;
    local_2c[2] = 0;
    local_2c[1] = 0;
    do {
      if ((a_mant_1 & 1) != 0) {
        add_multiword(local_2c + 1,b_mant,2);
      }
      w = 3;
      do {
        word_ptr = local_2c + w + 1;
        uVar1 = (int)*word_ptr >> 1;
        *word_ptr = uVar1;
        if ((local_2c[w] & 1) == 0) {
          uVar1 = uVar1 & 0x7fffffff;
        }
        else {
          uVar1 = uVar1 | 0x80000000;
        }
        w = w + -1;
        *word_ptr = uVar1;
      } while (w != 0);
      local_2c[1] = (int)local_2c[1] >> 1;
      if ((a_mant & 1) == 0) {
        a_mant_1 = (int)a_mant_1 >> 1 & 0x7fffffff;
      }
      else {
        a_mant_1 = (int)a_mant_1 >> 1 | 0x80000000;
      }
      a_mant = (int)a_mant >> 1;
      bits = bits + -1;
    } while (bits != 0);
    if (local_2c[4] != 0) {
      local_2c[3] = local_2c[3] | 1;
    }
    a_exp = a_exp + (b_exp - 0x3fe);
    uVar1 = pack_round_double(result_sign,a_exp,local_2c + 1,result);
    return uVar1;
  }
  if (local_2c[0] == 1) {
    result[1] = 0;
    *result = 0;
    *result = result_sign;
    return result_sign & 0xffff0000;
  }
  if (local_2c[0] == 2) {
    *result = 0x7ff00000;
    result[1] = 0;
    *result = result_sign | 0x7ff00000;
    return result_sign & 0xffff0000 | 0x7ff00000;
  }
  if (local_2c[0] != 3) {
    return local_2c[0] & 0xffff0000;
  }
  *result = 0x7ff00000;
  result[1] = 1;
  return 1;
#undef b_exp
#undef a_exp
#undef result_sign
#undef a_mant
#undef a_mant_1
#undef local_2c
#undef b_sign
#undef a_class
#undef a_sign
#undef b_mant
}



