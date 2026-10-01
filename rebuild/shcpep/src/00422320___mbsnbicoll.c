#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_mbcodepage
#define stock_mbcodepage (*(unsigned int *)(g_sd + 0x495c))
#undef stock_mblcid
#define stock_mblcid (*(unsigned int *)(g_sd + 0x4960))


// entry: 00422320
// name : __mbsnbicoll
// size : 59
// sig  : int __mbsnbicoll(uchar * _Str1, uchar * _Str2, size_t _MaxCount)


/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 1998 Release */

int __cdecl __mbsnbicoll(uchar *_Str1,uchar *_Str2,size_t _MaxCount)

{
  int iVar1;
  
  if (_MaxCount == 0) {
    return 0;
  }
  iVar1 = stock_crtCompareStringA(stock_mblcid,1,_Str1,_MaxCount,_Str2,_MaxCount,stock_mbcodepage);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}



