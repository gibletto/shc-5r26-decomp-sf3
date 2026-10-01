#include "decls.h"
#include "imports.h"

// entry: 00435500
// name : stock_fopen
// size : 21
// sig  : FILE * __cdecl stock_fopen(char *path,char *mode)


FILE * __cdecl stock_fopen(char *path,char *mode)

{
  FILE *stream;
  
  stream = __fsopen(path,mode,0x40);
  return stream;
}
