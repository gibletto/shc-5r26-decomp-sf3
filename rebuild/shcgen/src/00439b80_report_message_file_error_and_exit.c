#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_internal_error_text
#define g_internal_error_text (*(char * *)(g_sd + 0x1c998))
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x1ff84))


// entry: 00439b80
// name : report_message_file_error_and_exit
// size : 215
// sig  : void report_message_file_error_and_exit(int msgno)


int __cdecl report_message_file_error_and_exit(int msgno)

{
  ushort exit_code;
  
  exit_code = 5;
  _sprintf(&g_message_number_text,&DAT_0045c9b0,msgno);
  _fputs(&DAT_0045c9ac,(FILE *)&stock_stdout);
  _fputs(g_loaded_request->source_name,(FILE *)&stock_stdout);
  _fputs(s__0____0045c9a4,(FILE *)&stock_stdout);
  _fputs(&g_message_number_text,(FILE *)&stock_stdout);
  _fputs(&DAT_0045c9a0,(FILE *)&stock_stdout);
  if (msgno / 1000 == 4) {
    _fputs(g_internal_error_text,(FILE *)&stock_stdout);
  }
  else if (msgno / 1000 == 3) {
    exit_code = 4;
    _fputs(*(char **)(s_al008_004595f8 + msgno * 4),(FILE *)&stock_stdout);
  }
  close_and_delete_temp_files();
  stock_exit((short)(exit_code | 0x10) * 2 + 1);
  return;
}



