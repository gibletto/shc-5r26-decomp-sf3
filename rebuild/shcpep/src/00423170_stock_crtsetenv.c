#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x4488))
#undef stock_initenv
#define stock_initenv (*(int * *)(g_sd + 0x448c))
#undef stock_wenviron
#define stock_wenviron (*(int * *)(g_sd + 0x4490))


// entry: 00423170
// name : stock_crtsetenv
// size : 592
// sig  : int stock_crtsetenv(uchar * option, int primary)


int __cdecl stock_crtsetenv(uchar *option,int primary)

{
  uchar uVar1;
  int iVar2;
  int *piVar3;
  uchar *puVar4;
  int iVar5;
  int *piVar6;
  uchar *puVar7;
  uint uVar8;
  uint uVar9;
  uchar *puVar10;
  uchar *puVar11;
  bool bVar12;
  
  if (((option == (uchar *)0x0) || (puVar4 = __mbschr(option,0x3d), puVar4 == (uchar *)0x0)) ||
     (puVar4 == option)) {
    return -1;
  }
  bVar12 = puVar4[1] == '\0';
  if (stock_environ == stock_initenv) {
    stock_environ = copy_environ(stock_environ);
  }
  if (stock_environ == (int *)0x0) {
    if ((primary == 0) || (stock_wenviron == (undefined4 *)0x0)) {
      if (bVar12) {
        return 0;
      }
      stock_environ = stock_malloc(4);
      if (stock_environ == (int *)0x0) {
        return -1;
      }
      *stock_environ = 0;
      if (stock_wenviron == (undefined4 *)0x0) {
        stock_wenviron = stock_malloc(4);
        if (stock_wenviron == (undefined4 *)0x0) {
          return -1;
        }
        *stock_wenviron = 0;
      }
    }
    else {
      iVar5 = ___wtomb_environ();
      if (iVar5 != 0) {
        return -1;
      }
    }
  }
  piVar6 = stock_environ;
  iVar5 = findenv(option,(int)puVar4 - (int)option);
  if ((iVar5 < 0) || (*piVar6 == 0)) {
    if (bVar12) {
      return 0;
    }
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }
    piVar6 = stock_realloc(piVar6,iVar5 * 4 + 8);
    if (piVar6 == (int *)0x0) {
      return -1;
    }
    piVar6[iVar5] = (int)option;
    (piVar6 + iVar5)[1] = 0;
  }
  else {
    if (!bVar12) {
      piVar6[iVar5] = (int)option;
      goto LAB_00423332;
    }
    piVar3 = piVar6 + iVar5;
    stock_free((void *)*piVar3);
    iVar2 = *piVar3;
    while (iVar2 != 0) {
      iVar5 = iVar5 + 1;
      *piVar3 = piVar3[1];
      iVar2 = piVar3[1];
      piVar3 = piVar3 + 1;
    }
    piVar6 = stock_realloc(piVar6,iVar5 << 2);
    if (piVar6 == (int *)0x0) goto LAB_00423332;
  }
  stock_environ = piVar6;
LAB_00423332:
  if (primary != 0) {
    uVar8 = 0xffffffff;
    puVar7 = option;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      uVar1 = *puVar7;
      puVar7 = puVar7 + 1;
    } while (uVar1 != '\0');
    puVar7 = stock_malloc(~uVar8 + 1);
    if (puVar7 != (uchar *)0x0) {
      uVar8 = 0xffffffff;
      puVar10 = option;
      do {
        puVar11 = puVar10;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        puVar11 = puVar10 + 1;
        uVar1 = *puVar10;
        puVar10 = puVar11;
      } while (uVar1 != '\0');
      uVar8 = ~uVar8;
      puVar10 = puVar11 + -uVar8;
      puVar11 = puVar7;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)puVar11 = *(undefined4 *)puVar10;
        puVar10 = puVar10 + 4;
        puVar11 = puVar11 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      puVar7[(int)puVar4 - (int)option] = '\0';
      SetEnvironmentVariableA
                ((LPCSTR)puVar7,
                 (LPCSTR)(-(uint)!bVar12 & (uint)(puVar7 + ((int)puVar4 - (int)option) + 1)));
      stock_free(puVar7);
    }
  }
  return 0;
}



