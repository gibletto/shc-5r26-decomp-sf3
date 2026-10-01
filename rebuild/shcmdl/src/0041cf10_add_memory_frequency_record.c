#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_mem_freq_list
#define g_mem_freq_list (*(mem_freq * *)(g_sd + 0x164a0))


// entry: 0041cf10
// name : add_memory_frequency_record
// size : 123
// sig  : void add_memory_frequency_record(lreg * lr, int freq)


int __cdecl add_memory_frequency_record(lreg *lr,int freq)

{
  mem_freq *old_head;
  
  old_head = g_mem_freq_list;
  if (g_mem_freq_list == (mem_freq *)0x0) {
    g_mem_freq_list = regalloc_alloc(0x1c);
    g_mem_freq_list->next = (mem_freq *)0x0;
  }
  else {
    g_mem_freq_list = regalloc_alloc(0x1c);
    g_mem_freq_list->next = old_head;
  }
  g_mem_freq_list->freq = freq;
  g_mem_freq_list->lreg = lr;
  g_mem_freq_list->mem_number = 0;
  g_mem_freq_list->pregno = lr->pregno;
  g_mem_freq_list->merge_next = 0;
  g_mem_freq_list->merge_prev = 0;
  return;
}



