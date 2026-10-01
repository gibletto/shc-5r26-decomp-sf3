#include "decls.h"
#include "imports.h"

// entry: 004397d0
// name : _wctomb
// size : 146
// sig  : int _wctomb(char * _MbCh, wchar_t _WCh)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _wctomb
   
   Library: Visual Studio 1998 Release */

int __cdecl _wctomb(char *_MbCh,wchar_t _WCh)

{
  unsigned char _frec_4[4];
#define defused (*(BOOL *)(_frec_4 + 0))
  int result;
  
  if (_MbCh == (char *)0x0) {
    return 0;
  }
  if (DAT_00443ec0 == 0) {
    if (0xff < (ushort)_WCh) {
      _stock_errno = 0x2a;
      return -1;
    }
    *_MbCh = (char)_WCh;
    return 1;
  }
  defused = 0;
  result = WideCharToMultiByte(stock_lc_codepage,0x220,&_WCh,1,_MbCh,stock_mb_cur_max,(LPCSTR)0x0,
                               &defused);
  if ((result == 0) || (defused != 0)) {
    _stock_errno = 0x2a;
    result = -1;
  }
  return result;
#undef defused
}



