#include "decls.h"
#include "imports.h"

// entry: 004221a0
// name : _strtoul
// size : 26
// sig  : ulong _strtoul(char * _Str, char * * _EndPtr, int _Radix)


/* Library Function - Single Match
    _strtoul
   
   Library: Visual Studio 1998 Release */

ulong __cdecl _strtoul(char *_Str,char **_EndPtr,int _Radix)

{
  uint uVar1;
  
  uVar1 = stock_strtoxl((byte *)_Str,_EndPtr,_Radix,1);
  return uVar1;
}



