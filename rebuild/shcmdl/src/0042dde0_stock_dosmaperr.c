#include "decls.h"
#include "imports.h"

// entry: 0042dde0
// name : stock_dosmaperr
// size : 102
// sig  : void stock_dosmaperr(uint oserr)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_dosmaperr(uint oserr)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = 0;
  puVar2 = &stock_errtable;
  stock_doserrno = oserr;
  do {
    if (*puVar2 == oserr) {
      _stock_errno = *(undefined4 *)(iVar1 * 8 + SD(0x00436ccc));
      return;
    }
    puVar2 = puVar2 + 2;
    iVar1 = iVar1 + 1;
  } while (puVar2 < &DAT_00436e30);
  if ((0x12 < oserr) && (oserr < 0x25)) {
    _stock_errno = 0xd;
    return;
  }
  if ((0xbb < oserr) && (oserr < 0xcb)) {
    _stock_errno = 8;
    return;
  }
  _stock_errno = 0x16;
  return;
}



