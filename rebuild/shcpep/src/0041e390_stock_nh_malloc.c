#include "decls.h"
#include "imports.h"

// entry: 0041e390
// name : stock_nh_malloc
// size : 64
// sig  : void * stock_nh_malloc(uint size, int call_new_handler)


int * __cdecl stock_nh_malloc(uint size,int call_new_handler)

{
  void *block;
  int retry;
  
  if (0xffffffe0 < size) {
    return (void *)0x0;
  }
  if (size == 0) {
    size = 1;
  }
  while( true ) {
    block = stock_heap_alloc(size);
    if (block != (void *)0x0) {
      return block;
    }
    if (call_new_handler == 0) break;
    retry = stock_callnewh(size);
    if (retry == 0) {
      return (void *)0x0;
    }
  }
  return (void *)0x0;
}



