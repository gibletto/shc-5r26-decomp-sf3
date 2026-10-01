#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_progress_banner_table
#define g_progress_banner_table (*(unsigned char * *)(g_sd + 0x7dd0))


// entry: 004339b0
// name : emit_progress_banner
// size : 64
// sig  : void __cdecl emit_progress_banner(short stage)


int __cdecl emit_progress_banner(short stage)

{
  _fputs((&g_progress_banner_table)[stage],(FILE *)&stock_stderr);
  _fputc(10,(FILE *)&stock_stderr);
  _fflush((FILE *)&stock_stderr);
  return;
}
