#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x1ca48))


// entry: 0043f830
// name : stock_findenv
// size : 92
// sig  : int stock_findenv(uchar * name, uint len)


/* Library Function - Single Match
    _findenv
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_findenv(uchar *name,uint len)

{
  int iVar1;
  int *entry_ptr;
  
  iVar1 = *stock_environ;
  entry_ptr = stock_environ;
  while( true ) {
    if (iVar1 == 0) {
      return -((int)entry_ptr - (int)stock_environ >> 2);
    }
    iVar1 = stock_mbsnbicoll(name,(uchar *)*entry_ptr,len);
    if ((iVar1 == 0) &&
       ((*(char *)(*entry_ptr + len) == '=' || (*(char *)(*entry_ptr + len) == '\0')))) break;
    entry_ptr = entry_ptr + 1;
    iVar1 = *entry_ptr;
  }
  return (int)entry_ptr - (int)stock_environ >> 2;
}



