#include "decls.h"
#include "imports.h"

// entry: 0043a5b0
// name : stock_heap_alloc
// size : 21
// sig  : void * stock_heap_alloc(uint size)


int * __cdecl stock_heap_alloc(uint size)

{
  LPVOID block;
  
  block = HeapAlloc(stock_crtheap,0,size);
  return block;
}



