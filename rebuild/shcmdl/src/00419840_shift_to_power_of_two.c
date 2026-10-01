#include "decls.h"
#include "imports.h"

// entry: 00419840
// name : shift_to_power_of_two
// size : 24
// sig  : int shift_to_power_of_two(int count)


int __cdecl shift_to_power_of_two(int count)

{
  if ((-1 < count) && (count < 0x20)) {
    return 1 << ((byte)count & 0x1f);
  }
  return 0;
}



