#include "decls.h"
#include "imports.h"

// entry: 0042ef50
// name : get_full_path
// size : 24
// sig  : char * __cdecl get_full_path(char *path,char *out)


char * __cdecl get_full_path(char *path,char *out)

{
  char *pcVar1;
  
  pcVar1 = stock_fullpath(out,path,0xfc);
  return pcVar1;
}
