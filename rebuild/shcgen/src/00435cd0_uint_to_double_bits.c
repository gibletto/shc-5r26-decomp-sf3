#include "decls.h"
#include "imports.h"

// entry: 00435cd0
// name : uint_to_double_bits
// size : 88
// sig  : int uint_to_double_bits(int * src, uint * dst)


int __cdecl uint_to_double_bits(int *src,uint *dst)

{
  unsigned char _frec_c[12];
#define mant_hi (*(uint *)(_frec_c + 0))
#define local_8 (*(int *)(_frec_c + 4))
#define local_4 (*(undefined4 *)(_frec_c + 8))
  int status;
  
  local_8 = *src;
  if (local_8 == 0) {
    *dst = 0;
    dst[1] = 0;
    return 0;
  }
  local_4 = 0;
  mant_hi = local_8 >> 0xb & 0x1fffff;
  local_8 = local_8 << 0x15;
  status = pack_round_double(0,0x41e,&mant_hi,dst);
  return status;
#undef mant_hi
#undef local_8
#undef local_4
}



