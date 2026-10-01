#include "decls.h"
#include "imports.h"

// entry: 00428200
// name : convert_double_to_ldouble
// size : 283
// sig  : uint convert_double_to_ldouble(uint * src, uint * dst)


uint __cdecl convert_double_to_ldouble(uint *src,uint *dst)

{
  unsigned char _frec_22[34];
#define exponent (*(ushort *)(_frec_22 + 0))
#define sign (*(uint *)(_frec_22 + 2))
#define local_1c (*(uint (*)[3])(_frec_22 + 6))
#define low_bits (*(uint *)(_frec_22 + 18))
#define local_c (*(undefined4 *)(_frec_22 + 22))
#define mant (*(uint *)(_frec_22 + 26))
#define mant_1 (*(uint *)(_frec_22 + 30))
  short bits;
  uint uVar1;
  
  unpack_double(src,&sign,&exponent,&mant,(int *)local_1c);
  if (local_1c[0] == 0) {
    local_1c[1] = 0;
    local_1c[2] = mant;
    low_bits = mant_1;
    bits = 0xb;
    exponent = exponent + 0x3c00;
    local_c = 0;
    do {
      local_1c[2] = local_1c[2] << 1;
      if ((low_bits & 0x80000000) != 0) {
        local_1c[2] = local_1c[2] | 1;
      }
      low_bits = low_bits << 1;
      bits = bits + -1;
    } while (bits != 0);
    uVar1 = pack_round_double(sign,exponent,local_1c + 1,dst);
    return uVar1;
  }
  if (local_1c[0] == 1) {
    *dst = 0;
    dst[1] = 0;
    dst[2] = 0;
    *dst = sign;
    return 0;
  }
  if (local_1c[0] == 2) {
    *dst = 0x7fff0000;
    dst[1] = 0;
    dst[2] = 0;
    *dst = sign | 0x7fff0000;
    return sign & 0xffff0000 | 0x7fff0000;
  }
  if (local_1c[0] != 3) {
    return local_1c[0] & 0xffff0000;
  }
  *dst = 0x7fff0000;
  dst[1] = 0x80000000;
  dst[2] = 1;
  return 1;
#undef exponent
#undef sign
#undef local_1c
#undef low_bits
#undef local_c
#undef mant
#undef mant_1
}



