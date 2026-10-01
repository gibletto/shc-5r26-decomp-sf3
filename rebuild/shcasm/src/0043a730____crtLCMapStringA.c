#include "decls.h"
#include "imports.h"

// entry: 0043a730
// name : ___crtLCMapStringA
// size : 555
// sig  : int ___crtLCMapStringA(_locale_t _Plocinfo, LPCWSTR _LocaleName, DWORD _DwMapFlag, LPCSTR _LpSrcStr, int _CchSrc, LPSTR _LpDestStr, int _CchDest, int _Code_page, BOOL _BError)


/* Library Function - Single Match
    ___crtLCMapStringA
   
   Library: Visual Studio 1998 Release */

int __cdecl ___crtLCMapStringA(_locale_t _Plocinfo,LPCWSTR _LocaleName,DWORD _DwMapFlag,LPCSTR _LpSrcStr,
                  int _CchSrc,LPSTR _LpDestStr,int _CchDest,int _Code_page,BOOL _BError)

{
  int iVar1;
  LPCWSTR lpWideCharStr;
  int dest_len;
  LPCWSTR lpDestStr;
  
  if (stock_f_use_LCMapString == 0) {
    iVar1 = LCMapStringA(0,0x100,&DAT_00443f7c,1,(LPSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringW(0,0x100,(LPCWSTR)&DAT_00443f80,1,(LPWSTR)0x0,0);
      if (iVar1 == 0) {
        return 0;
      }
      stock_f_use_LCMapString = 1;
    }
    else {
      stock_f_use_LCMapString = 2;
    }
  }
  if (0 < (int)_LpSrcStr) {
    _LpSrcStr = (LPCSTR)_strncnt_lcmap((char *)_DwMapFlag,(size_t)_LpSrcStr);
  }
  if (stock_f_use_LCMapString == 2) {
    iVar1 = LCMapStringA((LCID)_Plocinfo,(DWORD)_LocaleName,(LPCSTR)_DwMapFlag,(int)_LpSrcStr,
                         (LPSTR)_CchSrc,(int)_LpDestStr);
    return iVar1;
  }
  if (stock_f_use_LCMapString != 1) {
    return stock_f_use_LCMapString;
  }
  lpDestStr = (LPCWSTR)0x0;
  if (_CchDest == 0) {
    _CchDest = stock_lc_codepage;
  }
  iVar1 = MultiByteToWideChar(_CchDest,9,(LPCSTR)_DwMapFlag,(int)_LpSrcStr,(LPWSTR)0x0,0);
  if (iVar1 == 0) {
    return 0;
  }
  lpWideCharStr = stock_malloc(iVar1 * 2);
  if (lpWideCharStr == (LPCWSTR)0x0) {
    return 0;
  }
  dest_len = MultiByteToWideChar(_CchDest,1,(LPCSTR)_DwMapFlag,(int)_LpSrcStr,lpWideCharStr,iVar1);
  if ((dest_len != 0) &&
     (dest_len = LCMapStringW((LCID)_Plocinfo,(DWORD)_LocaleName,lpWideCharStr,iVar1,(LPWSTR)0x0,0),
     dest_len != 0)) {
    if (((uint)_LocaleName & 0x400) == 0) {
      lpDestStr = stock_malloc(dest_len * 2);
      if ((lpDestStr == (LPCWSTR)0x0) ||
         (iVar1 = LCMapStringW((LCID)_Plocinfo,(DWORD)_LocaleName,lpWideCharStr,iVar1,lpDestStr,
                               dest_len), iVar1 == 0)) goto LAB_0043a8ab;
      if (_LpDestStr == (LPSTR)0x0) {
        dest_len = WideCharToMultiByte(_CchDest,0x220,lpDestStr,dest_len,(LPSTR)0x0,0,(LPCSTR)0x0,
                                       (LPBOOL)0x0);
        iVar1 = dest_len;
      }
      else {
        dest_len = WideCharToMultiByte(_CchDest,0x220,lpDestStr,dest_len,(LPSTR)_CchSrc,
                                       (int)_LpDestStr,(LPCSTR)0x0,(LPBOOL)0x0);
        iVar1 = dest_len;
      }
    }
    else {
      if (_LpDestStr == (LPSTR)0x0) goto LAB_0043a942;
      if ((int)_LpDestStr < dest_len) goto LAB_0043a8ab;
      iVar1 = LCMapStringW((LCID)_Plocinfo,(DWORD)_LocaleName,lpWideCharStr,iVar1,(LPWSTR)_CchSrc,
                           (int)_LpDestStr);
    }
    if (iVar1 != 0) {
LAB_0043a942:
      stock_free(lpWideCharStr);
      stock_free(lpDestStr);
      return dest_len;
    }
  }
LAB_0043a8ab:
  stock_free(lpWideCharStr);
  stock_free(lpDestStr);
  return 0;
}



