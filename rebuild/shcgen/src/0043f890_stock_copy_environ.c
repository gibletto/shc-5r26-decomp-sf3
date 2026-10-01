#include "decls.h"
#include "imports.h"

// entry: 0043f890
// name : stock_copy_environ
// size : 116
// sig  : char * * stock_copy_environ(char * * env)


/* Library Function - Single Match
    _copy_environ
   
   Library: Visual Studio 1998 Release */

char ** __cdecl stock_copy_environ(char **env)

{
  char **ppcVar1;
  char *pcVar2;
  int count;
  char **dst;
  
  count = 0;
  if (env != (char **)0x0) {
    pcVar2 = *env;
    ppcVar1 = env;
    while (pcVar2 != (char *)0x0) {
      ppcVar1 = ppcVar1 + 1;
      count = count + 1;
      pcVar2 = *ppcVar1;
    }
    ppcVar1 = stock_malloc(count * 4 + 4);
    if (ppcVar1 == (char **)0x0) {
      stock_amsg_exit(9);
    }
    pcVar2 = *env;
    dst = ppcVar1;
    while (pcVar2 != (char *)0x0) {
      pcVar2 = *env;
      env = env + 1;
      pcVar2 = stock_strdup(pcVar2);
      *dst = pcVar2;
      dst = dst + 1;
      pcVar2 = *env;
    }
    *dst = (char *)0x0;
    return ppcVar1;
  }
  return (char **)0x0;
}



