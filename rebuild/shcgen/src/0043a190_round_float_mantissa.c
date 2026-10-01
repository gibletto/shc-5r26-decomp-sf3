#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x1ff84))


// entry: 0043a190
// name : round_float_mantissa
// size : 62
// sig  : void round_float_mantissa(short * exponent, uint * mantissa)


int __cdecl round_float_mantissa(short *exponent,uint *mantissa)

{
  uint rounded;
  
  if ((g_loaded_request->fpu_mode & 2) == 0) {
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



