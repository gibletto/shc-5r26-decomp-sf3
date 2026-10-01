#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))


// entry: 0042ec79
// name : count_saved_registers
// size : 396
// sig  : short count_saved_registers(short aux_index)


short __cdecl count_saved_registers(short aux_index)

{
  ushort bit;
  short reg_no;
  short saved_count;
  ushort reg_mask;
  
  reg_mask = g_aux_record_table[aux_index].saved_regs;
  bit = 1;
  saved_count = 0;
  for (reg_no = 0; reg_no < 0x10; reg_no = reg_no + 1) {
    if ((bit & reg_mask) != 0) {
      saved_count = saved_count + 1;
    }
    if ((bit & g_aux_record_table[aux_index].saved_regs2) != 0) {
      saved_count = saved_count + 1;
    }
    bit = bit << 1;
  }
  if (((g_aux_record_table[aux_index].flags & 0x4000) != 0) &&
     ((g_aux_record_table[aux_index].flags & 0x1800) != 0)) {
    if (((int)(short)reg_mask & 0x8000U) != 0) {
      saved_count = saved_count + -1;
    }
    if ((reg_mask & 1) != 0) {
      saved_count = saved_count + -1;
    }
  }
  if ((g_aux_record_table[aux_index].saved_mac & 2) != 0) {
    saved_count = saved_count + 1;
  }
  if ((g_aux_record_table[aux_index].saved_mac & 1) != 0) {
    saved_count = saved_count + 1;
  }
  if ((g_aux_record_table[aux_index].saved_sys & 1) != 0) {
    saved_count = saved_count + 1;
  }
  if ((g_aux_record_table[aux_index].saved_sys & 2) != 0) {
    saved_count = saved_count + 1;
  }
  return saved_count;
}



