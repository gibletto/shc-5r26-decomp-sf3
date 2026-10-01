#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_aexit_rtn
#define stock_aexit_rtn (*(unsigned char * *)(g_sd + 0x1ca70))


// entry: 0043aa10
// name : stock_amsg_exit
// size : 38
// sig  : void stock_amsg_exit(int msg)


/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_amsg_exit(int msg)

{
  if (stock_error_mode != 2) {
    stock_FF_MSGBANNER();
  }
  stock_NMSG_WRITE(msg);
  (*(code *)stock_aexit_rtn)(0xff);
  return;
}



