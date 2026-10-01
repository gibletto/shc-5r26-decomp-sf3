#include "decls.h"
#include "imports.h"

// entry: 00435e20
// name : double_bits_to_int
// size : 309
// sig  : int double_bits_to_int(uint * src, uint * dst)


int __cdecl double_bits_to_int(uint *src,uint *dst)

{
  unsigned char _frec_12[18];
#define exponent (*(ushort *)(_frec_12 + 0))
#define mant_hi (*(uint *)(_frec_12 + 2))
#define mant_lo (*(uint *)(_frec_12 + 6))
#define fp_class (*(int *)(_frec_12 + 10))
#define sign (*(uint *)(_frec_12 + 14))
  short shift;
  uint status;
  ushort status_hi;
  
  status = unpack_double(src,&sign,&exponent,&mant_hi,&fp_class);
  status_hi = (ushort)(status >> 0x10);
  if (fp_class == 0) {
    if ((0x3fe < (short)exponent) && ((short)exponent < 0x453)) {
      shift = exponent - 0x433;
      if (shift < 1) {
        if ((shift < 0) && (shift = -shift, 0 < shift)) {
          do {
            if ((mant_hi & 1) == 0) {
              mant_lo = (int)mant_lo >> 1 & 0x7fffffff;
            }
            else {
              mant_lo = (int)mant_lo >> 1 | 0x80000000;
            }
            mant_hi = (int)mant_hi >> 1;
            shift = shift + -1;
          } while (shift != 0);
        }
      }
      else {
        do {
          mant_lo = mant_lo << 1;
          shift = shift + -1;
        } while (shift != 0);
      }
      if ((int)sign < 0) {
        *dst = -mant_lo;
        return -mant_lo & 0xffff0000;
      }
      *dst = mant_lo;
      return mant_lo & 0xffff0000;
    }
    *dst = 0;
  }
  else {
    *dst = 0;
    if ((fp_class == 2) || (fp_class == 3)) {
      return CONCAT22(status_hi,1);
    }
  }
  return (uint)status_hi << 0x10;
#undef exponent
#undef mant_hi
#undef mant_lo
#undef fp_class
#undef sign
}



