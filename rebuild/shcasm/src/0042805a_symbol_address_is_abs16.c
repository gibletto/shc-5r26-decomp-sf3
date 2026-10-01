#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0042805a
// name : symbol_address_is_abs16
// size : 156
// sig  : int symbol_address_is_abs16(short labno)


int __cdecl symbol_address_is_abs16(short labno)

{
  symbol *sym;
  int is_abs16;
  
  is_abs16 = 0;
  if (g_current_request->abs16 == '\x03') {
    is_abs16 = 1;
  }
  else if ((labno < 0xb7) && ((g_current_request->abs16 & 1) != 0)) {
    is_abs16 = 1;
  }
  else if (0xb6 < labno) {
    sym = find_symbol_by_id(labno);
    if ((sym->attr & 0x20) != 0) {
      is_abs16 = 1;
    }
  }
  return is_abs16;
}



