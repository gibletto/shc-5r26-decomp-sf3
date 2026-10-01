#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lit_file
#define g_lit_file (*(FILE * *)(g_sd + 0x1fa08))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041ab90
// name : run_stage_pipeline_and_exit
// size : 76
// sig  : void run_stage_pipeline_and_exit(char * request_path)


int __cdecl run_stage_pipeline_and_exit(char *request_path)

{
  if (*(short *)g_request->unknown_004 == 0) {
    write_final_literal_pool_flag(g_lit_file);
  }
  store_request_record_file(2,request_path);
  write_asa_record(0xd,0);
  close_stage_files();
  stock_exit(g_message_severity * 2 + 1);
  return;
}



