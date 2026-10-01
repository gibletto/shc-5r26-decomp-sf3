#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00409610
// name : set_symbol_address_from_location_counter
// size : 152
// sig  : void set_symbol_address_from_location_counter(void)


int __cdecl set_symbol_address_from_location_counter(void)

{
  uint sym_index;
  int sym;
  uint uVar1;
  
  sym_index = (uint)g_sud_symx;
  uVar1 = (int)sym_index >> 0x1f;
  if ((g_symbol_table[sym_index].attr & 1) != 0) {
    g_symbol_table[(sym_index ^ uVar1) - uVar1].frame_offset = g_current_section->data_loc;
    return;
  }
  if ((g_symbol_table[sym_index].attr & 2) != 0) {
    g_symbol_table[(sym_index ^ uVar1) - uVar1].frame_offset = g_current_section->data_loc;
    return;
  }
  sym = (sym_index ^ uVar1) - uVar1;
  if (((g_symbol_table[sym].type & 1) != 0) && ((g_symbol_table[sym].type & 2) == 0)) {
    g_symbol_table[sym].frame_offset = g_current_section->const_loc;
    return;
  }
  g_symbol_table[sym].frame_offset = g_current_section->data_loc;
  return;
}



