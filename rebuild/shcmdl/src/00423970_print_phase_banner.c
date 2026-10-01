#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_phase_banners
#define g_phase_banners (*(unsigned char * *)(g_sd + 0x3dd0))


// entry: 00423970
// name : print_phase_banner
// size : 64
// sig  : void print_phase_banner(short phase)


int __cdecl print_phase_banner(short phase)

{
  _fputs((&g_phase_banners)[phase],(FILE *)&stock_stderr);
  _fputc(10,(FILE *)&stock_stderr);
  _fflush((FILE *)&stock_stderr);
  return;
}



