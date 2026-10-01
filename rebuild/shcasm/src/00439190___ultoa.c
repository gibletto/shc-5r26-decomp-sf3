#include "decls.h"
#include "imports.h"

// entry: 00439190
// name : __ultoa
// size : 30
// sig  : char * __ultoa(ulong _Value, char * _Dest, int _Radix)


/* Library Function - Single Match
    __ultoa
   
   Library: Visual Studio 1998 Release */

char * __cdecl __ultoa(ulong _Value,char *_Dest,int _Radix)

{
  xtoa(_Value,_Dest,_Radix,0);
  return _Dest;
}



