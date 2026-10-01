#include "decls.h"
#include "imports.h"

// entry: 00427f20
// name : convert_float_to_double
// size : 249
// sig  : uint convert_float_to_double(uint * src, uint * dst)


uint __cdecl convert_float_to_double(uint *src,uint *dst)

{
  unsigned char _frec_1a[26];
#define exponent (*(ushort *)(_frec_1a + 0))
#define sign (*(uint *)(_frec_1a + 2))
#define fp_class (*(uint *)(_frec_1a + 6))
#define mant (*(uint *)(_frec_1a + 10))
#define dmant (*(uint *)(_frec_1a + 14))
#define dmant_1 (*(int *)(_frec_1a + 18))
#define dmant_2 (*(undefined4 *)(_frec_1a + 22))
  uint uVar1;
  
  unpack_float(src,&sign,&exponent,&mant,(int *)&fp_class);
  if (fp_class == 0) {
    dmant_2 = 0;
    exponent = exponent + 0x380;
    dmant_1 = mant << 0x1d;
    dmant = mant >> 3;
    uVar1 = pack_round_double(sign,exponent,&dmant,dst);
    return uVar1;
  }
  if (fp_class == 1) {
    dst[1] = 0;
    *dst = 0;
    *dst = sign;
    return sign & 0xffff0000;
  }
  if (fp_class == 2) {
    *dst = 0x7ff00000;
    dst[1] = 0;
    *dst = sign | 0x7ff00000;
    return sign & 0xffff0000 | 0x7ff00000;
  }
  if (fp_class != 3) {
    return fp_class & 0xffff0000;
  }
  *dst = 0x7ff00000;
  dst[1] = 1;
  return 1;
#undef exponent
#undef sign
#undef fp_class
#undef mant
#undef dmant
#undef dmant_1
#undef dmant_2
}



