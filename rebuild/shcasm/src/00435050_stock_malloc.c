#include "decls.h"
#include "imports.h"

// entry: 00435050
// name : stock_malloc
// size : 20
// sig  : void * __cdecl stock_malloc(uint size)


int * __cdecl stock_malloc(uint size)

{
  void *block;
  
  block = stock_nh_malloc(size,stock_newmode);
  return block;
}
