#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_mem_freq_list
#define g_mem_freq_list (*(mem_freq * *)(g_sd + 0x164a0))


// entry: 0041cda0
// name : collect_memory_frequencies
// size : 87
// sig  : void collect_memory_frequencies(void)


int __cdecl collect_memory_frequencies(void)

{
  int freq;
  lreg **slot;
  int i;
  
  g_mem_freq_list = (mem_freq *)0x0;
  i = 1;
  g_mem_lreg_count = 0;
  if (0 < g_lreg_count) {
    slot = g_lreg_table;
    do {
      slot = slot + 1;
      freq = 0;
      if ((*slot)->pregno < 0) {
        g_mem_lreg_count = g_mem_lreg_count + 1;
        freq = memory_lreg_frequency(*slot);
      }
      if (0 < freq) {
        add_memory_frequency_record(*slot,freq);
      }
      i = i + 1;
    } while (i <= g_lreg_count);
  }
  return;
}



