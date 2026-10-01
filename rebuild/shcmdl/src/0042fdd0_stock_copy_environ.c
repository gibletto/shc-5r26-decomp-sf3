#include "decls.h"
#include "imports.h"

// entry: 0042fdd0
// name : stock_copy_environ
// size : 116
// sig  : char * * stock_copy_environ(char * * env)


/* Library Function - Single Match
    _copy_environ
   
   Library: Visual Studio 1998 Release */

char ** __cdecl stock_copy_environ(char **env)

{
  char **ppcVar1;
  char **ppcVar2;
  char *pcVar3;
  int iVar4;
  
  iVar4 = 0;
  if (env != (char **)0x0) {
    pcVar3 = *env;
    ppcVar2 = env;
    while (pcVar3 != (char *)0x0) {
      ppcVar2 = ppcVar2 + 1;
      iVar4 = iVar4 + 1;
      pcVar3 = *ppcVar2;
    }
    ppcVar2 = stock_malloc(iVar4 * 4 + 4);
    if (ppcVar2 == (char **)0x0) {
      stock_amsg_exit(9);
    }
    pcVar3 = *env;
    ppcVar1 = ppcVar2;
    while (pcVar3 != (char *)0x0) {
      pcVar3 = *env;
      env = env + 1;
      pcVar3 = stock_strdup(pcVar3);
      *ppcVar1 = pcVar3;
      ppcVar1 = ppcVar1 + 1;
      pcVar3 = *env;
    }
    *ppcVar1 = (char *)0x0;
    return ppcVar2;
  }
  return (char **)0x0;
}



