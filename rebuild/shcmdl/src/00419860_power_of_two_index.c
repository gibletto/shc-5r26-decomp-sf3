#include "decls.h"
#include "imports.h"

// entry: 00419860
// name : power_of_two_index
// size : 50
// sig  : int power_of_two_index(uint value, int flag)


int __cdecl power_of_two_index(uint value,int flag)

{
  int result;
  int bit;
  bool bVar1;
  
  result = 0;
  bit = 1;
  while (((value & 1) == 0 || (bVar1 = result == 0, result = bit, bVar1))) {
    value = (int)value >> 1;
    bit = bit + 1;
    if (0x20 < bit) {
LAB_00419883:
      if ((flag != 0) && (result == 0x20)) {
        result = 0;
      }
      return result;
    }
  }
  result = 0;
  goto LAB_00419883;
}



