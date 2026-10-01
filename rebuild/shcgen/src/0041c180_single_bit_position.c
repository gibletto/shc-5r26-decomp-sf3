#include "decls.h"
#include "imports.h"

// entry: 0041c180
// name : single_bit_position
// size : 48
// sig  : short single_bit_position(uint mask)


short __cdecl single_bit_position(uint mask)

{
  short pos;
  short bit;
  bool found;
  
  pos = -1;
  bit = 0;
  found = false;
  do {
    if ((mask & 1) != 0) {
      if (found) {
        return -1;
      }
      found = true;
      pos = bit;
    }
    mask = (int)mask >> 1;
    bit = bit + 1;
  } while (bit < 0x20);
  return pos;
}



