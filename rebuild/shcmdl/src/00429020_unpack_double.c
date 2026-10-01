#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 00429020
// name : unpack_double
// size : 282
// sig  : uint unpack_double(uint * value, uint * sign, ushort * exponent, uint * mantissa, int * fp_class)


uint __cdecl unpack_double(uint *value,uint *sign,ushort *exponent,uint *mantissa,int *fp_class)

{
  ushort uVar2;
  option_record *poVar1;
  uint bits;
  uint lo_word;
  byte top_byte;
  
  bits = *value;
  *mantissa = bits;
  *sign = bits;
  lo_word = value[1];
  mantissa[1] = lo_word;
  *sign = *sign & 0x80000000;
  *exponent = ((ushort)(bits >> 0x10) & 0x7ff0) >> 4;
  bits = *mantissa & 0xfffff;
  *mantissa = bits;
  uVar2 = (ushort)(lo_word >> 0x10);
  if (((*exponent == 0) && (bits == 0)) && (mantissa[1] == 0)) {
    *fp_class = 1;
    return (uint)uVar2 << 0x10;
  }
  if (*exponent == 0x7ff) {
    if ((bits == 0) && (mantissa[1] == 0)) {
      *fp_class = 2;
      return (uint)uVar2 << 0x10;
    }
    if ((bits != 0) || (mantissa[1] != 0)) {
      *fp_class = 3;
      return (uint)uVar2 << 0x10;
    }
  }
  *fp_class = 0;
  poVar1 = g_options_for_errors;
  if (*exponent != 0) {
    *mantissa = *mantissa | 0x100000;
    return (uint)uVar2 << 0x10;
  }
  if ((g_options_for_errors->cpu == 4) && ((g_options_for_errors->fpu_mode & 1) != 0)) {
    bits = (uint)g_options_for_errors & 0xffff0000;
    *fp_class = 1;
    *mantissa = 0;
    mantissa[1] = 0;
    return bits;
  }
  *exponent = 1;
  top_byte = *(byte *)((int)mantissa + 2);
  while ((top_byte & 0x10) == 0) {
    poVar1 = (option_record *)(*mantissa * 2);
    *mantissa = (uint)poVar1;
    if ((mantissa[1] & 0x80000000) != 0) {
      poVar1 = (option_record *)((uint)poVar1 | 1);
      *mantissa = (uint)poVar1;
    }
    mantissa[1] = mantissa[1] * 2;
    *exponent = *exponent - 1;
    top_byte = *(byte *)((int)mantissa + 2);
  }
  return (uint)poVar1 & 0xffff0000;
}



