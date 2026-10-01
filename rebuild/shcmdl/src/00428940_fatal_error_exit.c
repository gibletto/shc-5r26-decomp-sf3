#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_s_Internal_error_00435f90
#define PTR_s_Internal_error_00435f90 (*(unsigned char * *)(g_sd + 0x3f90))
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 00428940
// name : fatal_error_exit
// size : 215
// sig  : int __cdecl fatal_error_exit(int errcode)


int __cdecl fatal_error_exit(int errcode)

{
  int extraout_EAX;
  ushort exit_code;
  
  exit_code = 5;
  _sprintf(&g_fatal_code_text,&g_str_percent_d,errcode);
  _fputs(&g_str_newline_indent,(FILE *)&stock_stdout);
  _fputs(g_options_for_errors->source_name,(FILE *)&stock_stdout);
  _fputs(s__0____00435f9c,(FILE *)&stock_stdout);
  _fputs(&g_fatal_code_text,(FILE *)&stock_stdout);
  _fputs(&g_str_space,(FILE *)&stock_stdout);
  if (errcode / 1000 == 4) {
    _fputs(PTR_s_Internal_error_00435f90,(FILE *)&stock_stdout);
  }
  else if (errcode / 1000 == 3) {
    exit_code = 4;
    _fputs(*(char **)(errcode * 4 + SD(0x00432bf0)),(FILE *)&stock_stdout);
  }
  remove_temp_files();
  stock_exit((short)(exit_code | 0x10) * 2 + 1);
  return extraout_EAX;
}
