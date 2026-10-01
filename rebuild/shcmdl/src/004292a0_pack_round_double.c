#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 004292a0
// name : pack_round_double
// size : 443
// sig  : int pack_round_double(uint sign, short exponent, uint * mantissa, uint * result)


int __cdecl pack_round_double(uint sign,short exponent,uint *mantissa,uint *result)

{
  uint tmp_word;
  uint tmp_word_1;
  undefined2 status;
  uint *mant;
  
  mant = mantissa;
  status = 0;
  if (((*mantissa == 0) && (mantissa[1] == 0)) && (mantissa[2] == 0)) {
    *result = 0;
    result[1] = 0;
    return 0;
  }
  if ((*mantissa & 0x100000) == 0) {
    do {
      tmp_word = *mantissa;
      *mantissa = tmp_word * 2;
      if ((mantissa[1] & 0x80000000) != 0) {
        *mantissa = tmp_word * 2 | 1;
      }
      tmp_word = mantissa[1] * 2;
      mantissa[1] = tmp_word;
      if ((mantissa[2] & 0x80000000) != 0) {
        mantissa[1] = tmp_word | 1;
      }
      exponent = exponent + -1;
      mantissa[2] = mantissa[2] * 2;
    } while ((*mantissa & 0x100000) == 0);
  }
  if (exponent < 1) {
    if (exponent < -0x35) {
      mantissa[2] = 0;
      mantissa[1] = 0;
      exponent = 0;
      *mantissa = 0;
    }
    else {
      if ((mantissa[2] & 0x3fffffff) != 0) {
        mantissa[2] = mantissa[2] | 0x20000000;
      }
      exponent = exponent + -1;
      while (exponent < 0) {
        tmp_word = (int)mantissa[2] >> 1;
        mantissa[2] = tmp_word;
        if ((mantissa[1] & 1) == 0) {
          tmp_word = tmp_word & 0x7fffffff;
        }
        else {
          tmp_word = tmp_word | 0x80000000;
        }
        tmp_word_1 = (int)mantissa[1] >> 1;
        mantissa[2] = tmp_word;
        mantissa[1] = tmp_word_1;
        if ((*mantissa & 1) == 0) {
          tmp_word_1 = tmp_word_1 & 0x7fffffff;
        }
        else {
          tmp_word_1 = tmp_word_1 | 0x80000000;
        }
        exponent = exponent + 1;
        mantissa[1] = tmp_word_1;
        *mantissa = (int)*mantissa >> 1;
        if ((mantissa[2] & 0x10000000) != 0) {
          tmp_word = mantissa[2] & 0xefffffff;
          mantissa[2] = tmp_word;
          mantissa[2] = tmp_word | 0x20000000;
        }
      }
    }
  }
  round_double_mantissa(&exponent,mantissa);
  if (exponent < 0x7ff) {
    if (((exponent == 0) && (*mant == 0)) && (mant[1] == 0)) {
      status = 3;
    }
    else if (((exponent == 0) && (g_options_for_errors->cpu == 4)) &&
            ((g_options_for_errors->fpu_mode & 1) != 0)) {
      status = 0;
      *mant = 0;
      mant[1] = 0;
    }
  }
  else {
    status = 2;
    *mant = 0;
    mant[1] = 0;
    exponent = 0x7ff;
  }
  tmp_word = *mant;
  *mant = tmp_word & 0xfffff;
  *result = (int)exponent << 0x14 | sign | tmp_word & 0xfffff;
  tmp_word = mant[1];
  result[1] = tmp_word;
  return CONCAT22((short)(tmp_word >> 0x10),status);
}



