#include "decls.h"
#include "imports.h"

// entry: 0043a5e0
// name : copy_environ
// size : 116
// sig  : undefined4 * copy_environ(int * param_1)


/* Library Function - Single Match
    _copy_environ
   
   Library: Visual Studio 1998 Release */

undefined4 * __cdecl copy_environ(int *param_1)

{
  undefined4 *newenv;
  char *str;
  int iVar1;
  int *scan;
  undefined4 *dst;
  int env_entry;
  
  iVar1 = 0;
  if (param_1 != (int *)0x0) {
    env_entry = *param_1;
    scan = param_1;
    while (env_entry != 0) {
      scan = scan + 1;
      iVar1 = iVar1 + 1;
      env_entry = *scan;
    }
    newenv = stock_malloc(iVar1 * 4 + 4);
    if (newenv == (undefined4 *)0x0) {
      __amsg_exit(9);
    }
    iVar1 = *param_1;
    dst = newenv;
    while (iVar1 != 0) {
      str = (char *)*param_1;
      param_1 = param_1 + 1;
      str = __strdup(str);
      *dst = str;
      dst = dst + 1;
      iVar1 = *param_1;
    }
    *dst = 0;
    return newenv;
  }
  return (undefined4 *)0x0;
}



