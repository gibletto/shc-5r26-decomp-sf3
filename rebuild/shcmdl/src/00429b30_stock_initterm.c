#include "decls.h"
#include "imports.h"

// entry: 00429b30
// name : stock_initterm
// size : 32
// sig  : void stock_initterm(void * begin, void * end)


int __cdecl stock_initterm(void *begin,void *end)

{
  for (; begin < end; begin = (void *)((int)begin + 4)) {
    if (*(code **)begin != 0) {
      (**(code **)begin)();
    }
  }
  return;
}



