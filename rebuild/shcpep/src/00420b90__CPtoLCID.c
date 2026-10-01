#include "decls.h"
#include "imports.h"

// entry: 00420b90
// name : _CPtoLCID
// size : 56
// sig  : int _CPtoLCID(int codepage)


/* Library Function - Single Match
    _CPtoLCID
   
   Library: Visual Studio 1998 Release */

int __cdecl _CPtoLCID(int codepage)

{
  switch(codepage) {
  case 0x3a4:
    return 0x411;
  default:
    return 0;
  case 0x3a8:
    return 0x804;
  case 0x3b5:
    return 0x412;
  case 0x3b6:
    return 0x404;
  }
}



