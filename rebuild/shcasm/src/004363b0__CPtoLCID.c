#include "decls.h"
#include "imports.h"

// entry: 004363b0
// name : _CPtoLCID
// size : 56
// sig  : undefined4 _CPtoLCID(undefined4 param_1)


/* Library Function - Single Match
    _CPtoLCID
   
   Library: Visual Studio 1998 Release */

undefined4 __cdecl _CPtoLCID(undefined4 param_1)

{
  switch(param_1) {
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



