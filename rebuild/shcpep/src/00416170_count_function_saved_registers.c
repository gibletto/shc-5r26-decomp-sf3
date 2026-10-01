#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 00416170
// name : count_function_saved_registers
// size : 134
// sig  : short count_function_saved_registers(void)


short __cdecl count_function_saved_registers(void)

{
  short count;
  byte bit;
  
  count = 0;
  bit = 0;
  do {
    if (((int)g_aux_record_table[g_current_aux_index].saved_regs & 1 << (bit & 0x1f)) != 0) {
      count = count + 1;
    }
    bit = bit + 1;
  } while ((char)bit < '\x10');
  bit = 0;
  do {
    if (((int)(char)g_aux_record_table[g_current_aux_index].saved_mac & 1 << (bit & 0x1f)) != 0) {
      count = count + 1;
    }
    bit = bit + 1;
  } while ((char)bit < '\x02');
  bit = 0;
  do {
    if (((int)g_aux_record_table[g_current_aux_index].saved_regs2 & 1 << (bit & 0x1f)) != 0) {
      count = count + 1;
    }
    bit = bit + 1;
  } while ((char)bit < '\x10');
  bit = 0;
  do {
    if (((int)(char)g_aux_record_table[g_current_aux_index].saved_sys & 1 << (bit & 0x1f)) != 0) {
      count = count + 1;
    }
    bit = bit + 1;
  } while ((char)bit < '\x02');
  return count;
}



