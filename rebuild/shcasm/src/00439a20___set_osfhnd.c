#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 00439a20
// name : __set_osfhnd
// size : 163
// sig  : int __set_osfhnd(int param_1, intptr_t param_2)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_osfhnd
   
   Library: Visual Studio 1998 Release */

int __cdecl __set_osfhnd(int param_1,intptr_t param_2)

{
  int *ioinfo_block;
  int ioinfo_ofs;
  
  if ((uint)param_1 < stock_nhandle) {
    ioinfo_block = (int *)((int)&stock_pioinfo + ((int)(param_1 & 0xffffffe7U) >> 3));
    ioinfo_ofs = (param_1 & 0x1fU) * 8;
    if (*(int *)(*ioinfo_block + ioinfo_ofs) == -1) {
      if (stock_app_type == 1) {
        if (param_1 == 0) {
          SetStdHandle(0xfffffff6,(HANDLE)param_2);
        }
        else if (param_1 == 1) {
          SetStdHandle(0xfffffff5,(HANDLE)param_2);
        }
        else if (param_1 == 2) {
          SetStdHandle(0xfffffff4,(HANDLE)param_2);
        }
      }
      *(intptr_t *)(*ioinfo_block + ioinfo_ofs) = param_2;
      return 0;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
}



