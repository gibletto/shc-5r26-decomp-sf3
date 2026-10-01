#include "decls.h"
#include "imports.h"

// entry: 00422420
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
#define local_4 (*(BOOL *)(_frec_4 + 0))
  int iVar1;
  
  if (_MbCh == (char *)0x0) {
    return 0;
  }
  if (DAT_004291b8 == 0) {
    if (0xff < (ushort)_WCh) {
      _stock_errno = 0x2a;
      return -1;
    }
    *_MbCh = (char)_WCh;
    return 1;
  }
  local_4 = 0;
  iVar1 = WideCharToMultiByte(stock_lc_codepage,0x220,&_WCh,1,_MbCh,stock_mb_cur_max,(LPCSTR)0x0,
                              &local_4);
  if ((iVar1 == 0) || (local_4 != 0)) {
    _stock_errno = 0x2a;
    iVar1 = -1;
  }
  return iVar1;
#undef local_4
}



