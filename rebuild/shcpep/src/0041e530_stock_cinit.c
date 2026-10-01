#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_fpinit
#define stock_fpinit (*(int (**)())(g_sd + 0x7f68))


// entry: 0041e530
// name : stock_cinit
// size : 48
// sig  : void stock_cinit(void)


int __cdecl stock_cinit(void)

{
  if (stock_fpinit != 0) {
    (*stock_fpinit)();
  }
  stock_initterm((undefined4 *)&stock_xi_a,(undefined4 *)&stock_xi_z);
  stock_initterm((undefined4 *)&stock_xc_a,(undefined4 *)&stock_xc_z);
  return;
}



