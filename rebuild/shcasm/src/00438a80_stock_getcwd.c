#include "decls.h"
#include "imports.h"

// entry: 00438a80
// name : stock_getcwd
// size : 21
// sig  : char * __cdecl stock_getcwd(char *buf,uint maxlen)


char * __cdecl stock_getcwd(char *buf,uint maxlen)

{
  char *result;
  
  result = stock_getdcwd(0,buf,maxlen);
  return result;
}
