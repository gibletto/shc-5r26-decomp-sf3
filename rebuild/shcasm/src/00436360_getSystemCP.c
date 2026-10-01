#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_fSystemSet
#define stock_fSystemSet (*(unsigned int *)(g_sd + 0x85f4))


// entry: 00436360
// name : getSystemCP
// size : 77
// sig  : int getSystemCP(int param_1)


/* Library Function - Single Match
    _getSystemCP
   
   Library: Visual Studio 1998 Release */

int __cdecl getSystemCP(int param_1)

{
  int cp;
  bool bVar1;
  
  if (param_1 == -2) {
    stock_fSystemSet = 1;
                    /* WARNING: Could not recover jumptable at 0x0043637d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    cp = GetOEMCP();
    return cp;
  }
  if (param_1 == -3) {
    stock_fSystemSet = 1;
                    /* WARNING: Could not recover jumptable at 0x00436392. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    cp = GetACP();
    return cp;
  }
  bVar1 = param_1 == -4;
  if (bVar1) {
    param_1 = stock_lc_codepage;
  }
  stock_fSystemSet = (uint)bVar1;
  return param_1;
}



