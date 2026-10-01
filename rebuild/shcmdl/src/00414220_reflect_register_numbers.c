#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_mem_freq_list
#define g_mem_freq_list (*(mem_freq * *)(g_sd + 0x164a0))


// entry: 00414220
// name : reflect_register_numbers
// size : 319
// sig  : void reflect_register_numbers(void)


int __cdecl reflect_register_numbers(void)

{
  mem_freq *pmVar1;
  int mem_no;
  mem_freq *cur;
  int merged;
  short pregno;
  
  pmVar1 = g_mem_freq_list->next;
  cur = g_mem_freq_list;
  while (pmVar1 != (mem_freq *)0x0) {
    if ((cur->merge_next == 0) && (cur->merge_prev == 0)) {
      pregno = cur->pregno;
      for (pmVar1 = cur->next; pmVar1 != (mem_freq *)0x0; pmVar1 = pmVar1->next) {
        if (pmVar1->pregno == pregno) {
          cur->freq = cur->freq + pmVar1->freq;
          if (cur->merge_next != 0) {
            *(mem_freq **)(cur->merge_next + 0x18) = pmVar1;
            pmVar1->merge_next = cur->merge_next;
          }
          cur->merge_next = (int)pmVar1;
          pmVar1->merge_prev = (int)cur;
        }
      }
    }
    cur = cur->next;
    pmVar1 = cur->next;
  }
  mem_no = -1;
  sort_reflect_list_by_frequency();
  pmVar1 = g_mem_freq_list;
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
    FID_conflict__wprintf(s__________reflect_start__________004355f0);
    for (pmVar1 = g_mem_freq_list; pmVar1 != (mem_freq *)0x0; pmVar1 = pmVar1->next) {
      pregno = pmVar1->lreg->pregno;
      if (pregno < 0) {
        FID_conflict__wprintf(&g_fmt_3d,(int)pregno);
      }
    }
    FID_conflict__wprintf(&g_str_newline);
    pmVar1 = g_mem_freq_list;
  }
  for (; pmVar1 != (mem_freq *)0x0; pmVar1 = pmVar1->next) {
    if (pmVar1->merge_prev == 0) {
      pmVar1->mem_number = mem_no;
      pmVar1->lreg->pregno = (short)mem_no;
      for (merged = pmVar1->merge_next; merged != 0; merged = *(int *)(merged + 0x14)) {
        *(int *)(merged + 4) = mem_no;
        **(short **)(merged + 0x10) = (short)mem_no;
      }
    }
    mem_no = mem_no + -1;
  }
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
    FID_conflict__wprintf(s__________reflect_end__________004355c8);
    for (pmVar1 = g_mem_freq_list; pmVar1 != (mem_freq *)0x0; pmVar1 = pmVar1->next) {
      pregno = pmVar1->lreg->pregno;
      if (pregno < 0) {
        FID_conflict__wprintf(&g_fmt_3d,(int)pregno);
      }
    }
    FID_conflict__wprintf(&g_str_newline);
  }
  sort_lregs_by_mreg();
  return;
}



