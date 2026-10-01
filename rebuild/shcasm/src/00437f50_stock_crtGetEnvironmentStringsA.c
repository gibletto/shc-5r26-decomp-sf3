#include "decls.h"
#include "imports.h"

// entry: 00437f50
// name : stock_crtGetEnvironmentStringsA
// size : 411
// sig  : char * stock_crtGetEnvironmentStringsA(void)


char * __cdecl stock_crtGetEnvironmentStringsA(void)

{
  uint uVar1;
  LPSTR aenv;
  char *aenv_copy;
  LPWCH prev;
  LPWCH pWVar2;
  char *size;
  WCHAR *wscan;
  int iVar3;
  char *dst;
  LPWCH env_block;
  WCHAR *wprev;
  char ch;
  WCHAR wch;
  
  prev = env_block;
  if (stock_f_use_GetEnvironmentStrings == 0) {
    prev = GetEnvironmentStringsW();
    if (prev == (LPWCH)0x0) {
      env_block = (LPWCH)GetEnvironmentStrings();
      if (env_block == (LPWCH)0x0) {
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
    if ((env_block == (LPWCH)0x0) &&
       (env_block = (LPWCH)GetEnvironmentStrings(), env_block == (LPWCH)0x0)) {
      return (char *)0x0;
    }
    ch = (char)*env_block;
    prev = env_block;
    while (ch != '\0') {
      do {
        pWVar2 = prev;
        prev = (LPWCH)((int)pWVar2 + 1);
      } while (*(char *)prev != '\0');
      prev = pWVar2 + 1;
      ch = (char)*prev;
    }
    size = (char *)((int)prev + (1 - (int)env_block));
    aenv_copy = stock_malloc((uint)size);
    if (aenv_copy == (char *)0x0) {
      FreeEnvironmentStringsA((LPCH)env_block);
      return (char *)0x0;
    }
    prev = env_block;
    dst = aenv_copy;
    for (uVar1 = (uint)size >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined4 *)dst = *(undefined4 *)prev;
      prev = prev + 2;
      dst = dst + 4;
    }
    for (uVar1 = (uint)size & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *dst = (char)*prev;
      prev = (LPWCH)((int)prev + 1);
      dst = dst + 1;
    }
    FreeEnvironmentStringsA((LPCH)env_block);
    return aenv_copy;
  }
  if ((prev == (LPWCH)0x0) && (prev = GetEnvironmentStringsW(), prev == (LPWCH)0x0)) {
    return (char *)0x0;
  }
  wch = *prev;
  wscan = prev;
  while (wch != L'\0') {
    do {
      wprev = wscan;
      wscan = wprev + 1;
    } while (*wscan != L'\0');
    wscan = wprev + 2;
    wch = *wscan;
  }
  iVar3 = ((int)wscan - (int)prev >> 1) + 1;
  uVar1 = WideCharToMultiByte(0,0,prev,iVar3,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
  if ((uVar1 != 0) && (aenv = stock_malloc(uVar1), aenv != (LPSTR)0x0)) {
    iVar3 = WideCharToMultiByte(0,0,prev,iVar3,aenv,uVar1,(LPCSTR)0x0,(LPBOOL)0x0);
    if (iVar3 == 0) {
      stock_free(aenv);
      aenv = (LPSTR)0x0;
    }
    FreeEnvironmentStringsW(prev);
    return aenv;
  }
  FreeEnvironmentStringsW(prev);
  return (char *)0x0;
}



