#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_aenvptr
#define stock_aenvptr (*(char * *)(g_sd + 0x81f8))
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x81d8))


// entry: 00437bf0
// name : stock_setenvp
// size : 219
// sig  : void stock_setenvp(void)


int __cdecl stock_setenvp(void)

{
  undefined4 *env_slot;
  void *copy;
  uint uVar1;
  uint len;
  uint n;
  char *env_str;
  int numstrings;
  char *src;
  char *pcVar2;
  char ch;
  
  numstrings = 0;
  ch = *stock_aenvptr;
  env_str = stock_aenvptr;
  while (ch != '\0') {
    if (*env_str != '=') {
      numstrings = numstrings + 1;
    }
    uVar1 = 0xffffffff;
    pcVar2 = env_str;
    do {
      if (uVar1 == 0) break;
      uVar1 = uVar1 - 1;
      ch = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (ch != '\0');
    env_str = env_str + ~uVar1;
    ch = *env_str;
  }
  env_slot = stock_malloc(numstrings * 4 + 4);
  stock_environ = env_slot;
  if (env_slot == (undefined4 *)0x0) {
    __amsg_exit(9);
  }
  ch = *stock_aenvptr;
  env_str = stock_aenvptr;
  do {
    if (ch == '\0') {
      stock_free(stock_aenvptr);
      *env_slot = 0;
      return;
    }
    uVar1 = 0xffffffff;
    pcVar2 = env_str;
    do {
      if (uVar1 == 0) break;
      uVar1 = uVar1 - 1;
      ch = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (ch != '\0');
    if (*env_str != '=') {
      copy = stock_malloc(~uVar1);
      *env_slot = copy;
      if (copy == (void *)0x0) {
        __amsg_exit(9);
      }
      len = 0xffffffff;
      pcVar2 = env_str;
      do {
        src = pcVar2;
        if (len == 0) break;
        len = len - 1;
        src = pcVar2 + 1;
        ch = *pcVar2;
        pcVar2 = src;
      } while (ch != '\0');
      len = ~len;
      pcVar2 = (char *)*env_slot;
      env_slot = env_slot + 1;
      src = src + -len;
      for (n = len >> 2; n != 0; n = n - 1) {
        *(undefined4 *)pcVar2 = *(undefined4 *)src;
        src = src + 4;
        pcVar2 = pcVar2 + 4;
      }
      for (len = len & 3; len != 0; len = len - 1) {
        *pcVar2 = *src;
        src = src + 1;
        pcVar2 = pcVar2 + 1;
      }
    }
    env_str = env_str + ~uVar1;
    ch = *env_str;
  } while( true );
}
