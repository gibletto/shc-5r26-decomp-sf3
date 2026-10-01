#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_lc_codepage
#define stock_lc_codepage (*(unsigned int *)(g_sd + 0x8ed0))


// entry: 0043a010
// name : stock_crtCompareStringA
// size : 749
// sig  : int stock_crtCompareStringA(uint locale, uint flags, uchar * str1, uint cnt1, uchar * str2, uint cnt2, uint code_page)


int __cdecl
stock_crtCompareStringA
          (uint locale,uint flags,uchar *str1,uint cnt1,uchar *str2,uint cnt2,uint code_page)

{
  size_t in_EAX;
  int iVar1;
  BOOL ok;
  BYTE *lead_range;
  PCNZWCH lpWideCharStr;
  int wlen2_done;
  LPWSTR wbuf2;
  size_t retval;
  _cpinfo cp_info;
  
  if (stock_f_use_CompareString == 0) {
    in_EAX = CompareStringA(0,0,&DAT_00443f7c,1,&DAT_00443f7c,1);
    if (in_EAX == 0) {
      in_EAX = CompareStringW(0,0,(PCNZWCH)&DAT_00443f80,1,(PCNZWCH)&DAT_00443f80,1);
      if (in_EAX == 0) {
        return 0;
      }
      stock_f_use_CompareString = 1;
    }
    else {
      stock_f_use_CompareString = 2;
    }
  }
  retval = in_EAX;
  if (0 < (int)cnt1) {
    retval = _strncnt((char *)str1,cnt1);
    cnt1 = retval;
  }
  if (0 < (int)cnt2) {
    retval = _strncnt((char *)str2,cnt2);
    cnt2 = retval;
  }
  if (stock_f_use_CompareString == 2) {
    iVar1 = CompareStringA(locale,flags,(PCNZCH)str1,cnt1,(PCNZCH)str2,cnt2);
    return iVar1;
  }
  if (stock_f_use_CompareString == 1) {
    retval = 0;
    wbuf2 = (LPWSTR)0x0;
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
      ok = GetCPInfo(code_page,&cp_info);
      if (ok == 0) {
        return 0;
      }
      if (0 < (int)cnt1) {
        if (cp_info.MaxCharSize < 2) {
          return 3;
        }
        lead_range = cp_info.LeadByte;
        while( true ) {
          if ((cp_info.LeadByte[0] == 0) || (lead_range[1] == 0)) {
            return 3;
          }
          if ((*lead_range <= *str1) && (*str1 <= lead_range[1])) break;
          lead_range = lead_range + 2;
          cp_info.LeadByte[0] = *lead_range;
        }
        return 2;
      }
      if (0 < (int)cnt2) {
        if (cp_info.MaxCharSize < 2) {
          return 1;
        }
        lead_range = cp_info.LeadByte;
        while( true ) {
          if ((cp_info.LeadByte[0] == 0) || (lead_range[1] == 0)) {
            return 1;
          }
          if ((*lead_range <= *str2) && (*str2 <= lead_range[1])) break;
          lead_range = lead_range + 2;
          cp_info.LeadByte[0] = *lead_range;
        }
        return 2;
      }
    }
    cp_info.MaxCharSize = MultiByteToWideChar(code_page,9,(LPCSTR)str1,cnt1,(LPWSTR)0x0,0);
    if (cp_info.MaxCharSize == 0) {
      return 0;
    }
    lpWideCharStr = stock_malloc(cp_info.MaxCharSize * 2);
    if (lpWideCharStr == (PCNZWCH)0x0) {
      return 0;
    }
    iVar1 = MultiByteToWideChar(code_page,1,(LPCSTR)str1,cnt1,lpWideCharStr,cp_info.MaxCharSize);
    if ((((iVar1 != 0) &&
         (iVar1 = MultiByteToWideChar(code_page,9,(LPCSTR)str2,cnt2,(LPWSTR)0x0,0), iVar1 != 0)) &&
        (wbuf2 = stock_malloc(iVar1 * 2), wbuf2 != (LPWSTR)0x0)) &&
       (wlen2_done = MultiByteToWideChar(code_page,1,(LPCSTR)str2,cnt2,wbuf2,iVar1), wlen2_done != 0
       )) {
      retval = CompareStringW(locale,flags,lpWideCharStr,cp_info.MaxCharSize,wbuf2,iVar1);
    }
    stock_free(lpWideCharStr);
    stock_free(wbuf2);
  }
  return retval;
}



