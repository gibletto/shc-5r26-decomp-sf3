#include "decls.h"
#include "imports.h"

// entry: 004279e0
// name : convert_int_to_ldouble
// size : 59
// sig  : void convert_int_to_ldouble(uint * src, uint * dst)


int __cdecl convert_int_to_ldouble(uint *src,uint *dst)

{
  unsigned char _frec_4[4];
#define magnitude (*(uint *)(_frec_4 + 0))
  uint sign;
  
  magnitude = *src;
  sign = magnitude & 0x80000000;
  if (sign != 0) {
    magnitude = -magnitude;
  }
  convert_uint_to_ldouble((int *)&magnitude,dst);
  *dst = *dst | sign;
  return;
#undef magnitude
}



