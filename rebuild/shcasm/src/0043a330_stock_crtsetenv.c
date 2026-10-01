#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x81d8))
#undef stock_initenv
#define stock_initenv (*(int * *)(g_sd + 0x81dc))
#undef stock_wenviron
#define stock_wenviron (*(int * *)(g_sd + 0x81e0))


// entry: 0043a330
// name : stock_crtsetenv
// size : 592
// sig  : int stock_crtsetenv(uchar * option, int primary)


int __cdecl stock_crtsetenv(uchar *option,int primary)

{
  uchar *equal;
  int ix;
  int *env;
  uchar *name_copy;
  uint uVar1;
  uint n;
  uchar *src;
  uchar *dst;
  bool is_delete;
  uchar ch;
  int next_entry;
  int *slot;
  
  if (((option == (uchar *)0x0) || (equal = __mbschr(option,0x3d), equal == (uchar *)0x0)) ||
     (equal == option)) {
    return -1;
  }
  is_delete = equal[1] == '\0';
  if (stock_environ == stock_initenv) {
    stock_environ = copy_environ(stock_environ);
  }
  if (stock_environ == (int *)0x0) {
    if ((primary == 0) || (stock_wenviron == (undefined4 *)0x0)) {
      if (is_delete) {
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
      ix = ___wtomb_environ();
      if (ix != 0) {
        return -1;
      }
    }
  }
  env = stock_environ;
  ix = findenv(option,(int)equal - (int)option);
  if ((ix < 0) || (*env == 0)) {
    if (is_delete) {
      return 0;
    }
    if (ix < 0) {
      ix = -ix;
    }
    env = stock_realloc(env,ix * 4 + 8);
    if (env == (int *)0x0) {
      return -1;
    }
    env[ix] = (int)option;
    (env + ix)[1] = 0;
  }
  else {
    if (!is_delete) {
      env[ix] = (int)option;
      goto LAB_0043a4f2;
    }
    slot = env + ix;
    stock_free((void *)*slot);
    next_entry = *slot;
    while (next_entry != 0) {
      ix = ix + 1;
      *slot = slot[1];
      next_entry = slot[1];
      slot = slot + 1;
    }
    env = stock_realloc(env,ix << 2);
    if (env == (int *)0x0) goto LAB_0043a4f2;
  }
  stock_environ = env;
LAB_0043a4f2:
  if (primary != 0) {
    uVar1 = 0xffffffff;
    name_copy = option;
    do {
      if (uVar1 == 0) break;
      uVar1 = uVar1 - 1;
      ch = *name_copy;
      name_copy = name_copy + 1;
    } while (ch != '\0');
    name_copy = stock_malloc(~uVar1 + 1);
    if (name_copy != (uchar *)0x0) {
      uVar1 = 0xffffffff;
      src = option;
      do {
        dst = src;
        if (uVar1 == 0) break;
        uVar1 = uVar1 - 1;
        dst = src + 1;
        ch = *src;
        src = dst;
      } while (ch != '\0');
      uVar1 = ~uVar1;
      src = dst + -uVar1;
      dst = name_copy;
      for (n = uVar1 >> 2; n != 0; n = n - 1) {
        *(undefined4 *)dst = *(undefined4 *)src;
        src = src + 4;
        dst = dst + 4;
      }
      for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
        *dst = *src;
        src = src + 1;
        dst = dst + 1;
      }
      name_copy[(int)equal - (int)option] = '\0';
      SetEnvironmentVariableA
                ((LPCSTR)name_copy,
                 (LPCSTR)(-(uint)!is_delete & (uint)(name_copy + ((int)equal - (int)option) + 1)));
      stock_free(name_copy);
    }
  }
  return 0;
}



