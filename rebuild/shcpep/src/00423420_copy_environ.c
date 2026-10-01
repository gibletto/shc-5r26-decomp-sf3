#include "decls.h"
#include "imports.h"

// entry: 00423420
// name : copy_environ
// size : 116
// sig  : undefined4 * copy_environ(int * oldenviron)


/* Library Function - Single Match
    _copy_environ
   
   Library: Visual Studio 1998 Release */

undefined4 * __cdecl copy_environ(int *oldenviron)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  
  iVar5 = 0;
  if (oldenviron != (int *)0x0) {
    iVar1 = *oldenviron;
    piVar6 = oldenviron;
    while (iVar1 != 0) {
      piVar6 = piVar6 + 1;
      iVar5 = iVar5 + 1;
      iVar1 = *piVar6;
    }
    puVar3 = stock_malloc(iVar5 * 4 + 4);
    if (puVar3 == (undefined4 *)0x0) {
      __amsg_exit(9);
    }
    iVar5 = *oldenviron;
    puVar2 = puVar3;
    while (iVar5 != 0) {
      pcVar4 = (char *)*oldenviron;
      oldenviron = oldenviron + 1;
      pcVar4 = __strdup(pcVar4);
      *puVar2 = pcVar4;
      puVar2 = puVar2 + 1;
      iVar5 = *oldenviron;
    }
    *puVar2 = 0;
    return puVar3;
  }
  return (undefined4 *)0x0;
}



