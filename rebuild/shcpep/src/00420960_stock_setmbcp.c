#include "decls.h"
#include "imports.h"

// entry: 00420960
// name : stock_setmbcp
// size : 475
// sig  : int stock_setmbcp(int codepage)


int __cdecl stock_setmbcp(int codepage)

{
  unsigned char _frec_18[24];
#define local_18 (*(int *)(_frec_18 + 0))
#define local_14 (*(_cpinfo *)(_frec_18 + 4))
  byte *pbVar1;
  byte bVar2;
  UINT CodePage;
  UINT *pUVar3;
  BOOL BVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  BYTE *pBVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  
  CodePage = getSystemCP(codepage);
  if (stock_mbcodepage == CodePage) {
    return 0;
  }
  if (CodePage == 0) {
    setSBCS();
    return 0;
  }
  local_18 = 0;
  pUVar3 = &stock_rgcode_page_info;
  do {
    if (*pUVar3 == CodePage) {
      uVar5 = 0;
      puVar10 = &stock_mbctype;
      for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar10 = 0;
        puVar10 = puVar10 + 1;
      }
      *(undefined1 *)puVar10 = 0;
      do {
        pbVar9 = &DAT_00428990 + (uVar5 + local_18 * 6) * 8;
        bVar2 = *pbVar9;
        while ((bVar2 != 0 && (pbVar9[1] != 0))) {
          uVar7 = (uint)*pbVar9;
          if (uVar7 <= pbVar9[1]) {
            bVar2 = (&stock_rgctypeflag)[uVar5];
            do {
              pbVar1 = (byte *)((int)&stock_mbctype + uVar7 + 1);
              *pbVar1 = *pbVar1 | bVar2;
              uVar7 = uVar7 + 1;
            } while (uVar7 <= pbVar9[1]);
          }
          pbVar9 = pbVar9 + 2;
          bVar2 = *pbVar9;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < 4);
      stock_mbcodepage = CodePage;
      stock_mblcid = _CPtoLCID(CodePage);
      stock_mbulinfo = *(undefined4 *)(&DAT_00428984 + local_18 * 0x30);
      DAT_0042896c = *(undefined4 *)(&DAT_00428988 + local_18 * 0x30);
      DAT_00428970 = *(undefined4 *)(local_18 * 0x30 + SD(0x0042898c));
      return 0;
    }
    pUVar3 = pUVar3 + 0xc;
    local_18 = local_18 + 1;
  } while (pUVar3 < &stock_badioinfo);
  BVar4 = GetCPInfo(CodePage,&local_14);
  if (BVar4 == 1) {
    puVar10 = &stock_mbctype;
    for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    *(undefined1 *)puVar10 = 0;
    if (local_14.MaxCharSize < 2) {
      stock_mblcid = 0;
      stock_mbcodepage = 0;
    }
    else {
      pBVar8 = local_14.LeadByte;
      while ((local_14.LeadByte[0] != 0 && (pBVar8[1] != 0))) {
        uVar5 = (uint)*pBVar8;
        if (uVar5 <= pBVar8[1]) {
          do {
            pbVar9 = (byte *)((int)&stock_mbctype + uVar5 + 1);
            *pbVar9 = *pbVar9 | 4;
            uVar5 = uVar5 + 1;
          } while (uVar5 <= pBVar8[1]);
        }
        pBVar8 = pBVar8 + 2;
        local_14.LeadByte[0] = *pBVar8;
      }
      uVar5 = 1;
      do {
        pbVar9 = (byte *)((int)&stock_mbctype + uVar5 + 1);
        *pbVar9 = *pbVar9 | 8;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0xff);
      stock_mbcodepage = CodePage;
      stock_mblcid = _CPtoLCID(CodePage);
    }
    stock_mbulinfo = 0;
    DAT_0042896c = 0;
    DAT_00428970 = 0;
    return 0;
  }
  if (stock_fSystemSet == 0) {
    return -1;
  }
  setSBCS();
  return 0;
#undef local_18
#undef local_14
}



