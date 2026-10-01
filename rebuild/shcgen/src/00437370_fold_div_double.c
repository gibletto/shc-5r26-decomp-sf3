#include "decls.h"
#include "imports.h"

// entry: 00437370
// name : fold_div_double
// size : 494
// sig  : uint fold_div_double(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_div_double(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_38[56];
#define b_exp (*(ushort *)(_frec_38 + 0))
#define a_exp (*(ushort *)(_frec_38 + 2))
#define rem (*(uint *)(_frec_38 + 4))
#define local_30 (*(uint (*)[5])(_frec_38 + 8))
#define action (*(int *)(_frec_38 + 28))
#define b_class (*(int *)(_frec_38 + 32))
#define b_sign (*(uint *)(_frec_38 + 36))
#define a_class (*(int *)(_frec_38 + 40))
#define a_sign (*(uint *)(_frec_38 + 44))
#define b_mant (*(uint (*)[2])(_frec_38 + 48))
  short sVar1;
  undefined2 extraout_var = 0;
  int cmp;
  uint uVar2;
  short w;
  uint *word_ptr;
  
  unpack_double(lhs,&a_sign,&a_exp,&rem,&a_class);
  unpack_double(rhs,&b_sign,&b_exp,b_mant,&b_class);
  sVar1 = classify_div_operands(a_sign,a_class,b_sign,b_class,&action,local_30 + 4);
  uVar2 = CONCAT22(extraout_var,sVar1);
  if (action == 0) {
    sVar1 = 0x37;
    local_30[3] = 0;
    local_30[2] = 0;
    local_30[1] = 0;
    do {
      local_30[1] = local_30[1] << 1;
      if ((local_30[2] & 0x80000000) != 0) {
        local_30[1] = local_30[1] | 1;
      }
      local_30[2] = local_30[2] << 1;
      cmp = compare_multiword(&rem,b_mant,2);
      if (-1 < (short)cmp) {
        sub_multiword(&rem,b_mant,2);
        local_30[2] = local_30[2] + 1;
      }
      rem = rem << 1;
      if ((local_30[0] & 0x80000000) != 0) {
        rem = rem | 1;
      }
      local_30[0] = local_30[0] << 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != 0);
    sVar1 = 2;
    do {
      w = 2;
      do {
        word_ptr = local_30 + w + 1;
        uVar2 = (int)*word_ptr >> 1;
        *word_ptr = uVar2;
        if ((local_30[w] & 1) == 0) {
          uVar2 = uVar2 & 0x7fffffff;
        }
        else {
          uVar2 = uVar2 | 0x80000000;
        }
        w = w + -1;
        *word_ptr = uVar2;
      } while (w != 0);
      local_30[1] = (int)local_30[1] >> 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != 0);
    if ((local_30[0] != 0) || (rem != 0)) {
      local_30[3] = local_30[3] | 0x20000000;
    }
    a_exp = a_exp + (0x3ff - b_exp);
    uVar2 = pack_round_double(local_30[4],a_exp,local_30 + 1,result);
    return uVar2;
  }
  if (action == 1) {
    *result = 0;
    result[1] = 0;
    *result = local_30[4];
    return uVar2;
  }
  if (action == 2) {
    *result = 0x7ff00000;
    *result = local_30[4] | 0x7ff00000;
    result[1] = 0;
    return uVar2;
  }
  if (action != 3) {
    return uVar2;
  }
  *result = 0x7ff00000;
  result[1] = 1;
  return 1;
#undef b_exp
#undef a_exp
#undef rem
#undef local_30
#undef action
#undef b_class
#undef b_sign
#undef a_class
#undef a_sign
#undef b_mant
}



