#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))


// entry: 00409c50
// name : get_symbol_attr_bit5_or_forced
// size : 76
// sig  : int get_symbol_attr_bit5_or_forced(short labno)


int __cdecl get_symbol_attr_bit5_or_forced(short labno)

{
  int rc;
  
  rc = 0;
  if ((g_current_request->abs16 != 3) && (((g_current_request->abs16 & 1) == 0 || (0xb6 < labno))))
  {
    g_current_symbol = find_label_symbol(labno);
    if ((g_current_symbol != (symbol *)0x0) && ((g_current_symbol->attr & 0x20) != 0)) {
      rc = 1;
    }
    return rc;
  }
  return 1;
}



