#include "decls.h"
#include "imports.h"

// entry: 0043ac30
// name : stock_unlink
// size : 14
// sig  : int __cdecl stock_unlink(char *path)


int __cdecl stock_unlink(char *path)

{
  int result;
  
  result = stock_remove(path);
  return result;
}
