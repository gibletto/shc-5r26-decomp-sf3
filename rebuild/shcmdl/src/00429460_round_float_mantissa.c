#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 00429460
// name : round_float_mantissa
// size : 62
// sig  : void round_float_mantissa(short * exponent, uint * mantissa)


int __cdecl round_float_mantissa(short *exponent,uint *mantissa)

{
  uint rounded;
  
  if ((g_options_for_errors->fpu_mode & 2) == 0) {
    if (((mantissa[1] & 0x80000000) != 0) &&
       (((mantissa[1] & 0x7fffffff) != 0 || ((*mantissa & 1) != 0)))) {
      rounded = *mantissa + 1;
      *mantissa = rounded;
      if ((rounded & 0x1000000) != 0) {
        *mantissa = (int)rounded >> 1;
        *exponent = *exponent + 1;
      }
    }
  }
  return;
}



