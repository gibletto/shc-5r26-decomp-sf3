#include "decls.h"
#include "imports.h"

// entry: 00423a70
// name : stock_remove
// size : 48
// sig  : int stock_remove(char * path)


int __cdecl stock_remove(char *path)

{
  BOOL BVar1;
  uint oserrno;
  
  BVar1 = DeleteFileA(path);
  oserrno = 0;
  if (BVar1 == 0) {
    oserrno = GetLastError();
  }
  if (oserrno != 0) {
    stock_dosmaperr(oserrno);
    return -1;
  }
  return 0;
}



