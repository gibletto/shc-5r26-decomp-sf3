#include "decls.h"
#include "imports.h"

// entry: 00427c60
// name : convert_double_to_int
// size : 309
// sig  : uint convert_double_to_int(uint * src, uint * dst)


uint __cdecl convert_double_to_int(uint *src,uint *dst)

{
  unsigned char _frec_12[18];
#define exponent (*(ushort *)(_frec_12 + 0))
#define mant (*(uint *)(_frec_12 + 2))
#define mant_1 (*(uint *)(_frec_12 + 6))
#define fp_class (*(int *)(_frec_12 + 10))
#define sign (*(uint *)(_frec_12 + 14))
  short shift;
  uint uVar1;
  ushort uVar2;
  
  uVar1 = unpack_double(src,&sign,&exponent,&mant,&fp_class);
  uVar2 = (ushort)(uVar1 >> 0x10);
  if (fp_class == 0) {
    if ((0x3fe < (short)exponent) && ((short)exponent < 0x453)) {
      shift = exponent - 0x433;
      if (shift < 1) {
        if ((shift < 0) && (shift = -shift, 0 < shift)) {
          do {
            if ((mant & 1) == 0) {
              mant_1 = (int)mant_1 >> 1 & 0x7fffffff;
            }
            else {
              mant_1 = (int)mant_1 >> 1 | 0x80000000;
            }
            mant = (int)mant >> 1;
            shift = shift + -1;
          } while (shift != 0);
        }
      }
      else {
        do {
          mant_1 = mant_1 << 1;
          shift = shift + -1;
        } while (shift != 0);
      }
      if ((int)sign < 0) {
        *dst = -mant_1;
        return -mant_1 & 0xffff0000;
      }
      *dst = mant_1;
      return mant_1 & 0xffff0000;
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
#undef fp_class
#undef sign
}



