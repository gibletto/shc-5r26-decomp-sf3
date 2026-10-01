#include "decls.h"
#include "imports.h"

// entry: 00439410
// name : _strtoul
// size : 26
// sig  : ulong _strtoul(char * _Str, char * * _EndPtr, int _Radix)


/* Library Function - Single Match
    _strtoul
   
   Library: Visual Studio 1998 Release */

ulong __cdecl _strtoul(char *_Str,char **_EndPtr,int _Radix)

{
  uint result;
  
  result = stock_strtoxl((byte *)_Str,_EndPtr,_Radix,1);
  return result;
}



