#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))


// entry: 00403590
// name : compute_lreg_profits
// size : 61
// sig  : void compute_lreg_profits(void)


int __cdecl compute_lreg_profits(void)

{
  int avg;
  int nclash;
  undefined4 *clash;
  lreg *reg;
  
  for (reg = g_lreg_list; reg != (lreg *)0x0; reg = reg->next) {
    avg = 0;
    nclash = 0;
    for (clash = reg->clashed; clash != (undefined4 *)0x0; clash = (undefined4 *)*clash) {
      nclash = nclash + 1;
      avg = avg + *(int *)(clash[1] + 4);
    }
    if (nclash != 0) {
      avg = avg / nclash;
    }
    reg->profit = reg->priori - avg;
  }
  return;
}



