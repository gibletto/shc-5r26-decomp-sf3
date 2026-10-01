#include "decls.h"
#include "imports.h"

// entry: 00429ce0
// name : stock_fopen
// size : 21
// sig  : FILE * __cdecl stock_fopen(char *name,char *mode)


FILE * __cdecl stock_fopen(char *name,char *mode)

{
  FILE *pFVar1;
  
  pFVar1 = __fsopen(name,mode,0x40);
  return pFVar1;
}
