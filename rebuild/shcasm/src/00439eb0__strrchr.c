#include "decls.h"
#include "imports.h"

// entry: 00439eb0
// name : _strrchr
// size : 39
// sig  : char * _strrchr(char * _Str, int _Ch)


/* Library Function - Single Match
    _strrchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strrchr(char *_Str,int _Ch)

{
  int iVar1;
  char *found;
  char *scan;
  char ch;
  
  iVar1 = -1;
  do {
    scan = _Str;
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    scan = _Str + 1;
    ch = *_Str;
    _Str = scan;
  } while (ch != '\0');
  iVar1 = -(iVar1 + 1);
  scan = scan + -1;
  do {
    found = scan;
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    found = scan + -1;
    ch = *scan;
    scan = found;
  } while ((char)_Ch != ch);
  found = found + 1;
  if (*found != (char)_Ch) {
    found = (char *)0x0;
  }
  return found;
}



