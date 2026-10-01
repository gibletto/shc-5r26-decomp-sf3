#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_fSystemSet
#define stock_fSystemSet (*(unsigned int *)(g_sd + 0x4974))


// entry: 00420b40
// name : getSystemCP
// size : 77
// sig  : int getSystemCP(int codepage)


/* Library Function - Single Match
    _getSystemCP
   
   Library: Visual Studio 1998 Release */

int __cdecl getSystemCP(int codepage)

{
  int iVar1;
  bool bVar2;
  
  if (codepage == -2) {
    stock_fSystemSet = 1;
                    /* WARNING: Could not recover jumptable at 0x00420b5d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (codepage == -3) {
    stock_fSystemSet = 1;
                    /* WARNING: Could not recover jumptable at 0x00420b72. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = codepage == -4;
  if (bVar2) {
    codepage = stock_lc_codepage;
  }
  stock_fSystemSet = (uint)bVar2;
  return codepage;
}



