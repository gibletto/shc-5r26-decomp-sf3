#include "decls.h"
#include "imports.h"

// entry: 0043a550
// name : stock_malloc
// size : 20
// sig  : void * stock_malloc(uint size)


int * __cdecl stock_malloc(uint size)

{
  void *block;
  
  block = stock_nh_malloc(size,stock_newmode);
  return block;
}



