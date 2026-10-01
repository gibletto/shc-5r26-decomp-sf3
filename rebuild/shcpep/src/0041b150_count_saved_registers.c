#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 0041b150
// name : count_saved_registers
// size : 130
// sig  : short count_saved_registers(short aux_index)


short __cdecl count_saved_registers(short aux_index)

{
  short count;
  short n;
  ushort bit;
  ushort saved_mask;
  
  bit = 1;
  n = 0x10;
  count = 0;
  saved_mask = g_aux_record_table[aux_index].saved_regs;
  do {
    if ((bit & saved_mask) != 0) {
      count = count + 1;
    }
    if ((bit & g_aux_record_table[aux_index].saved_regs2) != 0) {
      count = count + 1;
    }
    bit = bit * 2;
    n = n + -1;
  } while (n != 0);
  if (((g_aux_record_table[aux_index].flags & 0x4000) != 0) &&
     ((g_aux_record_table[aux_index].flags & 0x1800) != 0)) {
    if ((saved_mask & 0x8000) != 0) {
      count = count + -1;
    }
    if ((saved_mask & 1) != 0) {
      count = count + -1;
    }
  }
  if ((g_aux_record_table[aux_index].saved_mac & 2) != 0) {
    count = count + 1;
  }
  if ((g_aux_record_table[aux_index].saved_mac & 1) != 0) {
    count = count + 1;
  }
  if ((g_aux_record_table[aux_index].saved_sys & 1) != 0) {
    count = count + 1;
  }
  if ((g_aux_record_table[aux_index].saved_sys & 2) != 0) {
    count = count + 1;
  }
  return count;
}



