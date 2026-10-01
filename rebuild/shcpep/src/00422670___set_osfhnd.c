#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x6e40))


// entry: 00422670
// name : __set_osfhnd
// size : 163
// sig  : int __set_osfhnd(int fh, long value)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_osfhnd
   
   Library: Visual Studio 1998 Release */

int __cdecl __set_osfhnd(int fh,long value)

{
  int *piVar1;
  int iVar2;
  
  if ((uint)fh < stock_nhandle) {
    piVar1 = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7U) >> 3));
    iVar2 = (fh & 0x1fU) * 8;
    if (*(int *)(*piVar1 + iVar2) == -1) {
      if (stock_app_type == 1) {
        if (fh == 0) {
          SetStdHandle(0xfffffff6,(HANDLE)value);
        }
        else if (fh == 1) {
          SetStdHandle(0xfffffff5,(HANDLE)value);
        }
        else if (fh == 2) {
          SetStdHandle(0xfffffff4,(HANDLE)value);
        }
      }
      *(long *)(*piVar1 + iVar2) = value;
      return 0;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
}



