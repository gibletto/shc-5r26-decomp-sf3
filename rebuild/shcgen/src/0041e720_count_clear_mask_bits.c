#include "decls.h"
#include "imports.h"

// entry: 0041e720
// name : count_clear_mask_bits
// size : 30
// sig  : int count_clear_mask_bits(short mask)


int __cdecl count_clear_mask_bits(short mask)

{
  int n;
  int bit;
  
  bit = 0;
  n = 0;
  do {
    if (((int)mask & 1 << ((byte)bit & 0x1f)) == 0) {
      n = n + 1;
    }
    bit = bit + 1;
  } while (bit < 0x10);
  return n;
}



