#include "decls.h"
#include "imports.h"

// entry: 0042a2b0
// name : stock_realloc
// size : 111
// sig  : void * stock_realloc(void * ptr, uint size)


int * __cdecl stock_realloc(void *ptr,uint size)

{
  void *pvVar1;
  LPVOID pvVar2;
  int iVar3;
  
  if (ptr == (void *)0x0) {
    pvVar1 = stock_malloc(size);
    return pvVar1;
  }
  if (size != 0) {
    do {
      if (size < 0xffffffe1) {
        pvVar2 = HeapReAlloc(stock_crtheap,0,ptr,size);
      }
      else {
        pvVar2 = (LPVOID)0x0;
      }
      if (pvVar2 != (LPVOID)0x0) {
        return pvVar2;
      }
      if (stock_newmode == 0) {
        return (void *)0x0;
      }
      iVar3 = stock_callnewh(size);
    } while (iVar3 != 0);
    return (void *)0x0;
  }
  stock_free(ptr);
  return (void *)0x0;
}



