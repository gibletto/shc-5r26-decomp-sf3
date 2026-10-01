#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_lc_codepage
#define stock_lc_codepage (*(unsigned int *)(g_sd + 0x1d778))


// entry: 0043f2c0
// name : stock_crtCompareStringA
// size : 749
// sig  : int stock_crtCompareStringA(uint locale, uint flags, uchar * str1, uint cnt1, uchar * str2, uint cnt2, uint code_page)


int __cdecl
stock_crtCompareStringA
          (uint locale,uint flags,uchar *str1,uint cnt1,uchar *str2,uint cnt2,uint code_page)

{
  uint in_EAX;
  int iVar1;
  BOOL got_info;
  BYTE *lead_range;
  PCNZWCH wide1;
  int converted;
  LPWSTR wide2;
  uint cmp_result;
  _cpinfo cp_info;
  
  if (stock_f_use_CompareString == 0) {
    in_EAX = CompareStringA(0,0,&DAT_0045d7ec,1,&DAT_0045d7ec,1);
    if (in_EAX == 0) {
      in_EAX = CompareStringW(0,0,(PCNZWCH)&DAT_0045d7f0,1,(PCNZWCH)&DAT_0045d7f0,1);
      if (in_EAX == 0) {
        return 0;
      }
      stock_f_use_CompareString = 1;
    }
    else {
      stock_f_use_CompareString = 2;
    }
  }
  cmp_result = in_EAX;
  if (0 < (int)cnt1) {
    cmp_result = stock_strncnt((char *)str1,cnt1);
    cnt1 = cmp_result;
  }
  if (0 < (int)cnt2) {
    cmp_result = stock_strncnt((char *)str2,cnt2);
    cnt2 = cmp_result;
  }
  if (stock_f_use_CompareString == 2) {
    iVar1 = CompareStringA(locale,flags,(PCNZCH)str1,cnt1,(PCNZCH)str2,cnt2);
    return iVar1;
  }
  if (stock_f_use_CompareString == 1) {
    cmp_result = 0;
    wide2 = (LPWSTR)0x0;
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
      got_info = GetCPInfo(code_page,&cp_info);
      if (got_info == 0) {
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
    wide1 = stock_malloc(cp_info.MaxCharSize * 2);
    if (wide1 == (PCNZWCH)0x0) {
      return 0;
    }
    iVar1 = MultiByteToWideChar(code_page,1,(LPCSTR)str1,cnt1,wide1,cp_info.MaxCharSize);
    if ((((iVar1 != 0) &&
         (iVar1 = MultiByteToWideChar(code_page,9,(LPCSTR)str2,cnt2,(LPWSTR)0x0,0), iVar1 != 0)) &&
        (wide2 = stock_malloc(iVar1 * 2), wide2 != (LPWSTR)0x0)) &&
       (converted = MultiByteToWideChar(code_page,1,(LPCSTR)str2,cnt2,wide2,iVar1), converted != 0))
    {
      cmp_result = CompareStringW(locale,flags,wide1,cp_info.MaxCharSize,wide2,iVar1);
    }
    stock_free(wide1);
    stock_free(wide2);
  }
  return cmp_result;
}



