#include "decls.h"
#include "imports.h"

// entry: 004350d0
// name : stock_strcpy
// size : 7
// sig  : uint * stock_strcpy(uint * param_1, uint * param_2)


uint * __cdecl stock_strcpy(uint *param_1,uint *param_2)

{
  uint chunk;
  uint *dst;
  byte ch;
  uint probe;
  
  dst = param_1;
  while (((uint)param_2 & 3) != 0) {
    ch = (byte)*param_2;
    chunk = (uint)ch;
    param_2 = (uint *)((int)param_2 + 1);
    if (ch == 0) goto LAB_004351b0;
    *(byte *)dst = ch;
    dst = (uint *)((int)dst + 1);
  }
  do {
    probe = *param_2;
    chunk = *param_2;
    param_2 = param_2 + 1;
    if (((probe ^ 0xffffffff ^ probe + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)chunk == '\0') {
LAB_004351b0:
        *(byte *)dst = (byte)chunk;
        return param_1;
      }
      if ((char)(chunk >> 8) == '\0') {
        *(short *)dst = (short)chunk;
        return param_1;
      }
      if ((chunk & 0xff0000) == 0) {
        *(short *)dst = (short)chunk;
        *(byte *)((int)dst + 2) = 0;
        return param_1;
      }
      if ((chunk & 0xff000000) == 0) {
        *dst = chunk;
        return param_1;
      }
    }
    *dst = chunk;
    dst = dst + 1;
  } while( true );
}



