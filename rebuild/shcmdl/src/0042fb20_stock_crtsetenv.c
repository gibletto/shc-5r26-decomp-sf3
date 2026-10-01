#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(char ** *)(g_sd + 0x4088))
#undef stock_environ_initial
#define stock_environ_initial (*(char ** *)(g_sd + 0x408c))
#undef stock_wenviron
#define stock_wenviron (*(int * *)(g_sd + 0x4090))


// entry: 0042fb20
// name : stock_crtsetenv
// size : 592
// sig  : int stock_crtsetenv(uchar * option, int primary)


int __cdecl stock_crtsetenv(uchar *option,int primary)

{
  uchar uVar1;
  char *pcVar2;
  char **ppcVar3;
  uchar *puVar4;
  int iVar5;
  char **ppcVar6;
  uchar *puVar7;
  uint uVar8;
  uint uVar9;
  uchar *puVar10;
  uchar *puVar11;
  bool bVar12;
  
  if (((option == (uchar *)0x0) || (puVar4 = stock_mbschr(option,0x3d), puVar4 == (uchar *)0x0)) ||
     (puVar4 == option)) {
    return -1;
  }
  bVar12 = puVar4[1] == '\0';
  if (stock_environ == stock_environ_initial) {
    stock_environ = stock_copy_environ(stock_environ);
  }
  if (stock_environ == (char **)0x0) {
    if ((primary == 0) || (stock_wenviron == (undefined4 *)0x0)) {
      if (bVar12) {
        return 0;
      }
      stock_environ = stock_malloc(4);
      if (stock_environ == (char **)0x0) {
        return -1;
      }
      *stock_environ = (char *)0x0;
      if (stock_wenviron == (undefined4 *)0x0) {
        stock_wenviron = stock_malloc(4);
        if (stock_wenviron == (undefined4 *)0x0) {
          return -1;
        }
        *stock_wenviron = 0;
      }
    }
    else {
      iVar5 = stock_wtomb_environ();
      if (iVar5 != 0) {
        return -1;
      }
    }
  }
  ppcVar6 = stock_environ;
  iVar5 = stock_findenv(option,(int)puVar4 - (int)option);
  if ((iVar5 < 0) || (*ppcVar6 == (char *)0x0)) {
    if (bVar12) {
      return 0;
    }
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }
    ppcVar6 = stock_realloc(ppcVar6,iVar5 * 4 + 8);
    if (ppcVar6 == (char **)0x0) {
      return -1;
    }
    ppcVar6[iVar5] = (char *)option;
    (ppcVar6 + iVar5)[1] = (char *)0x0;
  }
  else {
    if (!bVar12) {
      ppcVar6[iVar5] = (char *)option;
      goto LAB_0042fce2;
    }
    ppcVar3 = ppcVar6 + iVar5;
    stock_free(*ppcVar3);
    pcVar2 = *ppcVar3;
    while (pcVar2 != (char *)0x0) {
      iVar5 = iVar5 + 1;
      *ppcVar3 = ppcVar3[1];
      pcVar2 = ppcVar3[1];
      ppcVar3 = ppcVar3 + 1;
    }
    ppcVar6 = stock_realloc(ppcVar6,iVar5 << 2);
    if (ppcVar6 == (char **)0x0) goto LAB_0042fce2;
  }
  stock_environ = ppcVar6;
LAB_0042fce2:
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



