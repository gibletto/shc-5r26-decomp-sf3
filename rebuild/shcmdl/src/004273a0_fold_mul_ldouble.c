#include "decls.h"
#include "imports.h"

// entry: 004273a0
// name : fold_mul_ldouble
// size : 649
// sig  : uint fold_mul_ldouble(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_mul_ldouble(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_48[72];
#define local_48 (*(undefined4 *)(_frec_48 + 0))
#define local_44 (*(uint (*)[5])(_frec_48 + 4))
#define action (*(uint *)(_frec_48 + 24))
#define a_mant (*(uint *)(_frec_48 + 28))
#define a_mant_1 (*(uint *)(_frec_48 + 32))
#define a_mant_2 (*(uint *)(_frec_48 + 36))
#define b_class (*(int *)(_frec_48 + 40))
#define b_sign (*(uint *)(_frec_48 + 44))
#define a_class (*(int *)(_frec_48 + 48))
#define a_sign (*(uint *)(_frec_48 + 52))
#define b_exp (*(int *)(_frec_48 + 56))
#define b_mant (*(uint (*)[3])(_frec_48 + 60))
  uint uVar1;
  short w;
  short bits;
  int res_exp;
  uint *word_ptr;
  
  unpack_double(lhs,&a_sign,(ushort *)((int)&local_48 + 2),&a_mant,&a_class);
  unpack_double(rhs,&b_sign,(ushort *)&local_48,b_mant,&b_class);
  b_exp = (int)(short)(ushort)local_48;
  classify_mul_operands(a_sign,a_class,b_sign,b_class,(int *)&action,local_44 + 4);
  if (action == 0) {
    bits = 0x40;
    local_44[3] = 0;
    local_44[2] = 0;
    local_44[1] = 0;
    local_44[0] = 0;
    do {
      if ((a_mant_2 & 1) != 0) {
        add_multiword(local_44,b_mant,3);
      }
      w = 3;
      do {
        word_ptr = local_44 + w;
        uVar1 = (int)*word_ptr >> 1;
        *word_ptr = uVar1;
        if (((&local_48)[w] & 1) == 0) {
          uVar1 = uVar1 & 0x7fffffff;
        }
        else {
          uVar1 = uVar1 | 0x80000000;
        }
        w = w + -1;
        *word_ptr = uVar1;
      } while (w != 0);
      local_44[0] = (int)local_44[0] >> 1;
      if ((local_44[3] & 0x1fffffff) != 0) {
        local_44[3] = local_44[3] & 0xefffffff | 0x20000000;
      }
      if ((a_mant_1 & 1) == 0) {
        a_mant_2 = (int)a_mant_2 >> 1 & 0x7fffffff;
      }
      else {
        a_mant_2 = (int)a_mant_2 >> 1 | 0x80000000;
      }
      a_mant_1 = (int)a_mant_1 >> 1 & 0x7fffffff;
      bits = bits + -1;
    } while (bits != 0);
    res_exp = b_exp + -0x3ffe + (int)(*(unsigned short *)((char *)&local_48 + 2));
    if (((local_44[1] != 0) || (local_44[2] != 0)) || (local_44[3] != 0)) {
      while ((local_44[1] & 0x80000000) == 0) {
        local_44[1] = local_44[1] << 1;
        if ((local_44[2] & 0x80000000) != 0) {
          local_44[1] = local_44[1] | 1;
        }
        local_44[2] = local_44[2] << 1;
        if ((local_44[3] & 0x80000000) != 0) {
          local_44[2] = local_44[2] | 1;
        }
        local_44[3] = local_44[3] << 1;
        res_exp = res_exp + -1;
      }
    }
    if (res_exp < 0x7fff) {
      (*(unsigned short *)((char *)&local_48 + 2)) = (short)res_exp;
      uVar1 = pack_round_double(local_44[4],(*(unsigned short *)((char *)&local_48 + 2)),local_44,result);
      return uVar1;
    }
    *result = 0x7fff0000;
    result[2] = 0;
    result[1] = 0;
    *result = local_44[4] | 0x7fff0000;
    return CONCAT22((short)((local_44[4] | 0x7fff0000) >> 0x10),2);
  }
  if (action == 1) {
    result[2] = 0;
    result[1] = 0;
    *result = 0;
    *result = local_44[4];
    return 0;
  }
  if (action == 2) {
    *result = 0x7fff0000;
    result[2] = 0;
    result[1] = 0;
    *result = local_44[4] | 0x7fff0000;
    return local_44[4] & 0xffff0000 | 0x7fff0000;
  }
  if (action == 3) {
    *result = 0x7fff0000;
    result[1] = 0x80000000;
    result[2] = 1;
    return 1;
  }
  return action & 0xffff0000;
#undef local_48
#undef local_44
#undef action
#undef a_mant
#undef a_mant_1
#undef a_mant_2
#undef b_class
#undef b_sign
#undef a_class
#undef a_sign
#undef b_exp
#undef b_mant
}



