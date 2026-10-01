#include "decls.h"
#include "imports.h"

// entry: 00436410
// name : setSBCS
// size : 44
// sig  : undefined4 __cdecl setSBCS(void)


/* Library Function - Single Match
    _setSBCS
   
   Library: Visual Studio 1998 Release */

undefined4 __cdecl setSBCS(void)

{
  int n;
  undefined4 *dst;
  
  dst = &stock_mbctype;
  for (n = 0x40; n != 0; n = n + -1) {
    *dst = 0;
    dst = dst + 1;
  }
  *(undefined1 *)dst = 0;
  stock_mbulinfo = 0;
  stock_mbcodepage = 0;
  stock_mblcid = 0;
  DAT_004435ec = 0;
  DAT_004435f0 = 0;
  return 0;
}
