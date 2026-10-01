#include "decls.h"
#include "imports.h"

// entry: 0041e560
// name : stock_exit
// size : 18
// sig  : void stock_exit(uint exit_code)


int __cdecl stock_exit(uint exit_code)

{
  stock_doexit(exit_code,0,0);
  return;
}



