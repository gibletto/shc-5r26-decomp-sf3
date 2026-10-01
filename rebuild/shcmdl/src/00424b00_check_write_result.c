#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 00424b00
// name : check_write_result
// size : 43
// sig  : void check_write_result(int result)


int __cdecl check_write_result(int result)

{
  if (result == -1) {
    write_error_record(g_options_for_errors->source_name,0,0xce7,(char *)0x0);
    stock_exit(9);
  }
  return;
}



