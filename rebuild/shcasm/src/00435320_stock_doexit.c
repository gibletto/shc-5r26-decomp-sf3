#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_onexitbegin
#define stock_onexitbegin (*(int * *)(g_sd + 0x16ccc))


// entry: 00435320
// name : stock_doexit
// size : 128
// sig  : void __cdecl stock_doexit(uint exit_code,int quick,int retcaller)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_doexit(uint exit_code,int quick,int retcaller)

{
  undefined4 *pfend;
  
  _stock_C_Exit_Done = 1;
  stock_exitflag = (undefined1)retcaller;
  if (quick == 0) {
    if ((stock_onexitbegin != (undefined4 *)0x0) &&
       (pfend = (undefined4 *)(stock_onexitend + -4), stock_onexitbegin <= pfend)) {
      do {
        if ((code *)*pfend != 0) {
          (*(code *)*pfend)();
        }
        pfend = pfend + -1;
      } while (stock_onexitbegin <= pfend);
    }
    stock_initterm((undefined4 *)&stock_xp_a,(undefined4 *)&stock_xp_z);
    _flushall();
  }
  stock_initterm((undefined4 *)&stock_xt_a,(undefined4 *)&stock_xt_z);
  if (retcaller == 0) {
                    /* WARNING: Subroutine does not return */
    ExitProcess(exit_code);
  }
  return;
}
