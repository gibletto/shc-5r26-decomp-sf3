#include "decls.h"
#include "imports.h"

// entry: 00427660
// name : fold_div_ldouble
// size : 689
// sig  : uint fold_div_ldouble(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_div_ldouble(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_48[72];
#define local_48 (*(undefined4 *)(_frec_48 + 0))
#define local_44 (*(uint (*)[5])(_frec_48 + 4))
#define rem (*(uint *)(_frec_48 + 24))
#define rem_1 (*(uint *)(_frec_48 + 28))
#define rem_2 (*(uint *)(_frec_48 + 32))
#define action (*(int *)(_frec_48 + 36))
#define b_class (*(int *)(_frec_48 + 40))
#define b_sign (*(uint *)(_frec_48 + 44))
#define a_class (*(int *)(_frec_48 + 48))
#define a_sign (*(uint *)(_frec_48 + 52))
#define b_exp (*(int *)(_frec_48 + 56))
#define b_mant (*(uint (*)[3])(_frec_48 + 60))
  short sVar1;
  undefined2 extraout_var = 0;
  int iVar2;
  uint uVar3;
  short w;
  uint *word_ptr;
  
  unpack_double(lhs,&a_sign,(ushort *)((int)&local_48 + 2),&rem,&a_class);
  unpack_double(rhs,&b_sign,(ushort *)&local_48,b_mant,&b_class);
  b_exp = (int)(short)(ushort)local_48;
  sVar1 = classify_div_operands(a_sign,a_class,b_sign,b_class,&action,local_44 + 4);
  uVar3 = CONCAT22(extraout_var,sVar1);
  if (action == 0) {
    sVar1 = 0x42;
    local_44[3] = 0;
    local_44[2] = 0;
    local_44[1] = 0;
    local_44[0] = 0;
    do {
      local_44[0] = local_44[0] << 1;
      if ((local_44[1] & 0x80000000) != 0) {
        local_44[0] = local_44[0] | 1;
      }
      local_44[1] = local_44[1] << 1;
      if ((local_44[2] & 0x80000000) != 0) {
        local_44[1] = local_44[1] | 1;
      }
      local_44[2] = local_44[2] << 1;
      iVar2 = compare_multiword(&rem,b_mant,3);
      if (-1 < (short)iVar2) {
        sub_multiword(&rem,b_mant,3);
        local_44[2] = local_44[2] + 1;
      }
      rem = rem << 1;
      if ((rem_1 & 0x80000000) != 0) {
        rem = rem | 1;
      }
      rem_1 = rem_1 << 1;
      if ((rem_2 & 0x80000000) != 0) {
        rem_1 = rem_1 | 1;
      }
      rem_2 = rem_2 << 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != 0);
    sVar1 = 2;
    do {
      w = 3;
      do {
        word_ptr = local_44 + w;
        uVar3 = (int)*word_ptr >> 1;
        *word_ptr = uVar3;
        if (((&local_48)[w] & 1) == 0) {
          uVar3 = uVar3 & 0x7fffffff;
        }
        else {
          uVar3 = uVar3 | 0x80000000;
        }
        w = w + -1;
        *word_ptr = uVar3;
      } while (w != 0);
      local_44[0] = (int)local_44[0] >> 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != 0);
    if (((rem_2 != 0) || (rem_1 != 0)) || (rem != 0)) {
      local_44[3] = local_44[3] | 0x20000000;
    }
    iVar2 = ((*(unsigned short *)((char *)&local_48 + 2)) - b_exp) + 0x3fff;
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
        iVar2 = iVar2 + -1;
      }
    }
    if (iVar2 < 0x7fff) {
      (*(unsigned short *)((char *)&local_48 + 2)) = (short)iVar2;
      uVar3 = pack_round_double(local_44[4],(*(unsigned short *)((char *)&local_48 + 2)),local_44,result);
      return uVar3;
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
    return uVar3;
  }
  if (action == 2) {
    *result = 0x7fff0000;
    result[2] = 0;
    result[1] = 0;
    *result = local_44[4] | 0x7fff0000;
    return uVar3;
  }
  if (action == 3) {
    *result = 0x7fff0000;
    result[2] = 1;
    result[1] = 0x80000000;
    return 1;
  }
  return uVar3;
#undef local_48
#undef local_44
#undef rem
#undef rem_1
#undef rem_2
#undef action
#undef b_class
#undef b_sign
#undef a_class
#undef a_sign
#undef b_exp
#undef b_mant
}



