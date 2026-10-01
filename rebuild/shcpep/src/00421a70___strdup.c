#include "decls.h"
#include "imports.h"

// entry: 00421a70
// name : __strdup
// size : 38
// sig  : char * __strdup(char * _Src)


/* Library Function - Single Match
    __strdup
   
   Library: Visual Studio 1998 Release */

char * __cdecl __strdup(char *_Src)

{
  char *pcVar1;
  char *_Dest;
  
  pcVar1 = stock_strlen((uint *)_Src);
  _Dest = stock_malloc((uint)(pcVar1 + 1));
  pcVar1 = (char *)0x0;
  if (_Dest != (char *)0x0) {
    pcVar1 = FID_conflict___mbscpy(_Dest,_Src);
  }
  return pcVar1;
}



