#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_onexitbegin
#define stock_onexitbegin (*(int * *)(g_sd + 0x28464))


// entry: 00429ab0
// name : stock_doexit
// size : 128
// sig  : void stock_doexit(uint errcode, int quick, int retcaller)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_doexit(uint errcode,int quick,int retcaller)

{
  undefined4 *puVar1;
  
  _stock_C_Exit_Done = 1;
  stock_exitflag = (undefined1)retcaller;
  if (quick == 0) {
    if ((stock_onexitbegin != (undefined4 *)0x0) &&
       (puVar1 = (undefined4 *)(stock_onexitend + -4), stock_onexitbegin <= puVar1)) {
      do {
        if ((code *)*puVar1 != 0) {
          (*(code *)*puVar1)();
        }
        puVar1 = puVar1 + -1;
      } while (stock_onexitbegin <= puVar1);
    }
    stock_initterm(&DAT_00433014,&DAT_00433020);
  }
  stock_initterm(&DAT_00433024,&DAT_00433028);
  if (retcaller == 0) {
                    /* WARNING: Subroutine does not return */
    ExitProcess(errcode);
  }
  return;
}



