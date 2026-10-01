#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_doserrno
#define stock_doserrno (*(unsigned int *)(g_sd + 0x1ca24))


// entry: 0043d150
// name : stock_dosmaperr
// size : 102
// sig  : void stock_dosmaperr(uint oserr)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_dosmaperr(uint oserr)

{
  int i;
  uint *entry;
  
  i = 0;
  entry = &stock_errtable;
  stock_doserrno = oserr;
  do {
    if (*entry == oserr) {
      _stock_errno = *(undefined4 *)(i * 8 + SD(0x0045d36c));
      return;
    }
    entry = entry + 2;
    i = i + 1;
  } while (entry < &DAT_0045d4d0);
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



