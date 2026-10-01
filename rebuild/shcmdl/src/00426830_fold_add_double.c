#include "decls.h"
#include "imports.h"

// entry: 00426830
// name : fold_add_double
// size : 729
// sig  : uint fold_add_double(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_add_double(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_34[52];
#define b_exp (*(ushort *)(_frec_34 + 0))
#define a_exp (*(ushort *)(_frec_34 + 2))
#define b_mant (*(uint *)(_frec_34 + 4))
#define b_mant_1 (*(uint *)(_frec_34 + 8))
#define b_mant_2 (*(uint *)(_frec_34 + 12))
#define a_mant (*(uint *)(_frec_34 + 16))
#define a_mant_1 (*(uint *)(_frec_34 + 20))
#define a_mant_2 (*(uint *)(_frec_34 + 24))
#define a_sign (*(uint *)(_frec_34 + 28))
#define b_sign (*(uint *)(_frec_34 + 32))
#define action (*(int *)(_frec_34 + 36))
#define result_sign (*(uint *)(_frec_34 + 40))
#define b_class (*(int *)(_frec_34 + 44))
#define a_class (*(int *)(_frec_34 + 48))
  undefined2 uVar1;
  ushort tmp_exp;
  uint tmp_mant;
  uint tmp_mant_1;
  uint tmp_sign;
  
  uVar1 = 0;
  unpack_double(lhs,&a_sign,&a_exp,&a_mant,&a_class);
  a_mant_2 = 0;
  unpack_double(rhs,&b_sign,&b_exp,&b_mant,&b_class);
  b_mant_2 = 0;
  classify_add_operands(a_sign,a_class,b_sign,b_class,&action,&result_sign);
  tmp_sign = a_sign;
  tmp_mant_1 = a_mant_1;
  tmp_mant = a_mant;
  tmp_exp = a_exp;
  if (action == 0) {
    if ((short)a_exp < (short)b_exp) {
      a_sign = b_sign;
      b_sign = tmp_sign;
      a_exp = b_exp;
      a_mant = b_mant;
      b_exp = tmp_exp;
      b_mant = tmp_mant;
      a_mant_1 = b_mant_1;
      b_mant_1 = tmp_mant_1;
    }
    if ((int)(short)a_exp - (int)(short)b_exp < 0x37) {
      for (; (short)b_exp < (short)a_exp; b_exp = b_exp + 1) {
        if ((b_mant_1 & 1) == 0) {
          b_mant_2 = (int)b_mant_2 >> 1 & 0x7fffffff;
        }
        else {
          b_mant_2 = (int)b_mant_2 >> 1 | 0x80000000;
        }
        if ((b_mant & 1) == 0) {
          b_mant_1 = (int)b_mant_1 >> 1 & 0x7fffffff;
        }
        else {
          b_mant_1 = (int)b_mant_1 >> 1 | 0x80000000;
        }
        b_mant = (int)b_mant >> 1;
        if ((b_mant_2 & 0x10000000) != 0) {
          b_mant_2 = b_mant_2 & 0xefffffff | 0x20000000;
        }
      }
    }
    else {
      b_mant_2 = 0x20000000;
      b_exp = a_exp;
      b_mant_1 = 0;
      b_mant = 0;
    }
    if (b_sign == a_sign) {
      add_multiword(&a_mant,&b_mant,3);
      if ((a_mant & 0x200000) != 0) {
        if ((a_mant_1 & 1) == 0) {
          a_mant_2 = (int)a_mant_2 >> 1 & 0x7fffffff;
        }
        else {
          a_mant_2 = (int)a_mant_2 >> 1 | 0x80000000;
        }
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
      sub_multiword(&a_mant,&b_mant,3);
      if ((int)a_mant < 0) {
        a_sign = b_sign;
        negate_multiword(&a_mant,3);
      }
    }
    action = pack_round_double(a_sign,a_exp,&a_mant,result);
    uVar1 = (undefined2)action;
  }
  else {
    action = action + 2;
    switch(action) {
    case 0:
      tmp_mant = *rhs;
      *result = tmp_mant;
      result[1] = rhs[1];
      return tmp_mant & 0xffff0000;
    case 1:
      tmp_mant = *lhs;
      *result = tmp_mant;
      result[1] = lhs[1];
      return tmp_mant & 0xffff0000;
    case 3:
      *result = 0;
      result[1] = 0;
      *result = result_sign;
      return result_sign & 0xffff0000;
    case 4:
      result[1] = 0;
      *result = 0x7ff00000;
      *result = result_sign | 0x7ff00000;
      return result_sign & 0xffff0000 | 0x7ff00000;
    case 5:
      *result = 0x7ff00000;
      result[1] = 1;
      return CONCAT22((short)((uint)action >> 0x10),1);
    }
  }
  return CONCAT22((short)((uint)action >> 0x10),uVar1);
#undef b_exp
#undef a_exp
#undef b_mant
#undef b_mant_1
#undef b_mant_2
#undef a_mant
#undef a_mant_1
#undef a_mant_2
#undef a_sign
#undef b_sign
#undef action
#undef result_sign
#undef b_class
#undef a_class
}



