#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_s_Internal_error_004283d8
#define PTR_s_Internal_error_004283d8 (*(unsigned char * *)(g_sd + 0x43d8))
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x6e34))


// entry: 0041e120
// name : report_message_file_error_and_exit
// size : 215
// sig  : void __cdecl report_message_file_error_and_exit(int msgno)


int __cdecl report_message_file_error_and_exit(int msgno)

{
  ushort exit_code;
  
  exit_code = 5;
  _sprintf(&g_message_number_text,s_pct_d_004283f0,msgno);
  _fputs(s_nl_sp_sp_004283ec,(FILE *)&stock_stdout);
  _fputs(g_loaded_request->source_name,(FILE *)&stock_stdout);
  _fputs(s__0____004283e4,(FILE *)&stock_stdout);
  _fputs(&g_message_number_text,(FILE *)&stock_stdout);
  _fputs(s_sp_004283e0,(FILE *)&stock_stdout);
  if (msgno / 1000 == 4) {
    _fputs(PTR_s_Internal_error_004283d8,(FILE *)&stock_stdout);
  }
  else if (msgno / 1000 == 3) {
    exit_code = 4;
    _fputs(*(char **)(s_imadd_end__00425030 + msgno * 4 + 8),(FILE *)&stock_stdout);
  }
  close_and_delete_temp_files();
  stock_exit((short)(exit_code | 0x10) * 2 + 1);
  return;
}
