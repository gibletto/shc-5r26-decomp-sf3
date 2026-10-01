#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR___exit_00436354
#define PTR___exit_00436354 (*(unsigned char * *)(g_sd + 0x4354))


// entry: 0042a4b0
// name : stock_amsg_exit
// size : 38
// sig  : void stock_amsg_exit(int msg)


/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_amsg_exit(int msg)

{
  if (stock_error_mode != 2) {
    __FF_MSGBANNER();
  }
  stock_NMSG_WRITE(msg);
  (*(code *)PTR___exit_00436354)(0xff);
  return;
}



