#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 00439ad0
// name : stock_free_osfhnd
// size : 144
// sig  : int stock_free_osfhnd(uint fh)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_free_osfhnd(uint fh)

{
  int *ioinfo;
  DWORD nStdHandle;
  int *ioinfo_block;
  int ioinfo_ofs;
  
  if (fh < stock_nhandle) {
    ioinfo_block = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3));
    ioinfo_ofs = (fh & 0x1f) * 8;
    ioinfo = (int *)(*ioinfo_block + ioinfo_ofs);
    if (((*(byte *)(ioinfo + 1) & 1) != 0) && (*ioinfo != -1)) {
      if (stock_app_type == 1) {
        if (fh == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (fh == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (fh != 2) goto LAB_00439b36;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_00439b36:
      *(undefined4 *)(*ioinfo_block + ioinfo_ofs) = 0xffffffff;
      return 0;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
}



