#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_acmdln
#define stock_acmdln (*(unsigned char * *)(g_sd + 0x16cc0))
#undef stock_argv
#define stock_argv (*(int * *)(g_sd + 0x81d0))


// entry: 00437cd0
// name : __setargv
// size : 155
// sig  : int __setargv(void)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setargv
   
   Library: Visual Studio 1998 Release */

int __cdecl __setargv(void)

{
  unsigned char _frec_8[8];
#define numargs (*(int *)(_frec_8 + 0))
#define numchars (*(int *)(_frec_8 + 4))
  undefined4 *argv_block;
  byte *cmdstart;
  
  GetModuleFileNameA((HMODULE)0x0,&stock_pgmname,0x104);
  _stock_pgmptr = &stock_pgmname;
  cmdstart = &stock_pgmname;
  if (*stock_acmdln != 0) {
    cmdstart = stock_acmdln;
  }
  parse_cmdline(cmdstart,(undefined4 *)0x0,(byte *)0x0,&numargs,&numchars);
  argv_block = stock_malloc(numargs * 4 + numchars);
  if (argv_block == (undefined4 *)0x0) {
    __amsg_exit(8);
  }
  parse_cmdline(cmdstart,argv_block,(byte *)(argv_block + numargs),&numargs,&numchars);
  stock_argv = argv_block;
  stock_argc = numargs + -1;
  return numargs + -1;
#undef numargs
#undef numchars
}



