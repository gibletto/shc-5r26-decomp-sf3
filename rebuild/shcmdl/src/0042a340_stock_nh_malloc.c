#include "decls.h"
#include "imports.h"

// entry: 0042a340
// name : stock_nh_malloc
// size : 64
// sig  : int stock_nh_malloc(uint size, int nhflag)


int __cdecl stock_nh_malloc(uint size,int nhflag)

{
  void *pvVar1;
  int iVar2;
  
  if (0xffffffe0 < size) {
    return 0;
  }
  if (size == 0) {
    size = 1;
  }
  while( true ) {
    pvVar1 = stock_heap_alloc(size);
    if (pvVar1 != (void *)0x0) {
      return (int)pvVar1;
    }
    if (nhflag == 0) break;
    iVar2 = stock_callnewh(size);
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 0;
}



