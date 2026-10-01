#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_doserrno
#define stock_doserrno (*(unsigned int *)(g_sd + 0x4464))
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x6e40))


// entry: 004215d0
// name : stock_write
// size : 555
// sig  : int stock_write(uint fh, char * buf, uint cnt)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_write(uint fh,char *buf,uint cnt)

{
  unsigned char _frec_418[1048];
#define local_418 (*(uint *)(_frec_418 + 0))
#define local_414 (*(DWORD *)(_frec_418 + 4))
#define local_410 (*(int * *)(_frec_418 + 8))
#define local_40c (*(int *)(_frec_418 + 12))
#define local_408 (*(DWORD *)(_frec_418 + 16))
#define local_404 (*(char (*)[1028])(_frec_418 + 20))
  byte bVar1;
  char cVar2;
  BOOL BVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  
  if (fh < stock_nhandle) {
    local_410 = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3));
    local_40c = (fh & 0x1f) * 8;
    bVar1 = *(byte *)(*local_410 + 4 + local_40c);
    if ((bVar1 & 1) != 0) {
      iVar5 = 0;
      local_408 = 0;
      if (cnt == 0) {
        return 0;
      }
      if ((bVar1 & 0x20) != 0) {
        stock_lseek(fh,0,2);
      }
      if ((*(byte *)((undefined4 *)(local_40c + *local_410) + 1) & 0x80) == 0) {
        BVar3 = WriteFile(*(HANDLE *)(local_40c + *local_410),buf,cnt,&local_414,(LPOVERLAPPED)0x0);
        if (BVar3 == 0) {
LAB_00421715:
          local_418 = GetLastError();
        }
        else {
          local_418 = 0;
          local_408 = local_414;
        }
      }
      else {
        local_418 = 0;
        pcVar6 = buf;
        do {
          if (cnt <= (uint)((int)pcVar6 - (int)buf)) break;
          pcVar4 = local_404;
          do {
            if (cnt <= (uint)((int)pcVar6 - (int)buf)) break;
            cVar2 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            if (cVar2 == '\n') {
              *pcVar4 = '\r';
              iVar5 = iVar5 + 1;
              pcVar4 = pcVar4 + 1;
            }
            *pcVar4 = cVar2;
            pcVar4 = pcVar4 + 1;
          } while ((int)pcVar4 - (int)local_404 < 0x400);
          BVar3 = WriteFile(*(HANDLE *)(*local_410 + local_40c),local_404,
                            (int)pcVar4 - (int)local_404,&local_414,(LPOVERLAPPED)0x0);
          if (BVar3 == 0) goto LAB_00421715;
          local_408 = local_408 + local_414;
        } while ((int)pcVar4 - (int)local_404 <= (int)local_414);
      }
      if (local_408 != 0) {
        return local_408 - iVar5;
      }
      if (local_418 == 0) {
        if (((*(byte *)(*local_410 + 4 + local_40c) & 0x40) != 0) && (*buf == '\x1a')) {
          return 0;
        }
        _stock_errno = 0x1c;
        stock_doserrno = 0;
        return -1;
      }
      if (local_418 != 5) {
        stock_dosmaperr(local_418);
        return -1;
      }
      _stock_errno = 9;
      stock_doserrno = local_418;
      return -1;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
#undef local_418
#undef local_414
#undef local_410
#undef local_40c
#undef local_408
#undef local_404
}



