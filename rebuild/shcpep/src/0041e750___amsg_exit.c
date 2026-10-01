#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_aexit_rtn
#define stock_aexit_rtn (*(unsigned char * *)(g_sd + 0x44b0))


// entry: 0041e750
// name : __amsg_exit
// size : 38
// sig  : void __amsg_exit(int rterrnum)


/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

int __cdecl __amsg_exit(int rterrnum)

{
  if (stock_error_mode != 2) {
    __FF_MSGBANNER();
  }
  stock_NMSG_WRITE(rterrnum);
  (*(code *)stock_aexit_rtn)(0xff);
  return;
}



