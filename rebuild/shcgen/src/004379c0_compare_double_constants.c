#include "decls.h"
#include "imports.h"

// entry: 004379c0
// name : compare_double_constants
// size : 181
// sig  : short compare_double_constants(uint * a, uint * b)


short __cdecl compare_double_constants(uint *a,uint *b)

{
  unsigned char _frec_10[16];
#define b_hi (*(uint *)(_frec_10 + 0))
#define b_lo (*(uint *)(_frec_10 + 4))
#define a_hi (*(uint *)(_frec_10 + 8))
#define a_lo (*(uint *)(_frec_10 + 12))
  int cmp;
  
  a_hi = *a;
  a_lo = a[1];
  b_hi = *b;
  b_lo = b[1];
  if ((((a_hi & 0x7ff00000) != 0x7ff00000) || (((a_hi & 0xfffff) == 0 && (a_lo == 0)))) &&
     (((b_hi & 0x7ff00000) != 0x7ff00000 || (((b_hi & 0xfffff) == 0 && (b_lo == 0)))))) {
    if (((a_hi & 0x7fffffff) == 0) && (a_lo == 0)) {
      a_hi = 0;
    }
    if (((b_hi & 0x7fffffff) == 0) && (b_lo == 0)) {
      b_hi = 0;
    }
    cmp = compare_multiword(&a_hi,&b_hi,2);
    return (short)cmp + 1;
  }
  return -1;
#undef b_hi
#undef b_lo
#undef a_hi
#undef a_lo
}



