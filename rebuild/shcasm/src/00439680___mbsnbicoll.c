#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_mbcodepage
#define stock_mbcodepage (*(unsigned int *)(g_sd + 0x85dc))
#undef stock_mblcid
#define stock_mblcid (*(unsigned int *)(g_sd + 0x85e0))


// entry: 00439680
// name : __mbsnbicoll
// size : 59
// sig  : int __mbsnbicoll(uchar * _Str1, uchar * _Str2, size_t _MaxCount)


/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 1998 Release */

int __cdecl __mbsnbicoll(uchar *_Str1,uchar *_Str2,size_t _MaxCount)

{
  int cmp_result;
  
  if (_MaxCount == 0) {
    return 0;
  }
  cmp_result = stock_crtCompareStringA
                         (stock_mblcid,1,_Str1,_MaxCount,_Str2,_MaxCount,stock_mbcodepage);
  if (cmp_result == 0) {
    return 0x7fffffff;
  }
  return cmp_result + -2;
}



