#include "decls.h"
#include "imports.h"

// entry: 0043ab50
// name : __mbschr
// size : 141
// sig  : uchar * __mbschr(uchar * _Str, uint _Ch)


/* Library Function - Single Match
    __mbschr
   
   Library: Visual Studio 1998 Release */

uchar * __cdecl __mbschr(uchar *_Str,uint _Ch)

{
  uchar *next;
  byte ch;
  uint wide_ch;
  
  if (stock_mbcodepage == 0) {
    next = (uchar *)stock_strchr((char *)_Str,(char)_Ch);
    return next;
  }
  ch = *_Str;
  while (wide_ch = (uint)(ushort)ch, ch != 0) {
    if ((*(byte *)((int)&stock_mbctype + wide_ch + 1) & 4) == 0) {
      next = _Str;
      if (wide_ch == _Ch) break;
    }
    else {
      if (_Str[1] == '\0') {
        return (uchar *)0x0;
      }
      next = _Str + 1;
      if (CONCAT11(ch,_Str[1]) == _Ch) {
        return _Str;
      }
    }
    _Str = next + 1;
    ch = next[1];
  }
  return (uchar *)(-(uint)(wide_ch == _Ch) & (uint)_Str);
}



