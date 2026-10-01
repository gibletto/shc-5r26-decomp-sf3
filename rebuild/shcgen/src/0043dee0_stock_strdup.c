#include "decls.h"
#include "imports.h"

// entry: 0043dee0
// name : stock_strdup
// size : 38
// sig  : char * stock_strdup(char * src)


/* Library Function - Single Match
    __strdup
   
   Library: Visual Studio 1998 Release */

char * __cdecl stock_strdup(char *src)

{
  uint len;
  char *dest;
  char *copy;
  
  len = stock_strlen(src);
  dest = stock_malloc(len + 1);
  copy = (char *)0x0;
  if (dest != (char *)0x0) {
    copy = stock_strcpy(dest,src);
  }
  return copy;
}



