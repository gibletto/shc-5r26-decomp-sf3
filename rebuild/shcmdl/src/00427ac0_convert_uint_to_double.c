#include "decls.h"
#include "imports.h"

// entry: 00427ac0
// name : convert_uint_to_double
// size : 88
// sig  : void convert_uint_to_double(int * src, uint * dst)


int __cdecl convert_uint_to_double(int *src,uint *dst)

{
  unsigned char _frec_c[12];
#define mant (*(uint *)(_frec_c + 0))
#define mant_1 (*(int *)(_frec_c + 4))
#define mant_2 (*(undefined4 *)(_frec_c + 8))
  
  mant_1 = *src;
  if (mant_1 == 0) {
    *dst = 0;
    dst[1] = 0;
    return;
  }
  mant_2 = 0;
  mant = mant_1 >> 0xb & 0x1fffff;
  mant_1 = mant_1 << 0x15;
  pack_round_double(0,0x41e,&mant,dst);
  return;
#undef mant
#undef mant_1
#undef mant_2
}



