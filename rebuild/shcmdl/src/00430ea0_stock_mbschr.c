#include "decls.h"
#include "imports.h"

// entry: 00430ea0
// name : stock_mbschr
// size : 141
// sig  : uchar * stock_mbschr(uchar * str, uint ch)


/* Library Function - Single Match
    __mbschr
   
   Library: Visual Studio 1998 Release */

uchar * __cdecl stock_mbschr(uchar *str,uint ch)

{
  byte bVar1;
  uint uVar2;
  uchar *puVar3;
  
  if (stock_mbcodepage == 0) {
    puVar3 = (uchar *)stock_strchr((char *)str,(char)ch);
    return puVar3;
  }
  bVar1 = *str;
  while (uVar2 = (uint)(ushort)bVar1, bVar1 != 0) {
    if ((*(byte *)((int)&stock_mbctype + uVar2 + 1) & 4) == 0) {
      puVar3 = str;
      if (uVar2 == ch) break;
    }
    else {
      if (str[1] == '\0') {
        return (uchar *)0x0;
      }
      puVar3 = str + 1;
      if (CONCAT11(bVar1,str[1]) == ch) {
        return str;
      }
    }
    str = puVar3 + 1;
    bVar1 = puVar3[1];
  }
  return (uchar *)(-(uint)(uVar2 == ch) & (uint)str);
}



