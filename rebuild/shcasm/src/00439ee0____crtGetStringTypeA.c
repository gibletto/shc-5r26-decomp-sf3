#include "decls.h"
#include "imports.h"

// entry: 00439ee0
// name : ___crtGetStringTypeA
// size : 291
// sig  : BOOL ___crtGetStringTypeA(_locale_t _Plocinfo, DWORD _DWInfoType, LPCSTR _LpSrcStr, int _CchSrc, LPWORD _LpCharType, int _Code_page, BOOL _BError)


/* Library Function - Single Match
    ___crtGetStringTypeA
   
   Library: Visual Studio 1998 Release */

BOOL __cdecl
___crtGetStringTypeA
          (_locale_t _Plocinfo,DWORD _DWInfoType,LPCSTR _LpSrcStr,int _CchSrc,LPWORD _LpCharType,
          int _Code_page,BOOL _BError)

{
  BOOL BVar1;
  int wlen;
  int iVar2;
  LPCWSTR lpWideCharStr;
  WORD dummy_type;
  
  iVar2 = stock_f_use_GetStringType;
  if (stock_f_use_GetStringType == 0) {
    BVar1 = GetStringTypeA(0,1,&DAT_00443f7c,1,&dummy_type);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeW(1,(LPCWSTR)&DAT_00443f80,1,&dummy_type);
      if (BVar1 == 0) {
        return 0;
      }
      iVar2 = 1;
    }
    else {
      iVar2 = 2;
    }
  }
  stock_f_use_GetStringType = iVar2;
  if (iVar2 != 2) {
    if (iVar2 == 1) {
      BVar1 = 0;
      lpWideCharStr = (LPCWSTR)0x0;
      if (_LpCharType == (LPWORD)0x0) {
        _LpCharType = stock_lc_codepage;
      }
      wlen = MultiByteToWideChar((UINT)_LpCharType,9,(LPCSTR)_DWInfoType,(int)_LpSrcStr,(LPWSTR)0x0,
                                 0);
      iVar2 = BVar1;
      if (((wlen != 0) && (lpWideCharStr = stock_calloc(2,wlen), lpWideCharStr != (LPCWSTR)0x0)) &&
         (wlen = MultiByteToWideChar((UINT)_LpCharType,1,(LPCSTR)_DWInfoType,(int)_LpSrcStr,
                                     lpWideCharStr,wlen), wlen != 0)) {
        iVar2 = GetStringTypeW((DWORD)_Plocinfo,lpWideCharStr,wlen,(LPWORD)_CchSrc);
      }
      stock_free(lpWideCharStr);
    }
    return iVar2;
  }
  if (_Code_page == 0) {
    _Code_page = DAT_00443ec0;
  }
  BVar1 = GetStringTypeA(_Code_page,(DWORD)_Plocinfo,(LPCSTR)_DWInfoType,(int)_LpSrcStr,
                         (LPWORD)_CchSrc);
  return BVar1;
}



