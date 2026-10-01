#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_pnhHeap
#define stock_pnhHeap (*(int (**)())(g_sd + 0xc560))


// entry: 004364f0
// name : stock_callnewh
// size : 33
// sig  : int stock_callnewh(uint size)


int __cdecl stock_callnewh(uint size)

{
  int handled;
  
  if (stock_pnhHeap != 0) {
    handled = (*stock_pnhHeap)(size);
    if (handled != 0) {
      return 1;
    }
  }
  return 0;
}



