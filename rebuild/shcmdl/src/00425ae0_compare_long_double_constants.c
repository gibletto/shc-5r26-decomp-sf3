#include "decls.h"
#include "imports.h"

// entry: 00425ae0
// name : compare_long_double_constants
// size : 325
// sig  : ushort compare_long_double_constants(uint * a, uint * b)


ushort __cdecl compare_long_double_constants(uint *a,uint *b)

{
  unsigned char _frec_4c[76];
#define a_exp (*(ushort *)(_frec_4c + 0))
#define b_exp (*(ushort *)(_frec_4c + 2))
#define a_class (*(int *)(_frec_4c + 4))
#define b_class (*(int *)(_frec_4c + 8))
#define a_sign (*(uint *)(_frec_4c + 12))
#define b_sign (*(uint *)(_frec_4c + 16))
#define a_mant (*(uint (*)[3])(_frec_4c + 20))
#define local_2c (*(undefined4 *)(_frec_4c + 32))
#define b_mant (*(uint (*)[3])(_frec_4c + 36))
#define local_1c (*(undefined4 *)(_frec_4c + 48))
#define b_packed (*(uint (*)[3])(_frec_4c + 52))
#define a_packed (*(uint (*)[3])(_frec_4c + 64))
  int cmp;
  
  unpack_double(a,&a_sign,&a_exp,a_mant,&a_class);
  local_2c = 0;
  unpack_double(b,&b_sign,&b_exp,b_mant,&b_class);
  local_1c = 0;
  if ((a_class == 3) || (b_class == 3)) {
    return 0xffff;
  }
  if ((a_class == 1) && (b_class == 1)) {
    return 1;
  }
  if (a_class != 2) {
    if (b_class != 2) {
      pack_round_double(a_sign,a_exp,a_mant,a_packed);
      pack_round_double(b_sign,b_exp,b_mant,b_packed);
      cmp = compare_multiword(a_packed,b_packed,3);
      return (short)cmp + 1;
    }
    if (a_class != 2) goto LAB_00425c00;
  }
  if (b_class == 2) {
    if (b_sign != a_sign) {
      return -(ushort)(a_sign == 0) & 2;
    }
    return 1;
  }
  if ((a_class == 2) && (a_sign == 0)) {
    return 2;
  }
LAB_00425c00:
  if ((b_class == 2) && ((int)b_sign < 0)) {
    return 2;
  }
  return 0;
#undef a_exp
#undef b_exp
#undef a_class
#undef b_class
#undef a_sign
#undef b_sign
#undef a_mant
#undef local_2c
#undef b_mant
#undef local_1c
#undef b_packed
#undef a_packed
}



