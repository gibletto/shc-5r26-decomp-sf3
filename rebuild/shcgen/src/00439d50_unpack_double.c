#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x1ff84))


// entry: 00439d50
// name : unpack_double
// size : 282
// sig  : uint unpack_double(uint * value, uint * sign, ushort * exponent, uint * mantissa, int * fp_class)


uint __cdecl unpack_double(uint *value,uint *sign,ushort *exponent,uint *mantissa,int *fp_class)

{
  ushort uVar2;
  request *prVar1;
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
  prVar1 = g_loaded_request;
  if (*exponent != 0) {
    *mantissa = *mantissa | 0x100000;
    return (uint)uVar2 << 0x10;
  }
  if ((g_loaded_request->cpu == 4) && ((g_loaded_request->fpu_mode & 1) != 0)) {
    bits = (uint)g_loaded_request & 0xffff0000;
    *fp_class = 1;
    *mantissa = 0;
    mantissa[1] = 0;
    return bits;
  }
  *exponent = 1;
  top_byte = *(byte *)((int)mantissa + 2);
  while ((top_byte & 0x10) == 0) {
    prVar1 = (request *)(*mantissa * 2);
    *mantissa = (uint)prVar1;
    if ((mantissa[1] & 0x80000000) != 0) {
      prVar1 = (request *)((uint)prVar1 | 1);
      *mantissa = (uint)prVar1;
    }
    mantissa[1] = mantissa[1] * 2;
    *exponent = *exponent - 1;
    top_byte = *(byte *)((int)mantissa + 2);
  }
  return (uint)prVar1 & 0xffff0000;
}



