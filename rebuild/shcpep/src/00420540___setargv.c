#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_acmdln
#define stock_acmdln (*(unsigned char * *)(g_sd + 0x7f60))
#undef stock_argv
#define stock_argv (*(int * *)(g_sd + 0x4480))


// entry: 00420540
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
#define local_8 (*(int *)(_frec_8 + 0))
#define local_4 (*(int *)(_frec_8 + 4))
  undefined4 *argv;
  byte *cmdstart;
  
  GetModuleFileNameA((HMODULE)0x0,&stock_pgmname,0x104);
  _stock_pgmptr = &stock_pgmname;
  cmdstart = &stock_pgmname;
  if (*stock_acmdln != 0) {
    cmdstart = stock_acmdln;
  }
  parse_cmdline(cmdstart,(undefined4 *)0x0,(byte *)0x0,&local_8,&local_4);
  argv = stock_malloc(local_8 * 4 + local_4);
  if (argv == (undefined4 *)0x0) {
    __amsg_exit(8);
  }
  parse_cmdline(cmdstart,argv,(byte *)(argv + local_8),&local_8,&local_4);
  stock_argv = argv;
  stock_argc = local_8 + -1;
  return local_8 + -1;
#undef local_8
#undef local_4
}



