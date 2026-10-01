#include "decls.h"
#include "imports.h"

// entry: 004207c0
// name : stock_crtGetEnvironmentStringsA
// size : 411
// sig  : char * stock_crtGetEnvironmentStringsA(void)


char * __cdecl stock_crtGetEnvironmentStringsA(void)

{
  char cVar1;
  WCHAR WVar2;
  LPWCH pWVar3;
  uint uVar4;
  LPSTR lpMultiByteStr;
  char *pcVar5;
  LPWCH pWVar6;
  char *size;
  WCHAR *pWVar7;
  int iVar9;
  char *pcVar10;
  LPWCH local_4;
  WCHAR *pWVar8;
  
  pWVar3 = local_4;
  if (stock_f_use_GetEnvironmentStrings == 0) {
    pWVar3 = GetEnvironmentStringsW();
    if (pWVar3 == (LPWCH)0x0) {
      local_4 = (LPWCH)GetEnvironmentStrings();
      if (local_4 == (LPWCH)0x0) {
        return (char *)0x0;
      }
      stock_f_use_GetEnvironmentStrings = 2;
    }
    else {
      stock_f_use_GetEnvironmentStrings = 1;
    }
  }
  if (stock_f_use_GetEnvironmentStrings != 1) {
    if (stock_f_use_GetEnvironmentStrings != 2) {
      return (char *)0x0;
    }
    if ((local_4 == (LPWCH)0x0) && (local_4 = (LPWCH)GetEnvironmentStrings(), local_4 == (LPWCH)0x0)
       ) {
      return (char *)0x0;
    }
    cVar1 = (char)*local_4;
    pWVar3 = local_4;
    while (cVar1 != '\0') {
      do {
        pWVar6 = pWVar3;
        pWVar3 = (LPWCH)((int)pWVar6 + 1);
      } while (*(char *)pWVar3 != '\0');
      pWVar3 = pWVar6 + 1;
      cVar1 = (char)*pWVar3;
    }
    size = (char *)((int)pWVar3 + (1 - (int)local_4));
    pcVar5 = stock_malloc((uint)size);
    if (pcVar5 == (char *)0x0) {
      FreeEnvironmentStringsA((LPCH)local_4);
      return (char *)0x0;
    }
    pWVar3 = local_4;
    pcVar10 = pcVar5;
    for (uVar4 = (uint)size >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pWVar3;
      pWVar3 = pWVar3 + 2;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar4 = (uint)size & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar10 = (char)*pWVar3;
      pWVar3 = (LPWCH)((int)pWVar3 + 1);
      pcVar10 = pcVar10 + 1;
    }
    FreeEnvironmentStringsA((LPCH)local_4);
    return pcVar5;
  }
  if ((pWVar3 == (LPWCH)0x0) && (pWVar3 = GetEnvironmentStringsW(), pWVar3 == (LPWCH)0x0)) {
    return (char *)0x0;
  }
  WVar2 = *pWVar3;
  pWVar7 = pWVar3;
  while (WVar2 != L'\0') {
    do {
      pWVar8 = pWVar7;
      pWVar7 = pWVar8 + 1;
    } while (*pWVar7 != L'\0');
    pWVar7 = pWVar8 + 2;
    WVar2 = *pWVar7;
  }
  iVar9 = ((int)pWVar7 - (int)pWVar3 >> 1) + 1;
  uVar4 = WideCharToMultiByte(0,0,pWVar3,iVar9,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
  if ((uVar4 != 0) && (lpMultiByteStr = stock_malloc(uVar4), lpMultiByteStr != (LPSTR)0x0)) {
    iVar9 = WideCharToMultiByte(0,0,pWVar3,iVar9,lpMultiByteStr,uVar4,(LPCSTR)0x0,(LPBOOL)0x0);
    if (iVar9 == 0) {
      stock_free(lpMultiByteStr);
      lpMultiByteStr = (LPSTR)0x0;
    }
    FreeEnvironmentStringsW(pWVar3);
    return lpMultiByteStr;
  }
  FreeEnvironmentStringsW(pWVar3);
  return (char *)0x0;
}



