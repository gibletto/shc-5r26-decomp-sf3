#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x1ca48))


// entry: 0043b430
// name : stock_getenv
// size : 150
// sig  : char * stock_getenv(char * name)


/* Library Function - Multiple Matches With Different Base Names
    __getenv_lk
    _getenv
   
   Library: Visual Studio 1998 Release */

char * __cdecl stock_getenv(char *name)

{
  int iVar1;
  uint name_len;
  uint uVar2;
  int *env_ptr;
  char *p;
  char ch;
  
  if (stock_environ == (int *)0x0) {
    if ((stock_wenviron != 0) && (iVar1 = stock_wtomb_environ(), iVar1 != 0)) {
      return (char *)0x0;
    }
    if (stock_environ == (int *)0x0) {
      return (char *)0x0;
    }
  }
  if (name != (char *)0x0) {
    name_len = 0xffffffff;
    p = name;
    do {
      if (name_len == 0) break;
      name_len = name_len - 1;
      ch = *p;
      p = p + 1;
    } while (ch != '\0');
    name_len = ~name_len - 1;
    iVar1 = *stock_environ;
    env_ptr = stock_environ;
    while (iVar1 != 0) {
      uVar2 = 0xffffffff;
      p = (char *)*env_ptr;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        ch = *p;
        p = p + 1;
      } while (ch != '\0');
      if (((name_len < ~uVar2 - 1) && (((uchar *)*env_ptr)[name_len] == '=')) &&
         (iVar1 = stock_mbsnbicoll((uchar *)*env_ptr,(uchar *)name,name_len), iVar1 == 0)) {
        return (char *)(*env_ptr + 1 + name_len);
      }
      env_ptr = env_ptr + 1;
      iVar1 = *env_ptr;
    }
  }
  return (char *)0x0;
}



