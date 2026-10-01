#include "decls.h"
#include "imports.h"

// entry: 0041e510
// name : open_shared_file
// size : 21
// sig  : FILE * __cdecl open_shared_file(char *path,char *mode)


FILE * __cdecl open_shared_file(char *path,char *mode)

{
  FILE *stream;
  
  stream = __fsopen(path,mode,0x40);
  return stream;
}
