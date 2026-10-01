#include "decls.h"
#include "imports.h"

// entry: 0043a730
// name : stock_fopen
// size : 21
// sig  : FILE * stock_fopen(char * path, char * mode)


FILE * __cdecl stock_fopen(char *path,char *mode)

{
  FILE *fp;
  
  fp = __fsopen(path,mode,0x40);
  return fp;
}



