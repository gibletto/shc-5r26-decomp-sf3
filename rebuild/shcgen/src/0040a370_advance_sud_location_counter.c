#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040a370
// name : advance_sud_location_counter
// size : 122
// sig  : void advance_sud_location_counter(int size)


int __cdecl advance_sud_location_counter(int size)

{
  uint uVar1;
  uint *loc_ptr;
  uint cur_loc;
  
  uVar1 = (uint)g_sud_symx;
  if (((((g_symbol_table[uVar1].attr & 1) == 0) && ((g_symbol_table[uVar1].attr & 2) == 0)) &&
      ((g_symbol_table[(uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)].type & 1) != 0)) &&
     ((g_symbol_table[(uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)].type & 2) == 0)) {
    loc_ptr = &g_current_section->const_loc;
  }
  else {
    loc_ptr = &g_current_section->data_loc;
  }
  uVar1 = *loc_ptr;
  cur_loc = *loc_ptr;
  *loc_ptr = size + cur_loc;
  if (size + cur_loc < uVar1) {
    report_codegen_message(0xc81,1,0,0,(char *)0x0);
  }
  return;
}



