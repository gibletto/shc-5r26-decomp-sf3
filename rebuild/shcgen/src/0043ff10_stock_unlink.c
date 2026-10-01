#include "decls.h"
#include "imports.h"

// entry: 0043ff10
// name : stock_unlink
// size : 14
// sig  : int stock_unlink(char * path)


int __cdecl stock_unlink(char *path)

{
  int iVar1;
  
  iVar1 = stock_remove(path);
  return iVar1;
}



