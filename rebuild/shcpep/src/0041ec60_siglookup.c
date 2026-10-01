#include "decls.h"
#include "imports.h"

// entry: 0041ec60
// name : siglookup
// size : 49
// sig  : uint siglookup(int signum)


/* Library Function - Single Match
    _siglookup
   
   Library: Visual Studio 1998 Release */

uint __cdecl siglookup(int signum)

{
  undefined *puVar1;
  
  puVar1 = &stock_XcptActTab;
  do {
    if (*(int *)(puVar1 + 4) == signum) break;
    puVar1 = puVar1 + 0xc;
  } while (puVar1 < &stock_XcptActTab + stock_XcptActTabCount * 0xc);
  return -(uint)(*(int *)(puVar1 + 4) == signum) & (uint)puVar1;
}



