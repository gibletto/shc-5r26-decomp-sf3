#include "decls.h"
#include "imports.h"

// entry: 0041e3f0
// name : stock_free
// size : 24
// sig  : void __cdecl stock_free(void *p)


int __cdecl stock_free(void *p)

{
  if (p != (void *)0x0) {
    HeapFree(stock_crtheap,0,p);
  }
  return;
}
