#include "decls.h"
#include "imports.h"

// entry: 0042df70
// name : stock_strdup
// size : 38
// sig  : char * stock_strdup(char * src)


/* Library Function - Single Match
    __strdup
   
   Library: Visual Studio 1998 Release */

char * __cdecl stock_strdup(char *src)

{
  uint uVar1;
  char *dst;
  char *pcVar2;
  
  uVar1 = stock_strlen(src);
  dst = stock_malloc(uVar1 + 1);
  pcVar2 = (char *)0x0;
  if (dst != (char *)0x0) {
    pcVar2 = stock_strcpy(dst,src);
  }
  return pcVar2;
}



