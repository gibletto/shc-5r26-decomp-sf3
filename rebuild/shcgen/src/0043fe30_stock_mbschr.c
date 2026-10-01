#include "decls.h"
#include "imports.h"

// entry: 0043fe30
// name : stock_mbschr
// size : 141
// sig  : uchar * stock_mbschr(uchar * str, uint ch)


/* Library Function - Single Match
    __mbschr
   
   Library: Visual Studio 1998 Release */

uchar * __cdecl stock_mbschr(uchar *str,uint ch)

{
  uchar *puVar1;
  uint code_unit;
  byte lead;
  
  if (stock_mbcodepage == 0) {
    puVar1 = (uchar *)stock_strchr((char *)str,(char)ch);
    return puVar1;
  }
  lead = *str;
  while (code_unit = (uint)(ushort)lead, lead != 0) {
    if ((*(byte *)((int)&stock_mbctype + code_unit + 1) & 4) == 0) {
      puVar1 = str;
      if (code_unit == ch) break;
    }
    else {
      if (str[1] == '\0') {
        return (uchar *)0x0;
      }
      puVar1 = str + 1;
      if (CONCAT11(lead,str[1]) == ch) {
        return str;
      }
    }
    str = puVar1 + 1;
    lead = puVar1[1];
  }
  return (uchar *)(-(uint)(code_unit == ch) & (uint)str);
}



