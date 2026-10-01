#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))


// entry: 0041a9c0
// name : sort_lregs_by_profit
// size : 54
// sig  : void sort_lregs_by_profit(void)


int __cdecl sort_lregs_by_profit(void)

{
  lreg **slot;
  lreg *lr;
  int n;
  
  n = 1;
  if (g_lreg_list != (lreg *)0x0) {
    slot = g_lreg_table;
    lr = g_lreg_list;
    do {
      slot = slot + 1;
      *slot = lr;
      n = n + 1;
      lr = lr->next;
    } while (lr != (lreg *)0x0);
  }
  g_lreg_count = n + -1;
  sort_lregs(1,2,g_lreg_count);
  return;
}



