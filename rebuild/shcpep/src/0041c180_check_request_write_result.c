#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x6e34))


// entry: 0041c180
// name : check_request_write_result
// size : 43
// sig  : void check_request_write_result(int result)


int __cdecl check_request_write_result(int result)

{
  if (result == -1) {
    report_message_by_code(g_loaded_request->source_name,0,0xce7,(char *)0x0);
    stock_exit(9);
  }
  return;
}



