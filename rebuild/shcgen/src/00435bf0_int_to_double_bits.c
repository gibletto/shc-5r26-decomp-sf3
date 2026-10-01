#include "decls.h"
#include "imports.h"

// entry: 00435bf0
// name : int_to_double_bits
// size : 59
// sig  : int int_to_double_bits(uint * src, uint * dst)


int __cdecl int_to_double_bits(uint *src,uint *dst)

{
  unsigned char _frec_4[4];
#define magnitude (*(uint *)(_frec_4 + 0))
  int status;
  uint sign;
  
  magnitude = *src;
  sign = magnitude & 0x80000000;
  if (sign != 0) {
    magnitude = -magnitude;
  }
  status = uint_to_double_bits((int *)&magnitude,dst);
  *dst = *dst | sign;
  return status;
#undef magnitude
}



