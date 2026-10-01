#include "decls.h"
#include "imports.h"

// entry: 004350d8
// name : stock_strcat
// size : 224
// sig  : uint * stock_strcat(uint * param_1, uint * param_2)


uint * __cdecl stock_strcat(uint *param_1,uint *param_2)

{
  uint *scan;
  uint chunk;
  uint *dst;
  byte ch;
  uint probe;
  
  scan = param_1;
  do {
    if (((uint)scan & 3) == 0) goto LAB_004350f4;
    chunk = *scan;
    scan = (uint *)((int)scan + 1);
  } while ((byte)chunk != 0);
  goto LAB_00435127;
  while( true ) {
    if ((chunk & 0xff0000) == 0) {
      dst = (uint *)((int)dst + 2);
      goto joined_r0x00435143;
    }
    if ((chunk & 0xff000000) == 0) break;
LAB_004350f4:
    do {
      dst = scan;
      scan = dst + 1;
    } while (((*dst ^ 0xffffffff ^ *dst + 0x7efefeff) & 0x81010100) == 0);
    chunk = *dst;
    if ((char)chunk == '\0') goto joined_r0x00435143;
    if ((char)(chunk >> 8) == '\0') {
      dst = (uint *)((int)dst + 1);
      goto joined_r0x00435143;
    }
  }
LAB_00435127:
  dst = (uint *)((int)scan + -1);
joined_r0x00435143:
  do {
    if (((uint)param_2 & 3) == 0) {
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
    ch = (byte)*param_2;
    chunk = (uint)ch;
    param_2 = (uint *)((int)param_2 + 1);
    if (ch == 0) goto LAB_004351b0;
    *(byte *)dst = ch;
    dst = (uint *)((int)dst + 1);
  } while( true );
}



