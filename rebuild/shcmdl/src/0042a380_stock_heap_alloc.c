#include "decls.h"
#include "imports.h"

// entry: 0042a380
// name : stock_heap_alloc
// size : 21
// sig  : void * __cdecl stock_heap_alloc(uint size)


int * __cdecl stock_heap_alloc(uint size)

{
  LPVOID pvVar1;
  
  pvVar1 = HeapAlloc(stock_crtheap,0,size);
  return pvVar1;
}
