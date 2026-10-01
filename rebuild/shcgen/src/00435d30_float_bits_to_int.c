#include "decls.h"
#include "imports.h"

// entry: 00435d30
// name : float_bits_to_int
// size : 205
// sig  : int float_bits_to_int(uint * src, uint * dst)


int __cdecl float_bits_to_int(uint *src,uint *dst)

{
  unsigned char _frec_e[14];
#define exponent (*(ushort *)(_frec_e + 0))
#define mantissa (*(uint *)(_frec_e + 2))
#define fp_class (*(int *)(_frec_e + 6))
#define sign (*(uint *)(_frec_e + 10))
  int status;
  ushort status_hi;
  short shift;
  
  status = unpack_float(src,&sign,&exponent,&mantissa,&fp_class);
  status_hi = (ushort)((uint)status >> 0x10);
  if (fp_class == 0) {
    if ((0x7e < (short)exponent) && ((short)exponent < 0xb6)) {
      shift = exponent - 0x96;
      (*(unsigned char *)((char *)&exponent + 0)) = (byte)shift;
      if (shift < 1) {
        if (shift < 0) {
          mantissa = (int)mantissa >> (-(byte)exponent & 0x1f);
        }
      }
      else {
        mantissa = mantissa << ((byte)exponent & 0x1f);
      }
      if ((int)sign < 0) {
        *dst = -mantissa;
        return -mantissa & 0xffff0000;
      }
      *dst = mantissa;
      return mantissa & 0xffff0000;
    }
    *dst = 0;
  }
  else {
    *dst = 0;
    if ((fp_class == 2) || (fp_class == 3)) {
      return CONCAT22(status_hi,1);
    }
  }
  return (uint)status_hi << 0x10;
#undef exponent
#undef mantissa
#undef fp_class
#undef sign
}



