#include "decls.h"
#include "imports.h"

// entry: 0042a320
// name : stock_malloc
// size : 20
// sig  : void * __cdecl stock_malloc(uint size)


int * __cdecl stock_malloc(uint size)

{
  void *pvVar1;
  
  pvVar1 = (void *)stock_nh_malloc(size,stock_newmode);
  return pvVar1;
}
