#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00420100
// name : new_symbol_number
// size : 47
// sig  : int new_symbol_number(void)


int __cdecl new_symbol_number(void)

{
  int *counter;
  int rc;
  
  counter = &g_options->symbol_count;
  if (*counter < (int)g_symbol_limit) {
    g_inline_new_symbols = g_inline_new_symbols + 1;
    *counter = *counter + 1;
    return CONCAT22((short)((uint)g_options >> 0x10),(short)g_options->symbol_count);
  }
  rc = abort_function_optimization();
  return rc;
}



