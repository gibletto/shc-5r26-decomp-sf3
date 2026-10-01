#include "decls.h"
#include "imports.h"

// entry: 004276c0
// name : reverse_bits_16
// size : 108
// sig  : ushort reverse_bits_16(ushort value)


ushort __cdecl reverse_bits_16(ushort value)

{
  undefined2 bit_index;
  undefined2 reversed;
  
  reversed = 0;
  for (bit_index = 0; bit_index < 0x10; bit_index = bit_index + 1) {
    if ((value & 1) != 0) {
      reversed = reversed | 1;
    }
    value = (short)value >> 1;
    if (bit_index != 0xf) {
      reversed = reversed << 1;
    }
  }
  return reversed;
}



