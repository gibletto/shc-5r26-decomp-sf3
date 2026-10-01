#include "decls.h"
#include "imports.h"

// entry: 004239c0
// name : __mbschr
// size : 141
// sig  : uchar * __mbschr(uchar * _Str, uint _Ch)


/* Library Function - Single Match
    __mbschr
   
   Library: Visual Studio 1998 Release */

uchar * __cdecl __mbschr(uchar *_Str,uint _Ch)

{
  byte bVar1;
  uint uVar2;
  uchar *puVar3;
  
  if (stock_mbcodepage == 0) {
    puVar3 = (uchar *)stock_strchr((char *)_Str,(char)_Ch);
    return puVar3;
  }
  bVar1 = *_Str;
  while (uVar2 = (uint)(ushort)bVar1, bVar1 != 0) {
    if ((*(byte *)((int)&stock_mbctype + uVar2 + 1) & 4) == 0) {
      puVar3 = _Str;
      if (uVar2 == _Ch) break;
    }
    else {
      if (_Str[1] == '\0') {
        return (uchar *)0x0;
      }
      puVar3 = _Str + 1;
      if (CONCAT11(bVar1,_Str[1]) == _Ch) {
        return _Str;
      }
    }
    _Str = puVar3 + 1;
    bVar1 = puVar3[1];
  }
  return (uchar *)(-(uint)(uVar2 == _Ch) & (uint)_Str);
}



