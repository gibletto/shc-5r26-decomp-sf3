#include "decls.h"
#include "imports.h"

// entry: 00437230
// name : stock_get_int_arg
// size : 15
// sig  : int stock_get_int_arg(int * pargptr)


int __cdecl stock_get_int_arg(int *pargptr)

{
  int *arg;
  
  arg = (int *)*pargptr;
  *pargptr = (int)(arg + 1);
  return *arg;
}



