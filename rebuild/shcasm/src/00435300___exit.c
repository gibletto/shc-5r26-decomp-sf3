#include "decls.h"
#include "imports.h"

// entry: 00435300
// name : __exit
// size : 18
// sig  : void __exit(int _Code)


/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Release */

int __cdecl __exit(int _Code)

{
  stock_doexit(_Code,1,0);
  return;
}



