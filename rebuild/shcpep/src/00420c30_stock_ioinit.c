#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_pioinfo
#define stock_pioinfo (*(int * *)(g_sd + 0x6e50))


// entry: 00420c30
// name : stock_ioinit
// size : 467
// sig  : void stock_ioinit(void)


int __cdecl stock_ioinit(void)

{
  unsigned char _frec_44[68];
#define local_44 (*(_STARTUPINFOA *)(_frec_44 + 0))
  undefined4 *puVar1;
  DWORD DVar2;
  HANDLE hFile;
  UINT *pUVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  int iVar8;
  UINT UVar9;
  UINT UVar10;
  
  puVar1 = stock_malloc(0x100);
  if (puVar1 == (undefined4 *)0x0) {
    __amsg_exit(0x1b);
  }
  stock_nhandle = 0x20;
  stock_pioinfo = puVar1;
  if (puVar1 < puVar1 + 0x40) {
    do {
      *(undefined1 *)(puVar1 + 1) = 0;
      puVar6 = puVar1 + 2;
      *puVar1 = 0xffffffff;
      *(undefined1 *)((int)puVar1 + 5) = 10;
      puVar1 = puVar6;
    } while (puVar6 < stock_pioinfo + 0x40);
  }
  GetStartupInfoA(&local_44);
  if ((local_44.cbReserved2 != 0) && ((UINT *)local_44.lpReserved2 != (UINT *)0x0)) {
    UVar9 = *(UINT *)local_44.lpReserved2;
    pUVar3 = (UINT *)((int)local_44.lpReserved2 + 4);
    pbVar7 = (byte *)(UVar9 + (int)pUVar3);
    if (0x7ff < (int)UVar9) {
      UVar9 = 0x800;
    }
    UVar10 = UVar9;
    if ((int)stock_nhandle < (int)UVar9) {
      piVar4 = &DAT_0042ae54;
      do {
        puVar1 = stock_malloc(0x100);
        UVar10 = stock_nhandle;
        if (puVar1 == (undefined4 *)0x0) break;
        *piVar4 = (int)puVar1;
        stock_nhandle = stock_nhandle + 0x20;
        if (puVar1 < puVar1 + 0x40) {
          do {
            *(undefined1 *)(puVar1 + 1) = 0;
            puVar6 = puVar1 + 2;
            *puVar1 = 0xffffffff;
            *(undefined1 *)((int)puVar1 + 5) = 10;
            puVar1 = puVar6;
          } while (puVar6 < (undefined4 *)(*piVar4 + 0x100));
        }
        piVar4 = piVar4 + 1;
        UVar10 = UVar9;
      } while ((int)stock_nhandle < (int)UVar9);
    }
    uVar5 = 0;
    if (0 < (int)UVar10) {
      do {
        if (((*(HANDLE *)pbVar7 != (HANDLE)0xffffffff) && ((*pUVar3 & 1) != 0)) &&
           (DVar2 = GetFileType(*(HANDLE *)pbVar7), DVar2 != 0)) {
          puVar1 = (undefined4 *)
                   (*(int *)((int)&stock_pioinfo + ((int)(uVar5 & 0xffffffe7) >> 3)) +
                   (uVar5 & 0x1f) * 8);
          *puVar1 = *(undefined4 *)pbVar7;
          *(byte *)(puVar1 + 1) = (byte)*pUVar3;
        }
        uVar5 = uVar5 + 1;
        pUVar3 = (UINT *)((int)pUVar3 + 1);
        pbVar7 = pbVar7 + 4;
      } while ((int)uVar5 < (int)UVar10);
    }
  }
  iVar8 = 0;
  do {
    piVar4 = stock_pioinfo + iVar8 * 2;
    if (*piVar4 == -1) {
      DVar2 = 0xfffffff6;
      *(undefined1 *)(piVar4 + 1) = 0x81;
      if (iVar8 != 0) {
        DVar2 = (iVar8 == 1) - 0xc;
      }
      hFile = GetStdHandle(DVar2);
      if ((hFile == (HANDLE)0xffffffff) || (DVar2 = GetFileType(hFile), DVar2 == 0)) {
        *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 0x40;
      }
      else {
        *piVar4 = (int)hFile;
        if ((DVar2 & 0xff) == 2) {
          *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 0x40;
        }
        else if ((DVar2 & 0xff) == 3) {
          *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 8;
        }
      }
    }
    else {
      *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 0x80;
    }
    iVar8 = iVar8 + 1;
  } while (iVar8 < 3);
  SetHandleCount(stock_nhandle);
  return;
#undef local_44
}



