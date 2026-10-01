#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_mbcodepage
#define stock_mbcodepage (*(unsigned int *)(g_sd + 0x1cef4))
#undef stock_mblcid
#define stock_mblcid (*(unsigned int *)(g_sd + 0x1cef8))


// entry: 0043e790
// name : stock_mbsnbicoll
// size : 59
// sig  : int stock_mbsnbicoll(uchar * str1, uchar * str2, uint count)


/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_mbsnbicoll(uchar *str1,uchar *str2,uint count)

{
  int cmp;
  
  if (count == 0) {
    return 0;
  }
  cmp = stock_crtCompareStringA(stock_mblcid,1,str1,count,str2,count,stock_mbcodepage);
  if (cmp == 0) {
    return 0x7fffffff;
  }
  return cmp + -2;
}



