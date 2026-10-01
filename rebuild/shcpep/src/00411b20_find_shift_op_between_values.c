#include "decls.h"
#include "imports.h"

// entry: 00411b20
// name : find_shift_op_between_values
// size : 105
// sig  : char find_shift_op_between_values(uint old_value, int new_value)


char __cdecl find_shift_op_between_values(uint old_value,int new_value)

{
  unsigned char _frec_18[24];
#define shifted_values (*(int (*)[4])(_frec_18 + 0))
#define shr8 (*(uint *)(_frec_18 + 16))
#define shr16 (*(uint *)(_frec_18 + 20))
  uint i;
  int *candidate;
  
  shifted_values[0] = old_value * 4;
  shifted_values[1] = old_value << 8;
  shifted_values[2] = old_value << 0x10;
  shifted_values[3] = old_value >> 2;
  shr8 = old_value >> 8;
  shr16 = old_value >> 0x10;
  i = 0;
  candidate = shifted_values;
  do {
    if (*candidate == new_value) {
      return (&g_shift_op_for_value_ratio)[i];
    }
    i = i + 1;
    candidate = candidate + 1;
  } while (i < 6);
  return '\0';
#undef shifted_values
#undef shr8
#undef shr16
}



