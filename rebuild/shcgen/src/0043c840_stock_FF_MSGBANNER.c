#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_adbgmsg
#define stock_adbgmsg (*(int (**)())(g_sd + 0x1d300))


// entry: 0043c840
// name : stock_FF_MSGBANNER
// size : 61
// sig  : void stock_FF_MSGBANNER(void)


/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_FF_MSGBANNER(void)

{
  if ((stock_error_mode == 1) || ((stock_error_mode == 0 && (stock_app_type == 1)))) {
    stock_NMSG_WRITE(0xfc);
    if (stock_adbgmsg != 0) {
      (*stock_adbgmsg)();
    }
    stock_NMSG_WRITE(0xff);
  }
  return;
}



