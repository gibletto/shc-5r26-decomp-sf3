#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x6e40))


// entry: 00421870
// name : stock_lseek
// size : 188
// sig  : uint stock_lseek(uint fh, int pos, uint mthd)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stock_lseek(uint fh,int pos,uint mthd)

{
  int *piVar1;
  int iVar2;
  byte *pbVar3;
  HANDLE hFile;
  DWORD DVar4;
  uint oserrno;
  
  if (fh < stock_nhandle) {
    piVar1 = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3));
    iVar2 = (fh & 0x1f) * 8;
    if ((*(byte *)(*piVar1 + 4 + iVar2) & 1) != 0) {
      hFile = (HANDLE)stock_get_osfhandle(fh);
      if (hFile == (HANDLE)0xffffffff) {
        _stock_errno = 9;
        return 0xffffffff;
      }
      DVar4 = SetFilePointer(hFile,pos,(PLONG)0x0,mthd);
      oserrno = 0;
      if (DVar4 == 0xffffffff) {
        oserrno = GetLastError();
      }
      if (oserrno != 0) {
        stock_dosmaperr(oserrno);
        return 0xffffffff;
      }
      pbVar3 = (byte *)(*piVar1 + 4 + iVar2);
      *pbVar3 = *pbVar3 & 0xfd;
      return DVar4;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return 0xffffffff;
}



