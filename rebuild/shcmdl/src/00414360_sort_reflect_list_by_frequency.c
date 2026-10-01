#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_mem_freq_list
#define g_mem_freq_list (*(mem_freq * *)(g_sd + 0x164a0))


// entry: 00414360
// name : sort_reflect_list_by_frequency
// size : 216
// sig  : void sort_reflect_list_by_frequency(void)


int __cdecl sort_reflect_list_by_frequency(void)

{
  mem_freq *pmVar1;
  mem_freq *cur;
  mem_freq *next;
  mem_freq *prev;
  bool swapped;
  
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
    FID_conflict__wprintf(s__________freqsort_start__________00435634);
    for (pmVar1 = g_mem_freq_list; pmVar1 != (mem_freq *)0x0; pmVar1 = pmVar1->next) {
      FID_conflict__wprintf(&g_fmt_3d,pmVar1->freq);
    }
    FID_conflict__wprintf(&g_str_newline);
  }
  do {
    swapped = false;
    pmVar1 = (mem_freq *)0x0;
    next = g_mem_freq_list;
    prev = g_mem_freq_list;
    while (cur = next, cur != (mem_freq *)0x0) {
      if (prev->freq < cur->freq) {
        swapped = true;
        next = cur;
        if (g_mem_freq_list != prev) {
          pmVar1->next = cur;
          next = g_mem_freq_list;
        }
        g_mem_freq_list = next;
        prev->next = cur->next;
        cur->next = prev;
      }
      pmVar1 = prev;
      prev = cur;
      next = cur->next;
    }
  } while (swapped);
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
    FID_conflict__wprintf(s__________freqsort_end__________00435614);
    for (pmVar1 = g_mem_freq_list; pmVar1 != (mem_freq *)0x0; pmVar1 = pmVar1->next) {
      FID_conflict__wprintf(&g_fmt_3d,pmVar1->freq);
    }
    FID_conflict__wprintf(&g_str_newline);
  }
  return;
}



