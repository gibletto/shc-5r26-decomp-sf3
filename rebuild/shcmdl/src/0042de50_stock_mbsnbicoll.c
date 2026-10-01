#include "decls.h"
#include "imports.h"

// entry: 0042de50
// name : stock_mbsnbicoll
// size : 59
// sig  : int stock_mbsnbicoll(uchar * s1, uchar * s2, uint count)


/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_mbsnbicoll(uchar *s1,uchar *s2,uint count)

{
  uint uVar1;
  
  if (count == 0) {
    return 0;
  }
  uVar1 = stock_crtCompareStringA(stock_mblcid,1,s1,count,s2,count,stock_mbcodepage);
  if (uVar1 == 0) {
    return 0x7fffffff;
  }
  return uVar1 - 2;
}



