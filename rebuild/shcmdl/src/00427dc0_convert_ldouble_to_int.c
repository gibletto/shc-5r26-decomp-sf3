#include "decls.h"
#include "imports.h"

// entry: 00427dc0
// name : convert_ldouble_to_int
// size : 317
// sig  : uint convert_ldouble_to_int(uint * src, uint * dst)


uint __cdecl convert_ldouble_to_int(uint *src,uint *dst)

{
  unsigned char _frec_16[22];
#define exponent (*(ushort *)(_frec_16 + 0))
#define mant (*(uint *)(_frec_16 + 2))
#define mant_1 (*(uint *)(_frec_16 + 6))
#define mant_2 (*(uint *)(_frec_16 + 10))
#define fp_class (*(int *)(_frec_16 + 14))
#define sign (*(uint *)(_frec_16 + 18))
  short shift;
  uint uVar1;
  ushort uVar2;
  
  uVar1 = unpack_double(src,&sign,&exponent,&mant,&fp_class);
  uVar2 = (ushort)(uVar1 >> 0x10);
  if (fp_class == 0) {
    if (((short)exponent < 0x405e) && (0x3ffe < (short)exponent)) {
      shift = exponent + 0xbfc2;
      if (shift < 1) {
        if ((shift < 0) && (shift = -shift, 0 < shift)) {
          do {
            if ((mant_1 & 1) == 0) {
              mant_2 = (int)mant_2 >> 1 & 0x7fffffff;
            }
            else {
              mant_2 = (int)mant_2 >> 1 | 0x80000000;
            }
            mant_1 = (int)mant_1 >> 1 & 0x7fffffff;
            shift = shift + -1;
          } while (shift != 0);
        }
      }
      else {
        do {
          mant_2 = mant_2 << 1;
          shift = shift + -1;
        } while (shift != 0);
      }
      if ((int)sign < 0) {
        *dst = -mant_2;
        return -mant_2 & 0xffff0000;
      }
      *dst = mant_2;
      return mant_2 & 0xffff0000;
    }
    *dst = 0;
  }
  else {
    *dst = 0;
    if ((fp_class == 2) || (fp_class == 3)) {
      return CONCAT22(uVar2,1);
    }
  }
  return (uint)uVar2 << 0x10;
#undef exponent
#undef mant
#undef mant_1
#undef mant_2
#undef fp_class
#undef sign
}



