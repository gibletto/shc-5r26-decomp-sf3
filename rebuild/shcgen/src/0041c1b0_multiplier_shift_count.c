#include "decls.h"
#include "imports.h"

// entry: 0041c1b0
// name : multiplier_shift_count
// size : 69
// sig  : short multiplier_shift_count(uint value)


short __cdecl multiplier_shift_count(uint value)

{
  short shift;
  
  shift = single_bit_position(value);
  if (shift == -1) {
    shift = single_bit_position(value - 1);
    if (shift != -1) {
      return shift;
    }
    shift = single_bit_position(value + 1);
  }
  if (shift == -1) {
    shift = two_bit_mask_bit_position(value,1);
  }
  return shift;
}



