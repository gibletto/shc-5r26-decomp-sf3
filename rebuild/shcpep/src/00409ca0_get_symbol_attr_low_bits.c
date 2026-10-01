#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))


// entry: 00409ca0
// name : get_symbol_attr_low_bits
// size : 36
// sig  : uint get_symbol_attr_low_bits(short labno)


uint __cdecl get_symbol_attr_low_bits(short labno)

{
  uint attr_bits;
  
  attr_bits = 0;
  g_current_symbol = find_label_symbol(labno);
  if (g_current_symbol != (symbol *)0x0) {
    attr_bits = g_current_symbol->attr & 3;
  }
  return attr_bits;
}



