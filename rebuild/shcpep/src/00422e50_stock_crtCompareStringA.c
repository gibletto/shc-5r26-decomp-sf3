#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_lc_codepage
#define stock_lc_codepage (*(unsigned int *)(g_sd + 0x51c8))


// entry: 00422e50
// name : stock_crtCompareStringA
// size : 749
// sig  : int stock_crtCompareStringA(uint locale, uint flags, uchar * str1, uint cnt1, uchar * str2, uint cnt2, uint code_page)


int __cdecl
stock_crtCompareStringA
          (uint locale,uint flags,uchar *str1,uint cnt1,uchar *str2,uint cnt2,uint code_page)

{
  size_t in_EAX;
  int iVar1;
  BOOL BVar2;
  BYTE *pBVar3;
  PCNZWCH lpWideCharStr;
  int iVar4;
  LPWSTR local_20;
  size_t local_18;
  _cpinfo local_14;
  
  if (stock_f_use_CompareString == 0) {
    in_EAX = CompareStringA(0,0,&DAT_00429220,1,&DAT_00429220,1);
    if (in_EAX == 0) {
      in_EAX = CompareStringW(0,0,(PCNZWCH)&DAT_00429224,1,(PCNZWCH)&DAT_00429224,1);
      if (in_EAX == 0) {
        return 0;
      }
      stock_f_use_CompareString = 1;
    }
    else {
      stock_f_use_CompareString = 2;
    }
  }
  local_18 = in_EAX;
  if (0 < (int)cnt1) {
    local_18 = _strncnt((char *)str1,cnt1);
    cnt1 = local_18;
  }
  if (0 < (int)cnt2) {
    local_18 = _strncnt((char *)str2,cnt2);
    cnt2 = local_18;
  }
  if (stock_f_use_CompareString == 2) {
    iVar1 = CompareStringA(locale,flags,(PCNZCH)str1,cnt1,(PCNZCH)str2,cnt2);
    return iVar1;
  }
  if (stock_f_use_CompareString == 1) {
    local_18 = 0;
    local_20 = (LPWSTR)0x0;
    if (code_page == 0) {
      code_page = stock_lc_codepage;
    }
    if ((cnt1 == 0) || (cnt2 == 0)) {
      if (cnt2 == cnt1) {
        return 2;
      }
      if (1 < (int)cnt2) {
        return 1;
      }
      if (1 < (int)cnt1) {
        return 3;
      }
      BVar2 = GetCPInfo(code_page,&local_14);
      if (BVar2 == 0) {
        return 0;
      }
      if (0 < (int)cnt1) {
        if (local_14.MaxCharSize < 2) {
          return 3;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 3;
          }
          if ((*pBVar3 <= *str1) && (*str1 <= pBVar3[1])) break;
          pBVar3 = pBVar3 + 2;
          local_14.LeadByte[0] = *pBVar3;
        }
        return 2;
      }
      if (0 < (int)cnt2) {
        if (local_14.MaxCharSize < 2) {
          return 1;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 1;
          }
          if ((*pBVar3 <= *str2) && (*str2 <= pBVar3[1])) break;
          pBVar3 = pBVar3 + 2;
          local_14.LeadByte[0] = *pBVar3;
        }
        return 2;
      }
    }
    local_14.MaxCharSize = MultiByteToWideChar(code_page,9,(LPCSTR)str1,cnt1,(LPWSTR)0x0,0);
    if (local_14.MaxCharSize == 0) {
      return 0;
    }
    lpWideCharStr = stock_malloc(local_14.MaxCharSize * 2);
    if (lpWideCharStr == (PCNZWCH)0x0) {
      return 0;
    }
    iVar1 = MultiByteToWideChar(code_page,1,(LPCSTR)str1,cnt1,lpWideCharStr,local_14.MaxCharSize);
    if ((((iVar1 != 0) &&
         (iVar1 = MultiByteToWideChar(code_page,9,(LPCSTR)str2,cnt2,(LPWSTR)0x0,0), iVar1 != 0)) &&
        (local_20 = stock_malloc(iVar1 * 2), local_20 != (LPWSTR)0x0)) &&
       (iVar4 = MultiByteToWideChar(code_page,1,(LPCSTR)str2,cnt2,local_20,iVar1), iVar4 != 0)) {
      local_18 = CompareStringW(locale,flags,lpWideCharStr,local_14.MaxCharSize,local_20,iVar1);
    }
    stock_free(lpWideCharStr);
    stock_free(local_20);
  }
  return local_18;
}



