#include "decls.h"
#include "imports.h"

// entry: 00429a70
// name : stock_exit
// size : 18
// sig  : void stock_exit(uint errcode)


int __cdecl stock_exit(uint errcode)

{
  stock_doexit(errcode,0,0);
  return;
}



