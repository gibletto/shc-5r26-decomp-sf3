#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_pnhHeap
#define stock_pnhHeap (*(int (**)())(g_sd + 0x5458))


// entry: 0041fdf0
// name : stock_callnewh
// size : 33
// sig  : int stock_callnewh(uint size)


int __cdecl stock_callnewh(uint size)

{
  int iVar1;
  
  if (stock_pnhHeap != 0) {
    iVar1 = (*stock_pnhHeap)(size);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}



