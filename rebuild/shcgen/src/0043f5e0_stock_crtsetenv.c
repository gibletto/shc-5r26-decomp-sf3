#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(char ** *)(g_sd + 0x1ca48))
#undef stock_initenv
#define stock_initenv (*(char ** *)(g_sd + 0x1ca4c))
#undef stock_wenviron
#define stock_wenviron (*(int * *)(g_sd + 0x1ca50))


// entry: 0043f5e0
// name : stock_crtsetenv
// size : 592
// sig  : int stock_crtsetenv(uchar * option, int primary)


int __cdecl stock_crtsetenv(uchar *option,int primary)

{
  char *pcVar1;
  uchar *equals;
  int iVar2;
  char **env;
  uchar *puVar3;
  uint uVar4;
  uint n_words;
  uchar *puVar5;
  uchar *puVar6;
  bool removing;
  uchar ch;
  char **slot;
  
  if (((option == (uchar *)0x0) || (equals = stock_mbschr(option,0x3d), equals == (uchar *)0x0)) ||
     (equals == option)) {
    return -1;
  }
  removing = equals[1] == '\0';
  if (stock_environ == stock_initenv) {
    stock_environ = stock_copy_environ(stock_environ);
  }
  if (stock_environ == (char **)0x0) {
    if ((primary == 0) || (stock_wenviron == (undefined4 *)0x0)) {
      if (removing) {
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
      iVar2 = stock_wtomb_environ();
      if (iVar2 != 0) {
        return -1;
      }
    }
  }
  env = stock_environ;
  iVar2 = stock_findenv(option,(int)equals - (int)option);
  if ((iVar2 < 0) || (*env == (char *)0x0)) {
    if (removing) {
      return 0;
    }
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    env = stock_realloc(env,iVar2 * 4 + 8);
    if (env == (char **)0x0) {
      return -1;
    }
    env[iVar2] = (char *)option;
    (env + iVar2)[1] = (char *)0x0;
  }
  else {
    if (!removing) {
      env[iVar2] = (char *)option;
      goto LAB_0043f7a2;
    }
    slot = env + iVar2;
    stock_free(*slot);
    pcVar1 = *slot;
    while (pcVar1 != (char *)0x0) {
      iVar2 = iVar2 + 1;
      *slot = slot[1];
      pcVar1 = slot[1];
      slot = slot + 1;
    }
    env = stock_realloc(env,iVar2 << 2);
    if (env == (char **)0x0) goto LAB_0043f7a2;
  }
  stock_environ = env;
LAB_0043f7a2:
  if (primary != 0) {
    uVar4 = 0xffffffff;
    puVar3 = option;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      ch = *puVar3;
      puVar3 = puVar3 + 1;
    } while (ch != '\0');
    puVar3 = stock_malloc(~uVar4 + 1);
    if (puVar3 != (uchar *)0x0) {
      uVar4 = 0xffffffff;
      puVar5 = option;
      do {
        puVar6 = puVar5;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        puVar6 = puVar5 + 1;
        ch = *puVar5;
        puVar5 = puVar6;
      } while (ch != '\0');
      uVar4 = ~uVar4;
      puVar5 = puVar6 + -uVar4;
      puVar6 = puVar3;
      for (n_words = uVar4 >> 2; n_words != 0; n_words = n_words - 1) {
        *(undefined4 *)puVar6 = *(undefined4 *)puVar5;
        puVar5 = puVar5 + 4;
        puVar6 = puVar6 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar3[(int)equals - (int)option] = '\0';
      SetEnvironmentVariableA
                ((LPCSTR)puVar3,
                 (LPCSTR)(-(uint)!removing & (uint)(puVar3 + ((int)equals - (int)option) + 1)));
      stock_free(puVar3);
    }
  }
  return 0;
}



