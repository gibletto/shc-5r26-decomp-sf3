#include "decls.h"
#include "imports.h"

// entry: 00420bf0
// name : setSBCS
// size : 44
// sig  : undefined setSBCS(void)


/* Library Function - Single Match
    _setSBCS
   
   Library: Visual Studio 1998 Release */

int __cdecl setSBCS(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &stock_mbctype;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  stock_mbulinfo = 0;
  stock_mbcodepage = 0;
  stock_mblcid = 0;
  DAT_0042896c = 0;
  DAT_00428970 = 0;
  return;
}



