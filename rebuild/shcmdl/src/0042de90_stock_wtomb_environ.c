#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_wenviron
#define stock_wenviron (*(int * *)(g_sd + 0x4090))


// entry: 0042de90
// name : stock_wtomb_environ
// size : 138
// sig  : int stock_wtomb_environ(void)


/* Library Function - Single Match
    ___wtomb_environ
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_wtomb_environ(void)

{
  uint size;
  uchar *option;
  int iVar1;
  int *piVar2;
  
  iVar1 = *stock_wenviron;
  piVar2 = stock_wenviron;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    size = WideCharToMultiByte(1,0,(LPCWSTR)*piVar2,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (size == 0) {
      return -1;
    }
    option = stock_malloc(size);
    if (option == (uchar *)0x0) {
      return -1;
    }
    iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*piVar2,-1,(LPSTR)option,size,(LPCSTR)0x0,(LPBOOL)0x0);
    if (iVar1 == 0) break;
    piVar2 = piVar2 + 1;
    stock_crtsetenv(option,0);
    iVar1 = *piVar2;
  }
  return -1;
}



