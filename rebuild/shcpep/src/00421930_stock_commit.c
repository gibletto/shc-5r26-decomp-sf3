#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x6e40))


// entry: 00421930
// name : stock_commit
// size : 111
// sig  : int stock_commit(uint fh)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_commit(uint fh)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD DVar2;
  int iVar3;
  
  if ((fh < stock_nhandle) &&
     ((*(byte *)(*(int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3)) + 4 + (fh & 0x1f) * 8
                ) & 1) != 0)) {
    hFile = (HANDLE)stock_get_osfhandle(fh);
    BVar1 = FlushFileBuffers(hFile);
    DVar2 = 0;
    if (BVar1 == 0) {
      DVar2 = GetLastError();
    }
    iVar3 = 0;
    if (DVar2 != 0) {
      _stock_errno = 9;
      stock_doserrno = DVar2;
      return -1;
    }
  }
  else {
    _stock_errno = 9;
    iVar3 = -1;
  }
  return iVar3;
}



