#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 0043a6b0
// name : stock_setmode
// size : 128
// sig  : int stock_setmode(uint fh, int mode)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_setmode(uint fh,int mode)

{
  byte new_flags;
  byte old_flags;
  byte *osfile;
  
  if (fh < stock_nhandle) {
    osfile = (byte *)(*(int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3)) + 4 +
                     (fh & 0x1f) * 8);
    old_flags = *osfile;
    if ((old_flags & 1) != 0) {
      if (mode == 0x8000) {
        new_flags = old_flags & 0x7f;
      }
      else {
        if (mode != 0x4000) {
          _stock_errno = 0x16;
          return -1;
        }
        new_flags = old_flags | 0x80;
      }
      *osfile = new_flags;
      return (-(uint)((old_flags & 0x80) == 0) & 0x4000) + 0x4000;
    }
  }
  _stock_errno = 9;
  return -1;
}



