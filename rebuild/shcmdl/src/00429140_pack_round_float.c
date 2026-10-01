#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 00429140
// name : pack_round_float
// size : 350
// sig  : uint pack_round_float(uint sign, short exponent, uint * mantissa, uint * result)


uint __cdecl pack_round_float(uint sign,short exponent,uint *mantissa,uint *result)

{
  uint tmp_word;
  undefined2 status;
  uint *mant;
  
  mant = mantissa;
  status = 0;
  if ((*mantissa == 0) && (mantissa[1] == 0)) {
    *result = 0;
    return (uint)result & 0xffff0000;
  }
  if ((*mantissa & 0x800000) == 0) {
    do {
      tmp_word = *mantissa;
      *mantissa = tmp_word * 2;
      if ((mantissa[1] & 0x80000000) != 0) {
        *mantissa = tmp_word * 2 | 1;
      }
      exponent = exponent + -1;
      mantissa[1] = mantissa[1] * 2;
    } while ((*mantissa & 0x800000) == 0);
  }
  if (exponent < 1) {
    if (exponent < -0x18) {
      mantissa[1] = 0;
      exponent = 0;
      *mantissa = 0;
    }
    else {
      if ((mantissa[1] & 0x3fffffff) != 0) {
        mantissa[1] = mantissa[1] | 0x20000000;
      }
      exponent = exponent + -1;
      while (exponent < 0) {
        tmp_word = (int)mantissa[1] >> 1;
        mantissa[1] = tmp_word;
        if ((*mantissa & 1) == 0) {
          tmp_word = tmp_word & 0x7fffffff;
        }
        else {
          tmp_word = tmp_word | 0x80000000;
        }
        exponent = exponent + 1;
        mantissa[1] = tmp_word;
        *mantissa = (int)*mantissa >> 1;
        if ((mantissa[1] & 0x10000000) != 0) {
          tmp_word = mantissa[1] & 0xefffffff;
          mantissa[1] = tmp_word;
          mantissa[1] = tmp_word | 0x20000000;
        }
      }
    }
  }
  round_float_mantissa(&exponent,mantissa);
  if (exponent < 0xff) {
    if (exponent == 0) {
      if (*mant == 0) {
        status = 3;
      }
      else if ((g_options_for_errors->fpu_mode & 1) != 0) {
        status = 0;
        *mant = 0;
      }
    }
  }
  else {
    status = 2;
    *mant = 0;
    exponent = 0xff;
  }
  tmp_word = *mant & 0x7fffff;
  *mant = tmp_word;
  *result = (int)exponent << 0x17 | tmp_word | sign;
  return CONCAT22((short)(tmp_word >> 0x10),status);
}



