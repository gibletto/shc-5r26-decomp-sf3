#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 00428f30
// name : unpack_float
// size : 225
// sig  : int unpack_float(uint * value, uint * sign, ushort * exponent, uint * mantissa, int * fp_class)


int __cdecl unpack_float(uint *value,uint *sign,ushort *exponent,uint *mantissa,int *fp_class)

{
  ushort uVar1;
  uint bits;
  byte top_byte;
  
  bits = *value;
  *mantissa = bits;
  *sign = bits;
  *sign = bits & 0x80000000;
  *exponent = ((ushort)(bits >> 0x10) & 0x7f80) >> 7;
  bits = *mantissa & 0x7fffff;
  *mantissa = bits;
  uVar1 = (ushort)((uint)sign >> 0x10);
  if ((*exponent == 0) && (bits == 0)) {
    *fp_class = 1;
    return (uint)uVar1 << 0x10;
  }
  if (*exponent == 0xff) {
    if (bits == 0) {
      *fp_class = 2;
      return (uint)uVar1 << 0x10;
    }
    if (bits != 0) {
      *fp_class = 3;
      return (uint)uVar1 << 0x10;
    }
  }
  *fp_class = 0;
  if (*exponent != 0) {
    *mantissa = *mantissa | 0x800000;
    return (uint)uVar1 << 0x10;
  }
  if ((g_options_for_errors->fpu_mode & 1) == 0) {
    *exponent = 1;
    top_byte = *(byte *)((int)mantissa + 2);
    while ((top_byte & 0x80) == 0) {
      *mantissa = *mantissa << 1;
      *exponent = *exponent - 1;
      top_byte = *(byte *)((int)mantissa + 2);
    }
    return (uint)uVar1 << 0x10;
  }
  *fp_class = 1;
  *mantissa = 0;
  return (uint)uVar1 << 0x10;
}



