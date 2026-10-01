#include "decls.h"
#include "imports.h"

// entry: 00427b20
// name : convert_uint_to_ldouble
// size : 74
// sig  : void convert_uint_to_ldouble(int * src, uint * dst)


int __cdecl convert_uint_to_ldouble(int *src,uint *dst)

{
  unsigned char _frec_10[16];
#define mant (*(uint *)(_frec_10 + 0))
#define mant_1 (*(int *)(_frec_10 + 4))
#define mant_2 (*(undefined4 *)(_frec_10 + 8))
#define mant_3 (*(undefined4 *)(_frec_10 + 12))
  
  mant_1 = *src;
  if (mant_1 == 0) {
    *dst = 0;
    dst[1] = 0;
    dst[2] = 0;
    return;
  }
  mant = 0;
  mant_2 = 0;
  mant_3 = 0;
  pack_round_double(0,0x401e,&mant,dst);
  return;
#undef mant
#undef mant_1
#undef mant_2
#undef mant_3
}



