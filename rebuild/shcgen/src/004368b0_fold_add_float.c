#include "decls.h"
#include "imports.h"

// entry: 004368b0
// name : fold_add_float
// size : 630
// sig  : uint fold_add_float(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_add_float(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_2c[44];
#define b_exp (*(ushort *)(_frec_2c + 0))
#define a_exp (*(ushort *)(_frec_2c + 2))
#define b_mant (*(uint *)(_frec_2c + 4))
#define b_mant_1 (*(uint *)(_frec_2c + 8))
#define a_mant (*(uint *)(_frec_2c + 12))
#define a_mant_1 (*(uint *)(_frec_2c + 16))
#define a_sign (*(uint *)(_frec_2c + 20))
#define b_sign (*(uint *)(_frec_2c + 24))
#define action (*(int *)(_frec_2c + 28))
#define result_sign (*(uint *)(_frec_2c + 32))
#define b_class (*(int *)(_frec_2c + 36))
#define a_class (*(int *)(_frec_2c + 40))
  uint uVar1;
  undefined2 uVar2;
  ushort tmp_exp;
  uint tmp_sign;
  
  uVar2 = 0;
  unpack_float(lhs,&a_sign,&a_exp,&a_mant,&a_class);
  a_mant_1 = 0;
  unpack_float(rhs,&b_sign,&b_exp,&b_mant,&b_class);
  b_mant_1 = 0;
  classify_add_operands(a_sign,a_class,b_sign,b_class,&action,&result_sign);
  tmp_sign = a_sign;
  uVar1 = a_mant;
  tmp_exp = a_exp;
  if (action == 0) {
    if ((short)a_exp < (short)b_exp) {
      a_sign = b_sign;
      b_sign = tmp_sign;
      a_exp = b_exp;
      a_mant = b_mant;
      b_exp = tmp_exp;
      b_mant = uVar1;
    }
    if ((int)(short)a_exp - (int)(short)b_exp < 0x1a) {
      for (; (short)b_exp < (short)a_exp; b_exp = b_exp + 1) {
        if ((b_mant & 1) == 0) {
          b_mant_1 = (int)b_mant_1 >> 1 & 0x7fffffff;
        }
        else {
          b_mant_1 = (int)b_mant_1 >> 1 | 0x80000000;
        }
        b_mant = (int)b_mant >> 1;
        if ((b_mant_1 & 0x10000000) != 0) {
          b_mant_1 = b_mant_1 & 0xefffffff | 0x20000000;
        }
      }
    }
    else {
      b_mant = 0;
      b_mant_1 = 0x20000000;
      b_exp = a_exp;
    }
    if (b_sign == a_sign) {
      add_multiword(&a_mant,&b_mant,2);
      if ((a_mant & 0x1000000) != 0) {
        if ((a_mant & 1) == 0) {
          a_mant_1 = (int)a_mant_1 >> 1 & 0x7fffffff;
        }
        else {
          a_mant_1 = (int)a_mant_1 >> 1 | 0x80000000;
        }
        a_mant = (int)a_mant >> 1;
        a_exp = a_exp + 1;
      }
    }
    else {
      sub_multiword(&a_mant,&b_mant,2);
      if ((int)a_mant < 0) {
        a_sign = b_sign;
        negate_multiword(&a_mant,2);
      }
    }
    uVar1 = pack_round_float(a_sign,a_exp,&a_mant,result);
    uVar2 = (undefined2)uVar1;
  }
  else {
    uVar1 = action + 2;
    switch(uVar1) {
    case 0:
      uVar1 = *rhs;
      *result = uVar1;
      return uVar1 & 0xffff0000;
    case 1:
      uVar1 = *lhs;
      *result = uVar1;
      return uVar1 & 0xffff0000;
    case 3:
      *result = 0;
      *result = result_sign;
      return result_sign & 0xffff0000;
    case 4:
      *result = 0x7f800000;
      *result = result_sign | 0x7f800000;
      return result_sign & 0xffff0000 | 0x7f800000;
    case 5:
      *result = 0x7f800001;
      return CONCAT22((short)(uVar1 >> 0x10),1);
    }
  }
  return CONCAT22((short)(uVar1 >> 0x10),uVar2);
#undef b_exp
#undef a_exp
#undef b_mant
#undef b_mant_1
#undef a_mant
#undef a_mant_1
#undef a_sign
#undef b_sign
#undef action
#undef result_sign
#undef b_class
#undef a_class
}



