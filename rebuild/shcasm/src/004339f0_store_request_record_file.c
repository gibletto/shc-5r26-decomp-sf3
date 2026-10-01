#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x13320))
#undef g_request_record_path
#define g_request_record_path (*(void * *)(g_sd + 0x13318))
#undef g_request_trailer_file
#define g_request_trailer_file (*(FILE * *)(g_sd + 0x1331c))


// entry: 004339f0
// name : store_request_record_file
// size : 218
// sig  : uint store_request_record_file(int stage, char * path)


uint __cdecl store_request_record_file(int stage,char *path)

{
  FILE *out;
  uint result;
  int close_result;
  uint extraout_EAX;
  
  out = stock_fopen(path,&s_wb_00442e24);
  if (out == (FILE *)0x0) {
    report_message_by_code(g_loaded_request->source_name,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  result = write_file_bytes(out,(char *)&g_request_record_size,2);
  check_request_write_result(result);
  write_request_fixed_part(g_loaded_request,out);
  write_request_variable_part(g_loaded_request,out);
  if (g_request_trailer_file != (FILE *)0x0) {
    copy_request_trailer_from_temp(out);
  }
  close_result = _fclose(out);
  if (close_result == -1) {
    report_message_by_code(g_loaded_request->source_name,0,0xce5,(char *)0x0);
    stock_exit(9);
  }
  stock_free(g_request_record_path);
  g_request_record_path = (void *)0x0;
  return extraout_EAX & 0xffff0000;
}



