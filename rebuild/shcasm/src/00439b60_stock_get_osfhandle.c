#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 00439b60
// name : stock_get_osfhandle
// size : 67
// sig  : int stock_get_osfhandle(uint fh)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_get_osfhandle(uint fh)

{
  int *ioinfo;
  
  if ((fh < stock_nhandle) &&
     (ioinfo = (int *)(*(int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3)) +
                      (fh & 0x1f) * 8), (*(byte *)(ioinfo + 1) & 1) != 0)) {
    return *ioinfo;
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
}



