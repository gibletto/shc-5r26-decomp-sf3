#include "decls.h"
#include "imports.h"

// entry: 0042a290
// name : stock_free
// size : 24
// sig  : int __cdecl stock_free(void *ptr)


int __cdecl stock_free(void *ptr)

{
  int iVar1;
  
  iVar1 = 0;
  if (ptr != (void *)0x0) {
    iVar1 = HeapFree(stock_crtheap,0,ptr);
  }
  return iVar1;
}
