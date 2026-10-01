#include "decls.h"
#include "imports.h"

// entry: 004081f0
// name : regalloc_alloc
// size : 29
// sig  : void * regalloc_alloc(uint size)


int * __cdecl regalloc_alloc(uint size)

{
  void *mem;
  
  mem = pool_alloc(size);
  if (mem == (void *)0x0) {
    abort_function_optimization();
  }
  return mem;
}



