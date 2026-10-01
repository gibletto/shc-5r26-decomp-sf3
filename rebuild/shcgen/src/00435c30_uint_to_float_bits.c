#include "decls.h"
#include "imports.h"

// entry: 00435c30
// name : uint_to_float_bits
// size : 160
// sig  : short uint_to_float_bits(int * src, uint * dst)


short __cdecl uint_to_float_bits(int *src,uint *dst)

{
  unsigned char _frec_8[8];
#define mant_hi (*(uint *)(_frec_8 + 0))
#define mant_lo (*(uint *)(_frec_8 + 4))
  short exponent;
  short inexact;
  uint top;
  int value;
  
  value = *src;
  inexact = 0;
  if (value == 0) {
    *dst = 0;
    return 0;
  }
  exponent = 0x9e;
  mant_hi = value >> 8 & 0xffffff;
  mant_lo = value << 0x18;
  top = value >> 8;
  while ((top & 0x800000) == 0) {
    mant_hi = mant_hi << 1;
    if ((mant_lo & 0x80000000) != 0) {
      mant_hi = mant_hi | 1;
    }
    mant_lo = mant_lo << 1;
    exponent = exponent + -1;
    top = mant_hi;
  }
  if (mant_lo != 0) {
    inexact = 5;
  }
  pack_round_float(0,exponent,&mant_hi,dst);
  return inexact;
#undef mant_hi
#undef mant_lo
}



