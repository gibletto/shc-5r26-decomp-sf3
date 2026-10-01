#include "decls.h"
#include "imports.h"

// entry: 00436180
// name : stock_setmbcp
// size : 475
// sig  : int stock_setmbcp(int codepage)


int __cdecl stock_setmbcp(int codepage)

{
  unsigned char _frec_18[24];
#define cp_index (*(int *)(_frec_18 + 0))
#define cp_info (*(_cpinfo *)(_frec_18 + 4))
  byte bVar1;
  UINT CodePage;
  UINT *cp_entry;
  BOOL BVar2;
  uint i;
  int n;
  uint ch;
  BYTE *lead_range;
  byte *pbVar3;
  undefined4 *dst;
  byte *ctype_byte;
  
  CodePage = getSystemCP(codepage);
  if (stock_mbcodepage == CodePage) {
    return 0;
  }
  if (CodePage == 0) {
    setSBCS();
    return 0;
  }
  cp_index = 0;
  cp_entry = &stock_rgcode_page_info;
  do {
    if (*cp_entry == CodePage) {
      i = 0;
      dst = &stock_mbctype;
      for (n = 0x40; n != 0; n = n + -1) {
        *dst = 0;
        dst = dst + 1;
      }
      *(undefined1 *)dst = 0;
      do {
        pbVar3 = &DAT_00443610 + (i + cp_index * 6) * 8;
        bVar1 = *pbVar3;
        while ((bVar1 != 0 && (pbVar3[1] != 0))) {
          ch = (uint)*pbVar3;
          if (ch <= pbVar3[1]) {
            bVar1 = (&stock_rgctypeflag)[i];
            do {
              ctype_byte = (byte *)((int)&stock_mbctype + ch + 1);
              *ctype_byte = *ctype_byte | bVar1;
              ch = ch + 1;
            } while (ch <= pbVar3[1]);
          }
          pbVar3 = pbVar3 + 2;
          bVar1 = *pbVar3;
        }
        i = i + 1;
      } while (i < 4);
      stock_mbcodepage = CodePage;
      stock_mblcid = _CPtoLCID(CodePage);
      stock_mbulinfo = *(undefined4 *)(&DAT_00443604 + cp_index * 0x30);
      DAT_004435ec = *(undefined4 *)(&DAT_00443608 + cp_index * 0x30);
      DAT_004435f0 = *(undefined4 *)(cp_index * 0x30 + SD(0x0044360c));
      return 0;
    }
    cp_entry = cp_entry + 0xc;
    cp_index = cp_index + 1;
  } while (cp_entry < &stock_newmode);
  BVar2 = GetCPInfo(CodePage,&cp_info);
  if (BVar2 == 1) {
    dst = &stock_mbctype;
    for (n = 0x40; n != 0; n = n + -1) {
      *dst = 0;
      dst = dst + 1;
    }
    *(undefined1 *)dst = 0;
    if (cp_info.MaxCharSize < 2) {
      stock_mblcid = 0;
      stock_mbcodepage = 0;
    }
    else {
      lead_range = cp_info.LeadByte;
      while ((cp_info.LeadByte[0] != 0 && (lead_range[1] != 0))) {
        i = (uint)*lead_range;
        if (i <= lead_range[1]) {
          do {
            pbVar3 = (byte *)((int)&stock_mbctype + i + 1);
            *pbVar3 = *pbVar3 | 4;
            i = i + 1;
          } while (i <= lead_range[1]);
        }
        lead_range = lead_range + 2;
        cp_info.LeadByte[0] = *lead_range;
      }
      i = 1;
      do {
        pbVar3 = (byte *)((int)&stock_mbctype + i + 1);
        *pbVar3 = *pbVar3 | 8;
        i = i + 1;
      } while (i < 0xff);
      stock_mbcodepage = CodePage;
      stock_mblcid = _CPtoLCID(CodePage);
    }
    stock_mbulinfo = 0;
    DAT_004435ec = 0;
    DAT_004435f0 = 0;
    return 0;
  }
  if (stock_fSystemSet == 0) {
    return -1;
  }
  setSBCS();
  return 0;
#undef cp_index
#undef cp_info
}



