#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_input_tail_file
#define g_input_tail_file (*(FILE * *)(g_sd + 0x2732c))
#undef g_int_file_path
#define g_int_file_path (*(char * *)(g_sd + 0x27328))
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 00424a20
// name : write_intermediate_file
// size : 218
// sig  : uint write_intermediate_file(int phase, char * path)


uint __cdecl write_intermediate_file(int phase,char *path)

{
  FILE *fp;
  uint result;
  int status;
  
  fp = stock_fopen(path,&g_mode_wb);
  if (fp == (FILE *)0x0) {
    write_error_record(g_options_for_errors->source_name,0,0xce4,(char *)0x0);
    stock_exit(9);
  }
  result = write_bytes(fp,(char *)&g_option_record_size,2);
  check_write_result(result);
  write_option_record((char *)g_options_for_errors,fp);
  write_option_strings_and_lists((int *)g_options_for_errors,fp);
  if (g_input_tail_file != (FILE *)0x0) {
    append_input_tail(fp);
  }
  status = _fclose(fp);
  if (status == -1) {
    write_error_record(g_options_for_errors->source_name,0,0xce5,(char *)0x0);
    stock_exit(9);
  }
  result = stock_free(g_int_file_path);
  g_int_file_path = (char *)0x0;
  return result & 0xffff0000;
}



