#include "decls.h"
#include "imports.h"

// entry: 00426f40
// name : fold_add_ldouble
// size : 897
// sig  : uint fold_add_ldouble(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_add_ldouble(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_40[64];
#define b_exp (*(ushort *)(_frec_40 + 0))
#define a_exp (*(ushort *)(_frec_40 + 2))
#define a_mant (*(uint *)(_frec_40 + 4))
#define a_mant_1 (*(uint *)(_frec_40 + 8))
#define a_mant_2 (*(uint *)(_frec_40 + 12))
#define a_mant_3 (*(uint *)(_frec_40 + 16))
#define a_sign (*(uint *)(_frec_40 + 20))
#define b_mant (*(uint *)(_frec_40 + 24))
#define b_mant_1 (*(uint *)(_frec_40 + 28))
#define b_mant_2 (*(uint *)(_frec_40 + 32))
#define b_mant_3 (*(uint *)(_frec_40 + 36))
#define local_18 (*(int *)(_frec_40 + 40))
#define b_sign (*(uint *)(_frec_40 + 44))
#define action (*(int *)(_frec_40 + 48))
#define result_sign (*(uint *)(_frec_40 + 52))
#define b_class (*(int *)(_frec_40 + 56))
#define a_class (*(int *)(_frec_40 + 60))
  uint uVar1;
  uint uVar2;
  int iVar3;
  int res_exp;
  undefined2 uVar4;
  uint tmp_sign;
  
  uVar4 = 0;
  unpack_double(lhs,&a_sign,&a_exp,&a_mant,&a_class);
  a_mant_3 = 0;
  unpack_double(rhs,&b_sign,&b_exp,&b_mant,&b_class);
  b_mant_3 = 0;
  iVar3 = (int)(short)a_exp;
  local_18 = (int)(short)b_exp;
  classify_add_operands(a_sign,a_class,b_sign,b_class,&action,&result_sign);
  tmp_sign = a_sign;
  uVar2 = a_mant_2;
  uVar1 = a_mant_1;
  if (action == 0) {
    res_exp = iVar3;
    if (iVar3 < local_18) {
      a_sign = b_sign;
      b_sign = tmp_sign;
      a_mant_1 = b_mant_1;
      b_mant_1 = uVar1;
      a_mant_2 = b_mant_2;
      b_mant_2 = uVar2;
      res_exp = local_18;
      local_18 = iVar3;
    }
    iVar3 = res_exp - local_18;
    if (iVar3 < 0x42) {
      if (local_18 < res_exp) {
        do {
          if ((b_mant_2 & 1) == 0) {
            b_mant_3 = (int)b_mant_3 >> 1 & 0x7fffffff;
          }
          else {
            b_mant_3 = (int)b_mant_3 >> 1 | 0x80000000;
          }
          if ((b_mant_1 & 1) == 0) {
            b_mant_2 = (int)b_mant_2 >> 1 & 0x7fffffff;
          }
          else {
            b_mant_2 = (int)b_mant_2 >> 1 | 0x80000000;
          }
          b_mant_1 = (int)b_mant_1 >> 1 & 0x7fffffff;
          if ((b_mant_3 & 0x10000000) != 0) {
            b_mant_3 = b_mant_3 & 0xefffffff | 0x20000000;
          }
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
    else {
      b_mant_3 = 0x20000000;
      b_mant_2 = 0;
      b_mant_1 = 0;
    }
    if (b_sign == a_sign) {
      add_multiword(&a_mant,&b_mant,4);
      if ((a_mant & 1) != 0) {
        if ((a_mant_2 & 1) == 0) {
          a_mant_3 = (int)a_mant_3 >> 1 & 0x7fffffff;
        }
        else {
          a_mant_3 = (int)a_mant_3 >> 1 | 0x80000000;
        }
        if ((a_mant_1 & 1) == 0) {
          a_mant_2 = (int)a_mant_2 >> 1 & 0x7fffffff;
        }
        else {
          a_mant_2 = (int)a_mant_2 >> 1 | 0x80000000;
        }
        a_mant_1 = (int)a_mant_1 >> 1 | 0x80000000;
        a_mant = (int)a_mant >> 1;
        if ((a_mant_3 & 0x10000000) != 0) {
          a_mant_3 = a_mant_3 & 0xefffffff | 0x20000000;
        }
        res_exp = res_exp + 1;
      }
    }
    else {
      sub_multiword(&a_mant,&b_mant,4);
      if ((int)a_mant < 0) {
        a_sign = b_sign;
        negate_multiword(&a_mant,4);
      }
    }
    if (((a_mant_1 != 0) || (a_mant_2 != 0)) || (a_mant_3 != 0)) {
      while ((a_mant_1 & 0x80000000) == 0) {
        a_mant_1 = a_mant_1 << 1;
        if ((a_mant_2 & 0x80000000) != 0) {
          a_mant_1 = a_mant_1 | 1;
        }
        a_mant_2 = a_mant_2 << 1;
        if ((a_mant_3 & 0x80000000) != 0) {
          a_mant_2 = a_mant_2 | 1;
        }
        a_mant_3 = a_mant_3 << 1;
        res_exp = res_exp + -1;
      }
    }
    if (0x7ffe < res_exp) {
      *result = 0x7fff0000;
      result[2] = 0;
      result[1] = 0;
      *result = a_sign | 0x7fff0000;
      return CONCAT22((short)((a_sign | 0x7fff0000) >> 0x10),2);
    }
    a_exp = (ushort)res_exp;
    action = pack_round_double(a_sign,a_exp,&a_mant,result);
    uVar4 = (undefined2)action;
  }
  else {
    action = action + 2;
    switch(action) {
    case 0:
      *result = *rhs;
      result[1] = rhs[1];
      uVar1 = rhs[2];
      result[2] = uVar1;
      return uVar1 & 0xffff0000;
    case 1:
      *result = *lhs;
      result[1] = lhs[1];
      uVar1 = lhs[2];
      result[2] = uVar1;
      return uVar1 & 0xffff0000;
    case 3:
      result[2] = 0;
      result[1] = 0;
      *result = 0;
      *result = result_sign;
      return 0;
    case 4:
      *result = 0x7fff0000;
      result[2] = 0;
      result[1] = 0;
      *result = result_sign | 0x7fff0000;
      return result_sign & 0xffff0000 | 0x7fff0000;
    case 5:
      *result = 0x7fff0000;
      result[2] = 1;
      result[1] = 0x80000000;
      return CONCAT22((short)((uint)action >> 0x10),1);
    }
  }
  return CONCAT22((short)((uint)action >> 0x10),uVar4);
#undef b_exp
#undef a_exp
#undef a_mant
#undef a_mant_1
#undef a_mant_2
#undef a_mant_3
#undef a_sign
#undef b_mant
#undef b_mant_1
#undef b_mant_2
#undef b_mant_3
#undef local_18
#undef b_sign
#undef action
#undef result_sign
#undef b_class
#undef a_class
}



