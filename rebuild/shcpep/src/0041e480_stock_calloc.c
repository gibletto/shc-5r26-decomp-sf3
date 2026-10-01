#include "decls.h"
#include "imports.h"

// entry: 0041e480
// name : stock_calloc
// size : 82
// sig  : void * stock_calloc(int count, int size)


int * __cdecl stock_calloc(int count,int size)

{
  LPVOID block;
  int retry;
  uint bytes;
  
  bytes = count * size;
  if (bytes == 0) {
    bytes = 1;
  }
  do {
    if (bytes < 0xffffffe1) {
      block = HeapAlloc(stock_crtheap,8,bytes);
    }
    else {
      block = (LPVOID)0x0;
    }
    if (block != (LPVOID)0x0) {
      return block;
    }
    if (stock_newmode == 0) {
      return (void *)0x0;
    }
    retry = stock_callnewh(bytes);
  } while (retry != 0);
  return (void *)0x0;
}



