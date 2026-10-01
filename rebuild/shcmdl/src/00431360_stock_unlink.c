#include "decls.h"
#include "imports.h"

// entry: 00431360
// name : stock_unlink
// size : 14
// sig  : int __cdecl stock_unlink(char *path)


int __cdecl stock_unlink(char *path)

{
  int iVar1;
  
  iVar1 = stock_remove(path);
  return iVar1;
}
