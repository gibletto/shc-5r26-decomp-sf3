#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042ba50
// name : get_symbol_attr_low_bits
// size : 70
// sig  : uchar get_symbol_attr_low_bits(short labno)


uchar __cdecl get_symbol_attr_low_bits(short labno)

{
  uint idx;
  
  idx = (uint)labno;
  if (*(int *)g_request->unknown_0b0 + 0xb6 < (int)idx) {
    return '\0';
  }
  if ((g_symbol_table[(idx ^ (int)idx >> 0x1f) - ((int)idx >> 0x1f)].attr & 1) != 0) {
    return '\x01';
  }
  return g_symbol_table[(idx ^ (int)idx >> 0x1f) - ((int)idx >> 0x1f)].attr & 2;
}



