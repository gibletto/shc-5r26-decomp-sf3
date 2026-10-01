#include "decls.h"
#include "imports.h"

// entry: 0042a0e0
// name : stock_calloc
// size : 82
// sig  : void * stock_calloc(int count, int size)


int * __cdecl stock_calloc(int count,int size)

{
  LPVOID pvVar1;
  int iVar2;
  uint dwBytes;
  
  dwBytes = count * size;
  if (dwBytes == 0) {
    dwBytes = 1;
  }
  do {
    if (dwBytes < 0xffffffe1) {
      pvVar1 = HeapAlloc(stock_crtheap,8,dwBytes);
    }
    else {
      pvVar1 = (LPVOID)0x0;
    }
    if (pvVar1 != (LPVOID)0x0) {
      return pvVar1;
    }
    if (stock_newmode == 0) {
      return (void *)0x0;
    }
    iVar2 = stock_callnewh(dwBytes);
  } while (iVar2 != 0);
  return (void *)0x0;
}



