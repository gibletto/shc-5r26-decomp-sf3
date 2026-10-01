#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_wenviron
#define stock_wenviron (*(int * *)(g_sd + 0x1ca50))


// entry: 0043e7d0
// name : stock_wtomb_environ
// size : 138
// sig  : int stock_wtomb_environ(void)


/* Library Function - Single Match
    ___wtomb_environ
   
   Library: Visual Studio 1998 Release */

int __cdecl stock_wtomb_environ(void)

{
  uint size;
  uchar *env_string;
  int iVar1;
  int *wenv_ptr;
  
  iVar1 = *stock_wenviron;
  wenv_ptr = stock_wenviron;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    size = WideCharToMultiByte(1,0,(LPCWSTR)*wenv_ptr,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (size == 0) {
      return -1;
    }
    env_string = stock_malloc(size);
    if (env_string == (uchar *)0x0) {
      return -1;
    }
    iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*wenv_ptr,-1,(LPSTR)env_string,size,(LPCSTR)0x0,
                                (LPBOOL)0x0);
    if (iVar1 == 0) break;
    wenv_ptr = wenv_ptr + 1;
    stock_crtsetenv(env_string,0);
    iVar1 = *wenv_ptr;
  }
  return -1;
}



