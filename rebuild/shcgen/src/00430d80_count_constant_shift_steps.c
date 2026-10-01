#include "decls.h"
#include "imports.h"

// entry: 00430d80
// name : count_constant_shift_steps
// size : 116
// sig  : short count_constant_shift_steps(int amount)


short __cdecl count_constant_shift_steps(int amount)

{
  int sixteens;
  int eights;
  int twos;
  uint sign;
  
  sign = amount >> 0x1f;
  sixteens = (int)(amount + (sign & 0xf)) >> 4;
  if (sixteens != 0) {
    amount = ((amount ^ sign) - sign & 0xf ^ sign) - sign;
  }
  sign = amount >> 0x1f;
  eights = (int)(amount + (sign & 7)) >> 3;
  if (eights != 0) {
    amount = ((amount ^ sign) - sign & 7 ^ sign) - sign;
  }
  sign = amount >> 0x1f;
  twos = amount / 2;
  if (twos != 0) {
    amount = ((amount ^ sign) - sign & 1 ^ sign) - sign;
  }
  return (short)eights + (short)twos + (short)sixteens + (short)amount;
}



