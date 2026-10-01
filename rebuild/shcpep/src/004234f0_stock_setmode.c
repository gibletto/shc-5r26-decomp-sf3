#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x6e40))


// entry: 004234f0
// name : stock_setmode
// size : 128
// sig  : int stock_setmode(uint fh, int mode)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_setmode(uint fh,int mode)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  
  if (fh < stock_nhandle) {
    pbVar1 = (byte *)(*(int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3)) + 4 +
                     (fh & 0x1f) * 8);
    bVar2 = *pbVar1;
    if ((bVar2 & 1) != 0) {
      if (mode == 0x8000) {
        bVar3 = bVar2 & 0x7f;
      }
      else {
        if (mode != 0x4000) {
          _stock_errno = 0x16;
          return -1;
        }
        bVar3 = bVar2 | 0x80;
      }
      *pbVar1 = bVar3;
      return (-(uint)((bVar2 & 0x80) == 0) & 0x4000) + 0x4000;
    }
  }
  _stock_errno = 9;
  return -1;
}



