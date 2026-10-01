#include "decls.h"
#include "imports.h"

// entry: 00436080
// name : convert_double_to_float
// size : 220
// sig  : uint convert_double_to_float(uint * src, uint * dst)


uint __cdecl convert_double_to_float(uint *src,uint *dst)

{
  unsigned char _frec_12[18];
#define exponent (*(ushort *)(_frec_12 + 0))
#define sign (*(uint *)(_frec_12 + 2))
#define mant (*(uint *)(_frec_12 + 6))
#define mant_1 (*(uint *)(_frec_12 + 10))
#define fp_class (*(uint *)(_frec_12 + 14))
  uint uVar1;
  
  unpack_double(src,&sign,&exponent,&mant,(int *)&fp_class);
  if (fp_class == 0) {
    exponent = exponent - 0x380;
    uVar1 = mant_1 >> 0x1d;
    mant_1 = mant_1 << 3;
    mant = mant << 3 | uVar1;
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
#undef fp_class
}



