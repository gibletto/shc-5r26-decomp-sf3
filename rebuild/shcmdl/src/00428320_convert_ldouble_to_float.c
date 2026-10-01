#include "decls.h"
#include "imports.h"

// entry: 00428320
// name : convert_ldouble_to_float
// size : 261
// sig  : uint convert_ldouble_to_float(uint * src, uint * dst)


uint __cdecl convert_ldouble_to_float(uint *src,uint *dst)

{
  unsigned char _frec_16[22];
#define exponent (*(ushort *)(_frec_16 + 0))
#define sign (*(uint *)(_frec_16 + 2))
#define mant (*(uint *)(_frec_16 + 6))
#define mant_1 (*(uint *)(_frec_16 + 10))
#define mant_2 (*(uint *)(_frec_16 + 14))
#define fp_class (*(uint *)(_frec_16 + 18))
  short bits;
  uint uVar1;
  
  unpack_double(src,&sign,&exponent,&mant,(int *)&fp_class);
  if (fp_class == 0) {
    bits = 0x18;
    exponent = exponent + 0xc080;
    do {
      mant = mant << 1;
      if ((mant_1 & 0x80000000) != 0) {
        mant = mant | 1;
      }
      mant_1 = mant_1 << 1;
      if ((mant_2 & 0x80000000) != 0) {
        mant_1 = mant_1 | 1;
      }
      mant_2 = mant_2 << 1;
      bits = bits + -1;
    } while (bits != 0);
    if (mant_2 != 0) {
      mant_1 = mant_1 | 1;
    }
    uVar1 = pack_round_float(sign,exponent,&mant,dst);
    return uVar1;
  }
  if (fp_class == 1) {
    *dst = 0;
    *dst = sign;
    return sign & 0xffff0000;
  }
  if (fp_class == 2) {
    *dst = 0x7f800000;
    *dst = sign | 0x7f800000;
    return sign & 0xffff0000 | 0x7f800000;
  }
  if (fp_class != 3) {
    return fp_class & 0xffff0000;
  }
  *dst = 0x7f800001;
  return 1;
#undef exponent
#undef sign
#undef mant
#undef mant_1
#undef mant_2
#undef fp_class
}



