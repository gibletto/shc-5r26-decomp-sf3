#include "decls.h"
#include "imports.h"

// entry: 0041fde0
// name : stock_get_short_arg
// size : 16
// sig  : ushort stock_get_short_arg(int * pargptr)


ushort __cdecl stock_get_short_arg(int *pargptr)

{
  ushort *puVar1;
  
  puVar1 = (ushort *)*pargptr;
  *pargptr = (int)(puVar1 + 2);
  return *puVar1;
}



