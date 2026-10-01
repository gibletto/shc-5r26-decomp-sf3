#include "decls.h"
#include "imports.h"

// entry: 0041fdb0
// name : stock_get_int_arg
// size : 15
// sig  : int stock_get_int_arg(int * pargptr)


int __cdecl stock_get_int_arg(int *pargptr)

{
  int *piVar1;
  
  piVar1 = (int *)*pargptr;
  *pargptr = (int)(piVar1 + 1);
  return *piVar1;
}



