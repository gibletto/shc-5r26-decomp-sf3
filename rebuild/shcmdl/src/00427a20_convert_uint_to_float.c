#include "decls.h"
#include "imports.h"

// entry: 00427a20
// name : convert_uint_to_float
// size : 160
// sig  : short convert_uint_to_float(int * src, uint * dst)


short __cdecl convert_uint_to_float(int *src,uint *dst)

{
  unsigned char _frec_8[8];
#define mant (*(uint *)(_frec_8 + 0))
#define mant_1 (*(uint *)(_frec_8 + 4))
  short exponent;
  short status;
  uint top;
  int value;
  
  value = *src;
  status = 0;
  if (value == 0) {
    *dst = 0;
    return 0;
  }
  exponent = 0x9e;
  mant = value >> 8 & 0xffffff;
  mant_1 = value << 0x18;
  top = value >> 8;
  while ((top & 0x800000) == 0) {
    mant = mant << 1;
    if ((mant_1 & 0x80000000) != 0) {
      mant = mant | 1;
    }
    mant_1 = mant_1 << 1;
    exponent = exponent + -1;
    top = mant;
  }
  if (mant_1 != 0) {
    status = 5;
  }
  pack_round_float(0,exponent,&mant,dst);
  return status;
#undef mant
#undef mant_1
}



