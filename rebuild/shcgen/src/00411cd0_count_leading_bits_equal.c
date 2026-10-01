#include "decls.h"
#include "imports.h"

// entry: 00411cd0
// name : count_leading_bits_equal
// size : 44
// sig  : int count_leading_bits_equal(int value, int max_bits, int bit)


/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int __cdecl count_leading_bits_equal(int value,int max_bits,int bit)

{
  int count;
  
  count = 0;
  for (; (max_bits != 0 && (-(value >> 0x1f) == bit)); value = value * 2) {
    count = count + 1;
    max_bits = max_bits + -1;
  }
  return count;
}



