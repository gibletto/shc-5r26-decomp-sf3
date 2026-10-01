#include "decls.h"
#include "imports.h"

// entry: 00437260
// name : stock_get_short_arg
// size : 16
// sig  : ushort stock_get_short_arg(int * pargptr)


ushort __cdecl stock_get_short_arg(int *pargptr)

{
  ushort *arg;
  
  arg = (ushort *)*pargptr;
  *pargptr = (int)(arg + 2);
  return *arg;
}



