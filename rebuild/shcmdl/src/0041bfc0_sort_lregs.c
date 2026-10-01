#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 0041bfc0
// name : sort_lregs
// size : 285
// sig  : void sort_lregs(int pivot, int lo, int hi)


int __cdecl sort_lregs(int pivot,int lo,int hi)

{
  lreg *plVar1;
  lreg **slot;
  int i;
  int j;
  int pivot_profit;
  lreg **probe;
  int profit;
  lreg *swap;
  
  do {
    if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
      i = 1;
      FID_conflict__wprintf(s_lregsort__d__d__d__00435b44,pivot,lo,hi);
      if (0 < g_lreg_count) {
        slot = g_lreg_table;
        do {
          slot = slot + 1;
          i = i + 1;
          FID_conflict__wprintf(&g_fmt_3d,(*slot)->profit);
        } while (i <= g_lreg_count);
      }
      FID_conflict__wprintf(&g_str_newline);
    }
    if (hi < lo) {
      return;
    }
    j = hi;
    i = lo;
    do {
      plVar1 = g_lreg_table[pivot];
      slot = g_lreg_table + i;
      pivot_profit = plVar1->profit;
      profit = (*slot)->profit;
      while (pivot_profit < profit) {
        if (j <= i) goto LAB_0041c0a3;
        probe = slot + 1;
        slot = slot + 1;
        i = i + 1;
        profit = (*probe)->profit;
      }
      slot = g_lreg_table + j;
      if ((*slot)->profit <= pivot_profit) {
LAB_0041c076:
        if (i < j) goto code_r0x0041c07a;
        i = i + -1;
LAB_0041c0a3:
        swap = g_lreg_table[i];
        g_lreg_table[i] = plVar1;
        g_lreg_table[pivot] = swap;
        break;
      }
LAB_0041c086:
      plVar1 = g_lreg_table[i];
      g_lreg_table[i] = g_lreg_table[j];
      g_lreg_table[j] = plVar1;
    } while (i <= j);
    sort_lregs(pivot,lo,i);
    lo = j + 1;
    pivot = j;
  } while( true );
code_r0x0041c07a:
  probe = slot + -1;
  slot = slot + -1;
  j = j + -1;
  if (pivot_profit < (*probe)->profit) goto LAB_0041c086;
  goto LAB_0041c076;
}



