#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x6e40))


// entry: 00421210
// name : stock_read
// size : 611
// sig  : int stock_read(uint fh, char * buf, uint cnt)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_read(uint fh,char *buf,uint cnt)

{
  unsigned char _frec_d[13];
#define local_d (*(char *)(_frec_d + 0))
#define local_c (*(DWORD *)(_frec_d + 1))
#define local_8 (*(DWORD *)(_frec_d + 5))
#define local_4 (*(char * *)(_frec_d + 9))
  int *piVar1;
  int iVar2;
  byte *pbVar3;
  char cVar4;
  int iVar5;
  BOOL BVar6;
  DWORD oserrno;
  byte bVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  
  if (fh < stock_nhandle) {
    piVar1 = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3));
    iVar2 = (fh & 0x1f) * 8;
    iVar5 = *piVar1 + iVar2;
    if ((*(byte *)(iVar5 + 4) & 1) != 0) {
      local_c = 0;
      if ((cnt == 0) || ((*(byte *)(iVar5 + 4) & 2) != 0)) {
        return 0;
      }
      pcVar8 = buf;
      if (((*(byte *)(iVar5 + 4) & 0x48) != 0) && (*(char *)(iVar5 + 5) != '\n')) {
        *buf = *(char *)(iVar5 + 5);
        pcVar8 = buf + 1;
        cnt = cnt - 1;
        local_c = 1;
        *(undefined1 *)(*piVar1 + 5 + iVar2) = 10;
      }
      BVar6 = ReadFile(*(HANDLE *)(*piVar1 + iVar2),pcVar8,cnt,&local_8,(LPOVERLAPPED)0x0);
      if (BVar6 == 0) {
        oserrno = GetLastError();
        if (oserrno == 5) {
          stock_doserrno = oserrno;
          _stock_errno = 9;
          return -1;
        }
        if (oserrno != 0x6d) {
          stock_dosmaperr(oserrno);
          return -1;
        }
        return 0;
      }
      local_c = local_c + local_8;
      pbVar3 = (byte *)(*piVar1 + 4 + iVar2);
      bVar7 = *pbVar3;
      if ((bVar7 & 0x80) != 0) {
        if ((local_8 == 0) || (*buf != '\n')) {
          bVar7 = bVar7 & 0xfb;
        }
        else {
          bVar7 = bVar7 | 4;
        }
        *pbVar3 = bVar7;
        local_4 = buf + local_c;
        pcVar8 = buf;
        pcVar10 = buf;
        if (buf < local_4) {
          do {
            cVar4 = *pcVar8;
            if (cVar4 == '\x1a') {
              pbVar3 = (byte *)(*piVar1 + 4 + iVar2);
              bVar7 = *pbVar3;
              if ((bVar7 & 0x40) == 0) {
                *pbVar3 = bVar7 | 2;
              }
              break;
            }
            if (cVar4 == '\r') {
              if (pcVar8 < local_4 + -1) {
                pcVar9 = pcVar8 + 1;
                if (*pcVar9 == '\n') {
                  pcVar9 = pcVar8 + 2;
                  *pcVar10 = '\n';
                }
                else {
                  *pcVar10 = '\r';
                }
                goto LAB_00421414;
              }
              pcVar9 = pcVar8 + 1;
              local_c = 0;
              BVar6 = ReadFile(*(HANDLE *)(*piVar1 + iVar2),&local_d,1,&local_8,(LPOVERLAPPED)0x0);
              if (BVar6 == 0) {
                local_c = GetLastError();
              }
              if ((local_c != 0) || (local_8 == 0)) {
LAB_00421411:
                *pcVar10 = '\r';
                goto LAB_00421414;
              }
              if ((*(byte *)(*piVar1 + 4 + iVar2) & 0x48) == 0) {
                if ((pcVar10 == buf) && (local_d == '\n')) {
                  *pcVar10 = '\n';
                  goto LAB_00421414;
                }
                stock_lseek(fh,-1,1);
                if (local_d != '\n') goto LAB_00421411;
              }
              else {
                if (local_d == '\n') {
                  *pcVar10 = '\n';
                  goto LAB_00421414;
                }
                *pcVar10 = '\r';
                pcVar10 = pcVar10 + 1;
                *(char *)(*piVar1 + 5 + iVar2) = local_d;
              }
            }
            else {
              pcVar9 = pcVar8 + 1;
              *pcVar10 = cVar4;
LAB_00421414:
              pcVar10 = pcVar10 + 1;
            }
            pcVar8 = pcVar9;
          } while (pcVar9 < local_4);
        }
        local_c = (int)pcVar10 - (int)buf;
      }
      return local_c;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
#undef local_d
#undef local_c
#undef local_8
#undef local_4
}



