#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042b9e0
// name : get_symbol_attr_bit5_or_forced
// size : 99
// sig  : char get_symbol_attr_bit5_or_forced(short labno)


char __cdecl get_symbol_attr_bit5_or_forced(short labno)

{
  uint idx;
  
  if (g_request->abs16 == 3) {
    return '\x01';
  }
  if (((g_request->abs16 & 1) != 0) && (labno < 0xb7)) {
    return '\x01';
  }
  idx = (uint)labno;
  if (*(int *)g_request->unknown_0b0 + 0xb6 < (int)idx) {
    return '\0';
  }
  return '\x01' - ((g_symbol_table[(idx ^ (int)idx >> 0x1f) - ((int)idx >> 0x1f)].attr & 0x20) == 0)
  ;
}



