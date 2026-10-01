#include "decls.h"
#include "imports.h"

// entry: 00431330
// name : stock_remove
// size : 48
// sig  : int stock_remove(char * path)


int __cdecl stock_remove(char *path)

{
  BOOL BVar1;
  uint oserr;
  
  BVar1 = DeleteFileA(path);
  oserr = 0;
  if (BVar1 == 0) {
    oserr = GetLastError();
  }
  if (oserr != 0) {
    stock_dosmaperr(oserr);
    return -1;
  }
  return 0;
}



