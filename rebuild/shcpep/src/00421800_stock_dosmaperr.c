#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_doserrno
#define stock_doserrno (*(unsigned int *)(g_sd + 0x4464))


// entry: 00421800
// name : stock_dosmaperr
// size : 102
// sig  : void stock_dosmaperr(uint oserrno)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_dosmaperr(uint oserrno)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = 0;
  puVar2 = &stock_errtable;
  stock_doserrno = oserrno;
  do {
    if (*puVar2 == oserrno) {
      _stock_errno = *(undefined4 *)(iVar1 * 8 + SD(0x00428dd4));
      return;
    }
    puVar2 = puVar2 + 2;
    iVar1 = iVar1 + 1;
  } while (puVar2 < &DAT_00428f38);
  if ((0x12 < oserrno) && (oserrno < 0x25)) {
    _stock_errno = 0xd;
    return;
  }
  if ((0xbb < oserrno) && (oserrno < 0xcb)) {
    _stock_errno = 8;
    return;
  }
  _stock_errno = 0x16;
  return;
}



