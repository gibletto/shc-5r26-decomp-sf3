#include "decls.h"
#include "imports.h"

// entry: 00427b70
// name : convert_float_to_int
// size : 205
// sig  : uint convert_float_to_int(uint * src, uint * dst)


uint __cdecl convert_float_to_int(uint *src,uint *dst)

{
  unsigned char _frec_e[14];
#define exponent (*(ushort *)(_frec_e + 0))
#define mant (*(uint *)(_frec_e + 2))
#define fp_class (*(int *)(_frec_e + 6))
#define sign (*(uint *)(_frec_e + 10))
  int iVar1;
  ushort uVar2;
  short shift;
  
  iVar1 = unpack_float(src,&sign,&exponent,&mant,&fp_class);
  uVar2 = (ushort)((uint)iVar1 >> 0x10);
  if (fp_class == 0) {
    if ((0x7e < (short)exponent) && ((short)exponent < 0xb6)) {
      shift = exponent - 0x96;
      (*(unsigned char *)((char *)&exponent + 0)) = (byte)shift;
      if (shift < 1) {
        if (shift < 0) {
          mant = (int)mant >> (-(byte)exponent & 0x1f);
        }
      }
      else {
        mant = mant << ((byte)exponent & 0x1f);
      }
      if ((int)sign < 0) {
        *dst = -mant;
        return -mant & 0xffff0000;
      }
      *dst = mant;
      return mant & 0xffff0000;
    }
    *dst = 0;
  }
  else {
    *dst = 0;
    if ((fp_class == 2) || (fp_class == 3)) {
      return CONCAT22(uVar2,1);
    }
  }
  return (uint)uVar2 << 0x10;
#undef exponent
#undef mant
#undef fp_class
#undef sign
}



