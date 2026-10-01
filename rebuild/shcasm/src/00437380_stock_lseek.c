#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 00437380
// name : stock_lseek
// size : 188
// sig  : uint stock_lseek(uint fh, int pos, uint mthd)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stock_lseek(uint fh,int pos,uint mthd)

{
  HANDLE hFile;
  DWORD new_pos;
  uint oserrno;
  int *ioinfo_block;
  int ioinfo_ofs;
  byte *osfile;
  
  if (fh < stock_nhandle) {
    ioinfo_block = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3));
    ioinfo_ofs = (fh & 0x1f) * 8;
    if ((*(byte *)(*ioinfo_block + 4 + ioinfo_ofs) & 1) != 0) {
      hFile = (HANDLE)stock_get_osfhandle(fh);
      if (hFile == (HANDLE)0xffffffff) {
        _stock_errno = 9;
        return 0xffffffff;
      }
      new_pos = SetFilePointer(hFile,pos,(PLONG)0x0,mthd);
      oserrno = 0;
      if (new_pos == 0xffffffff) {
        oserrno = GetLastError();
      }
      if (oserrno != 0) {
        stock_dosmaperr(oserrno);
        return 0xffffffff;
      }
      osfile = (byte *)(*ioinfo_block + 4 + ioinfo_ofs);
      *osfile = *osfile & 0xfd;
      return new_pos;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return 0xffffffff;
}



