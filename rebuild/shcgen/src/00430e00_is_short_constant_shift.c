#include "decls.h"
#include "imports.h"

// entry: 00430e00
// name : is_short_constant_shift
// size : 27
// sig  : char is_short_constant_shift(int amount)


char __cdecl is_short_constant_shift(int amount)

{
  short steps;
  
  steps = count_constant_shift_steps(amount);
  return steps < 4;
}



