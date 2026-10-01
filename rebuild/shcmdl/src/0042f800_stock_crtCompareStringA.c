#include "decls.h"
#include "imports.h"

// entry: 0042f800
// name : stock_crtCompareStringA
// size : 749
// sig  : uint stock_crtCompareStringA(uint locale, uint flags, uchar * s1, uint len1, uchar * s2, uint len2, uint code_page)


uint __cdecl
stock_crtCompareStringA
          (uint locale,uint flags,uchar *s1,uint len1,uchar *s2,uint len2,uint code_page)

{
  size_t in_EAX;
  uint uVar1;
  BOOL BVar2;
  BYTE *pBVar3;
  PCNZWCH lpWideCharStr;
  int iVar4;
  int iVar5;
  LPWSTR local_20;
  uint local_18;
  _cpinfo local_14;
  
  if (stock_compare_string_mode == 0) {
    in_EAX = CompareStringA(0,0,&DAT_004365d8,1,&DAT_004365d8,1);
    if (in_EAX == 0) {
      in_EAX = CompareStringW(0,0,(PCNZWCH)&DAT_004365dc,1,(PCNZWCH)&DAT_004365dc,1);
      if (in_EAX == 0) {
        return 0;
      }
      stock_compare_string_mode = 1;
    }
    else {
      stock_compare_string_mode = 2;
    }
  }
  local_18 = in_EAX;
  if (0 < (int)len1) {
    local_18 = _strncnt((char *)s1,len1);
    len1 = local_18;
  }
  if (0 < (int)len2) {
    local_18 = _strncnt((char *)s2,len2);
    len2 = local_18;
  }
  if (stock_compare_string_mode == 2) {
    uVar1 = CompareStringA(locale,flags,(PCNZCH)s1,len1,(PCNZCH)s2,len2);
    return uVar1;
  }
  if (stock_compare_string_mode == 1) {
    local_18 = 0;
    local_20 = (LPWSTR)0x0;
    if (code_page == 0) {
      code_page = stock_lc_codepage;
    }
    if ((len1 == 0) || (len2 == 0)) {
      if (len2 == len1) {
        return 2;
      }
      if (1 < (int)len2) {
        return 1;
      }
      if (1 < (int)len1) {
        return 3;
      }
      BVar2 = GetCPInfo(code_page,&local_14);
      if (BVar2 == 0) {
        return 0;
      }
      if (0 < (int)len1) {
        if (local_14.MaxCharSize < 2) {
          return 3;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 3;
          }
          if ((*pBVar3 <= *s1) && (*s1 <= pBVar3[1])) break;
          pBVar3 = pBVar3 + 2;
          local_14.LeadByte[0] = *pBVar3;
        }
        return 2;
      }
      if (0 < (int)len2) {
        if (local_14.MaxCharSize < 2) {
          return 1;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 1;
          }
          if ((*pBVar3 <= *s2) && (*s2 <= pBVar3[1])) break;
          pBVar3 = pBVar3 + 2;
          local_14.LeadByte[0] = *pBVar3;
        }
        return 2;
      }
    }
    local_14.MaxCharSize = MultiByteToWideChar(code_page,9,(LPCSTR)s1,len1,(LPWSTR)0x0,0);
    if (local_14.MaxCharSize == 0) {
      return 0;
    }
    lpWideCharStr = stock_malloc(local_14.MaxCharSize * 2);
    if (lpWideCharStr == (PCNZWCH)0x0) {
      return 0;
    }
    iVar4 = MultiByteToWideChar(code_page,1,(LPCSTR)s1,len1,lpWideCharStr,local_14.MaxCharSize);
    if ((((iVar4 != 0) &&
         (iVar4 = MultiByteToWideChar(code_page,9,(LPCSTR)s2,len2,(LPWSTR)0x0,0), iVar4 != 0)) &&
        (local_20 = stock_malloc(iVar4 * 2), local_20 != (LPWSTR)0x0)) &&
       (iVar5 = MultiByteToWideChar(code_page,1,(LPCSTR)s2,len2,local_20,iVar4), iVar5 != 0)) {
      local_18 = CompareStringW(locale,flags,lpWideCharStr,local_14.MaxCharSize,local_20,iVar4);
    }
    stock_free(lpWideCharStr);
    stock_free(local_20);
  }
  return local_18;
}



