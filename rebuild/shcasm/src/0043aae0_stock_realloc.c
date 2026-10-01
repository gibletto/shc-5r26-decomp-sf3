#include "decls.h"
#include "imports.h"

// entry: 0043aae0
// name : stock_realloc
// size : 111
// sig  : void * stock_realloc(void * block, uint size)


int * __cdecl stock_realloc(void *block,uint size)

{
  void *fresh;
  LPVOID new_block;
  int retry;
  
  if (block == (void *)0x0) {
    fresh = stock_malloc(size);
    return fresh;
  }
  if (size != 0) {
    do {
      if (size < 0xffffffe1) {
        new_block = HeapReAlloc(stock_crtheap,0,block,size);
      }
      else {
        new_block = (LPVOID)0x0;
      }
      if (new_block != (LPVOID)0x0) {
        return new_block;
      }
      if (stock_newmode == 0) {
        return (void *)0x0;
      }
      retry = stock_callnewh(size);
    } while (retry != 0);
    return (void *)0x0;
  }
  stock_free(block);
  return (void *)0x0;
}



