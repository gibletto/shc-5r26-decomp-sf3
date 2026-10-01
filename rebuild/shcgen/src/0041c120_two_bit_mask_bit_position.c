#include "decls.h"
#include "imports.h"

// entry: 0041c120
// name : two_bit_mask_bit_position
// size : 91
// sig  : short two_bit_mask_bit_position(uint mask, short low)


short __cdecl two_bit_mask_bit_position(uint mask,short low)

{
  short high;
  short low_bit;
  short bit;
  short nbits;
  short next_high;
  short next_low;
  
  bit = 0;
  nbits = 0;
  low_bit = -1;
  high = -1;
  do {
    if ((mask & 1) != 0) {
      next_high = high;
      next_low = bit;
      if ((nbits != 0) && (next_high = bit, next_low = low_bit, nbits != 1)) {
        low_bit = -1;
        goto LAB_0041c15e;
      }
      low_bit = next_low;
      nbits = nbits + 1;
      high = next_high;
    }
    mask = (int)mask >> 1;
    bit = bit + 1;
    if (0x1f < bit) {
LAB_0041c15e:
      if ((low_bit != -1) && (high == -1)) {
        low_bit = -1;
      }
      if (low == 0) {
        low_bit = high;
      }
      return low_bit;
    }
  } while( true );
}



