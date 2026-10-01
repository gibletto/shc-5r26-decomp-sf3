#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x1ff84))


// entry: 0043a1d0
// name : round_double_mantissa
// size : 81
// sig  : void round_double_mantissa(short * exponent, uint * mantissa)


int __cdecl round_double_mantissa(short *exponent,uint *mantissa)

{
  if ((g_loaded_request->cpu != 4) || ((g_loaded_request->fpu_mode & 2) == 0)) {
    if (((mantissa[2] & 0x80000000) != 0) &&
       (((mantissa[2] & 0x7fffffff) != 0 || ((mantissa[1] & 1) != 0)))) {
      if (mantissa[1] == 0xffffffff) {
        *mantissa = *mantissa + 1;
      }
      mantissa[1] = mantissa[1] + 1;
      if ((*mantissa & 0x200000) != 0) {
        *mantissa = (int)*mantissa >> 1;
        *exponent = *exponent + 1;
      }
    }
  }
  return;
}



