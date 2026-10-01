#include "decls.h"
#include "imports.h"

// entry: 0043fee0
// name : stock_remove
// size : 48
// sig  : int stock_remove(char * path)


int __cdecl stock_remove(char *path)

{
  BOOL deleted;
  uint oserr;
  
  deleted = DeleteFileA(path);
  oserr = 0;
  if (deleted == 0) {
    oserr = GetLastError();
  }
  if (oserr != 0) {
    stock_dosmaperr(oserr);
    return -1;
  }
  return 0;
}



