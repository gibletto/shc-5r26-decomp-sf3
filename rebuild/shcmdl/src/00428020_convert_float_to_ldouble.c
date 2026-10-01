#include "decls.h"
#include "imports.h"

// entry: 00428020
// name : convert_float_to_ldouble
// size : 244
// sig  : uint convert_float_to_ldouble(uint * src, uint * dst)


uint __cdecl convert_float_to_ldouble(uint *src,uint *dst)

{
  unsigned char _frec_1e[30];
#define exponent (*(ushort *)(_frec_1e + 0))
#define sign (*(uint *)(_frec_1e + 2))
#define fp_class (*(uint *)(_frec_1e + 6))
#define local_14 (*(uint (*)[3])(_frec_1e + 10))
#define local_8 (*(undefined4 *)(_frec_1e + 22))
#define local_4 (*(undefined4 *)(_frec_1e + 26))
  uint uVar1;
  
  unpack_float(src,&sign,&exponent,local_14,(int *)&fp_class);
  if (fp_class == 0) {
    exponent = exponent + 0x3f80;
    local_14[1] = 0;
    local_8 = 0;
    local_4 = 0;
    local_14[2] = local_14[0] << 8;
    uVar1 = pack_round_double(sign,exponent,local_14 + 1,dst);
    return uVar1;
  }
  if (fp_class == 1) {
    *dst = 0;
    dst[1] = 0;
    dst[2] = 0;
    *dst = sign;
    return 0;
  }
  if (fp_class == 2) {
    *dst = 0x7fff0000;
    dst[1] = 0;
    dst[2] = 0;
    *dst = sign | 0x7fff0000;
    return sign & 0xffff0000 | 0x7fff0000;
  }
  if (fp_class != 3) {
    return fp_class & 0xffff0000;
  }
  *dst = 0x7fff0000;
  dst[1] = 0x80000000;
  dst[2] = 1;
  return 1;
#undef exponent
#undef sign
#undef fp_class
#undef local_14
#undef local_8
#undef local_4
}



