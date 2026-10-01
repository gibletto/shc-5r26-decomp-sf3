#include "decls.h"
#include "imports.h"

// entry: 00436520
// name : stock_heap_init
// size : 21
// sig  : void stock_heap_init(void)


int __cdecl stock_heap_init(void)

{
  stock_crtheap = HeapCreate(1,0x1000,0);
  return;
}
