#include "decls.h"
#include "imports.h"

// entry: 00435e80
// name : siglookup
// size : 49
// sig  : uint siglookup(int param_1)


/* Library Function - Single Match
    _siglookup
   
   Library: Visual Studio 1998 Release */

uint __cdecl siglookup(int param_1)

{
  undefined *act;
  
  act = &stock_XcptActTab;
  do {
    if (*(int *)(act + 4) == param_1) break;
    act = act + 0xc;
  } while (act < &stock_XcptActTab + stock_XcptActTabCount * 0xc);
  return -(uint)(*(int *)(act + 4) == param_1) & (uint)act;
}



