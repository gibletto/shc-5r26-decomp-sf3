#include "decls.h"
#include "imports.h"

// entry: 00438ce0
// name : __strdup
// size : 38
// sig  : char * __strdup(char * _Src)


/* Library Function - Single Match
    __strdup
   
   Library: Visual Studio 1998 Release */

char * __cdecl __strdup(char *_Src)

{
  uint len;
  uint *copy;
  uint *result;
  
  len = stock_strlen(_Src);
  copy = stock_malloc(len + 1);
  result = (uint *)0x0;
  if (copy != (uint *)0x0) {
    result = stock_strcpy(copy,(uint *)_Src);
  }
  return (char *)result;
}



