#include "decls.h"
#include "imports.h"

// entry: 004377c0
// name : compare_float_constants
// size : 135
// sig  : short compare_float_constants(uint * a, uint * b)


short __cdecl compare_float_constants(uint *a,uint *b)

{
  unsigned char _frec_8[8];
#define b_bits (*(uint *)(_frec_8 + 0))
#define a_bits (*(uint *)(_frec_8 + 4))
  int cmp;
  
  a_bits = *a;
  b_bits = *b;
  if ((((a_bits & 0x7f800000) != 0x7f800000) || ((a_bits & 0x7fffff) == 0)) &&
     (((b_bits & 0x7f800000) != 0x7f800000 || ((b_bits & 0x7fffff) == 0)))) {
    if ((a_bits & 0x7fffffff) == 0) {
      a_bits = 0;
    }
    if ((b_bits & 0x7fffffff) == 0) {
      b_bits = 0;
    }
    cmp = compare_multiword(&a_bits,&b_bits,1);
    return (short)cmp + 1;
  }
  return -1;
#undef b_bits
#undef a_bits
}



