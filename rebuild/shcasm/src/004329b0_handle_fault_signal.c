#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x13320))
#undef g_request_record_path
#define g_request_record_path (*(char * *)(g_sd + 0x13318))


// entry: 004329b0
// name : handle_fault_signal
// size : 92
// sig  : void handle_fault_signal(int sig)


/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int __cdecl handle_fault_signal(int sig)

{
  close_and_delete_temp_files();
  if ((((g_loaded_request != (request *)0x0) &&
       (g_loaded_request->cpp_block != (request_cpp_block *)0x0)) && (g_loaded_request->stage == 0))
     && ((0 < g_loaded_request->error_count && ((g_loaded_request->message_flags & 1) == 0)))) {
    store_request_record_file(0,g_request_record_path);
    stock_exit(7);
  }
  stock_exit(0xf);
  return;
}



