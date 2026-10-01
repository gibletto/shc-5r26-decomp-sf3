#include "decls.h"
#include "imports.h"

// entry: 00435290
// name : stock_free
// size : 24
// sig  : void __cdecl stock_free(void *block)


int __cdecl stock_free(void *block)

{
  if (block != (void *)0x0) {
    HeapFree(stock_crtheap,0,block);
  }
  return;
}
