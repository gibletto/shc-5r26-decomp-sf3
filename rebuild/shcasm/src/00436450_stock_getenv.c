#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_environ
#define stock_environ (*(int * *)(g_sd + 0x81d8))


// entry: 00436450
// name : stock_getenv
// size : 150
// sig  : char * stock_getenv(char * _VarName)


/* Library Function - Multiple Matches With Different Base Names
    __getenv_lk
    _getenv
   
   Library: Visual Studio 1998 Release */

char * __cdecl stock_getenv(char *_VarName)

{
  int iVar1;
  uint name_len;
  uint uVar2;
  int *search;
  char *scan;
  char ch;
  
  if (stock_environ == (int *)0x0) {
    if ((stock_wenviron != 0) && (iVar1 = ___wtomb_environ(), iVar1 != 0)) {
      return (char *)0x0;
    }
    if (stock_environ == (int *)0x0) {
      return (char *)0x0;
    }
  }
  if (_VarName != (char *)0x0) {
    name_len = 0xffffffff;
    scan = _VarName;
    do {
      if (name_len == 0) break;
      name_len = name_len - 1;
      ch = *scan;
      scan = scan + 1;
    } while (ch != '\0');
    name_len = ~name_len - 1;
    iVar1 = *stock_environ;
    search = stock_environ;
    while (iVar1 != 0) {
      uVar2 = 0xffffffff;
      scan = (char *)*search;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        ch = *scan;
        scan = scan + 1;
      } while (ch != '\0');
      if (((name_len < ~uVar2 - 1) && (((uchar *)*search)[name_len] == '=')) &&
         (iVar1 = __mbsnbicoll((uchar *)*search,(uchar *)_VarName,name_len), iVar1 == 0)) {
        return (char *)(*search + 1 + name_len);
      }
      search = search + 1;
      iVar1 = *search;
    }
  }
  return (char *)0x0;
}



