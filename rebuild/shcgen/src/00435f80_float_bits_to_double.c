#include "decls.h"
#include "imports.h"

// entry: 00435f80
// name : float_bits_to_double
// size : 249
// sig  : uint float_bits_to_double(uint * src, uint * dst)


uint __cdecl float_bits_to_double(uint *src,uint *dst)

{
  unsigned char _frec_1a[26];
#define exponent (*(ushort *)(_frec_1a + 0))
#define sign (*(uint *)(_frec_1a + 2))
#define fp_class (*(uint *)(_frec_1a + 6))
#define mantissa (*(uint *)(_frec_1a + 10))
#define dmant_hi (*(uint *)(_frec_1a + 14))
#define dmant_lo (*(int *)(_frec_1a + 18))
#define local_4 (*(undefined4 *)(_frec_1a + 22))
  uint status;
  
  unpack_float(src,&sign,&exponent,&mantissa,(int *)&fp_class);
  if (fp_class == 0) {
    local_4 = 0;
    exponent = exponent + 0x380;
    dmant_lo = mantissa << 0x1d;
    dmant_hi = mantissa >> 3;
    status = pack_round_double(sign,exponent,&dmant_hi,dst);
    return status;
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
#undef mantissa
#undef dmant_hi
#undef dmant_lo
#undef local_4
}



