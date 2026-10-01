#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x4088))


// entry: 0042ad60
// name : stock_getenv
// size : 150
// sig  : char * stock_getenv(char * name)


/* Library Function - Multiple Matches With Different Base Names
    __getenv_lk
    _getenv
   
   Library: Visual Studio 1998 Release */

char * __cdecl stock_getenv(char *name)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  
  if (stock_environ == (int *)0x0) {
    if ((stock_wenviron != 0) && (iVar2 = stock_wtomb_environ(), iVar2 != 0)) {
      return (char *)0x0;
    }
    if (stock_environ == (int *)0x0) {
      return (char *)0x0;
    }
  }
  if (name != (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar6 = name;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3 - 1;
    iVar2 = *stock_environ;
    piVar5 = stock_environ;
    while (iVar2 != 0) {
      uVar4 = 0xffffffff;
      pcVar6 = (char *)*piVar5;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      if (((uVar3 < ~uVar4 - 1) && (((uchar *)*piVar5)[uVar3] == '=')) &&
         (iVar2 = stock_mbsnbicoll((uchar *)*piVar5,(uchar *)name,uVar3), iVar2 == 0)) {
        return (char *)(*piVar5 + 1 + uVar3);
      }
      piVar5 = piVar5 + 1;
      iVar2 = *piVar5;
    }
  }
  return (char *)0x0;
}



