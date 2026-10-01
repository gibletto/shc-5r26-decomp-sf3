#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_doserrno
#define stock_doserrno (*(unsigned int *)(g_sd + 0x81b4))


// entry: 00438c20
// name : stock_dosmaperr
// size : 102
// sig  : void __cdecl stock_dosmaperr(uint oserrno)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_dosmaperr(uint oserrno)

{
  int i;
  uint *err_entry;
  
  i = 0;
  err_entry = &stock_errtable;
  stock_doserrno = oserrno;
  do {
    if (*err_entry == oserrno) {
      _stock_errno = *(undefined4 *)(i * 8 + SD(0x00443b2c));
      return;
    }
    err_entry = err_entry + 2;
    i = i + 1;
  } while (err_entry < &stock_commode);
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
