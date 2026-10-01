#include "decls.h"
#include "imports.h"

// entry: 004221c0
// name : stock_mbsrchr
// size : 110
// sig  : char * __cdecl stock_mbsrchr(uchar *str,uint ch)


char * __cdecl stock_mbsrchr(uchar *str,uint ch)

{
  byte bVar1;
  byte *pbVar2;
  char *pcVar3;
  byte *pbVar4;
  
  pbVar2 = (byte *)0x0;
  if (stock_mbcodepage == 0) {
    pcVar3 = _strrchr((char *)str,ch);
    return pcVar3;
  }
  do {
    bVar1 = *str;
    if ((*(byte *)((int)&stock_mbctype + bVar1 + 1) & 4) == 0) {
      pbVar4 = str;
      if (bVar1 == ch) {
LAB_00422220:
        pbVar2 = str;
        pbVar4 = pbVar2;
      }
    }
    else {
      pbVar4 = str + 1;
      if (str[1] == 0) {
        str = pbVar4;
        if (pbVar2 == (byte *)0x0) goto LAB_00422220;
      }
      else if (CONCAT11(bVar1,str[1]) == ch) {
        pbVar2 = str;
      }
    }
    str = pbVar4 + 1;
    if (*pbVar4 == 0) {
      return (char *)pbVar2;
    }
  } while( true );
}
