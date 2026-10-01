#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x4088))


// entry: 0042fd70
// name : stock_findenv
// size : 92
// sig  : int stock_findenv(uchar * name, uint len)


/* Library Function - Single Match
    _findenv
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_findenv(uchar *name,uint len)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *stock_environ;
  piVar2 = stock_environ;
  while( true ) {
    if (iVar1 == 0) {
      return -((int)piVar2 - (int)stock_environ >> 2);
    }
    iVar1 = stock_mbsnbicoll(name,(uchar *)*piVar2,len);
    if ((iVar1 == 0) && ((*(char *)(*piVar2 + len) == '=' || (*(char *)(*piVar2 + len) == '\0'))))
    break;
    piVar2 = piVar2 + 1;
    iVar1 = *piVar2;
  }
  return (int)piVar2 - (int)stock_environ >> 2;
}



