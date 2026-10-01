#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_internal_error_text
#define g_internal_error_text (*(char * *)(g_sd + 0x8110))
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x13320))


// entry: 004347c0
// name : report_message_file_error_and_exit
// size : 215
// sig  : void __cdecl report_message_file_error_and_exit(int msgno)


int __cdecl report_message_file_error_and_exit(int msgno)

{
  ushort exit_level;
  
  exit_level = 5;
  _sprintf(&g_message_number_text,&s_pct_d_00443128,msgno);
  _fputs(&s_nl_sp_sp_00443124,(FILE *)&stock_stdout);
  _fputs(g_loaded_request->source_name,(FILE *)&stock_stdout);
  _fputs(s__0____0044311c,(FILE *)&stock_stdout);
  _fputs(&g_message_number_text,(FILE *)&stock_stdout);
  _fputs(&s_sp_00443118,(FILE *)&stock_stdout);
  if (msgno / 1000 == 4) {
    _fputs(g_internal_error_text,(FILE *)&stock_stdout);
  }
  else if (msgno / 1000 == 3) {
    exit_level = 4;
    _fputs(*(char **)(&g_internal_file_error_text + msgno * 4),(FILE *)&stock_stdout);
  }
  close_and_delete_temp_files();
  stock_exit((short)(exit_level | 0x10) * 2 + 1);
  return;
}
