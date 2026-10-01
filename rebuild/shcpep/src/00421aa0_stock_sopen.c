#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_umaskval
#define stock_umaskval (*(unsigned int *)(g_sd + 0x4468))


// entry: 00421aa0
// name : stock_sopen
// size : 981
// sig  : uint stock_sopen(char * path, uint oflag, int shflag, uint pmode)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stock_sopen(char *path,uint oflag,int shflag,uint pmode)

{
  unsigned char _frec_19[25];
#define local_19 (*(char *)(_frec_19 + 0))
#define local_18 (*(DWORD *)(_frec_19 + 1))
#define local_14 (*(uint *)(_frec_19 + 5))
#define local_10 (*(DWORD *)(_frec_19 + 9))
#define local_c (*(_SECURITY_ATTRIBUTES *)(_frec_19 + 13))
  int *piVar1;
  byte *pbVar2;
  uint uVar3;
  HANDLE hFile;
  uint uVar4;
  int iVar5;
  byte bVar6;
  DWORD DVar7;
  
  local_c.lpSecurityDescriptor = (LPVOID)0x0;
  local_c.nLength = 0xc;
  local_c.bInheritHandle = (BOOL)((oflag & 0x80) == 0);
  if ((oflag & 0x8000) == 0) {
    bVar6 = 0x80;
    if ((oflag & 0x4000) == 0) {
      bVar6 = (stock_fmode == 0x8000) - 1U & 0x80;
    }
  }
  else {
    bVar6 = 0;
  }
  uVar3 = oflag & 3;
  if (uVar3 == 0) {
    local_14 = 0x80000000;
  }
  else if (uVar3 == 1) {
    local_14 = 0x40000000;
  }
  else {
    if (uVar3 != 2) {
      _stock_errno = 0x16;
      stock_doserrno = 0;
      return 0xffffffff;
    }
    local_14 = 0xc0000000;
  }
  switch(shflag) {
  case 0x10:
    local_18 = 0;
    break;
  default:
    _stock_errno = 0x16;
    stock_doserrno = 0;
    return 0xffffffff;
  case 0x20:
    local_18 = 1;
    break;
  case 0x30:
    local_18 = 2;
    break;
  case 0x40:
    local_18 = 3;
  }
  uVar3 = oflag & 0x700;
  if (uVar3 < 0x101) {
    if (uVar3 == 0x100) {
      local_10 = 4;
      goto LAB_00421c41;
    }
    if (uVar3 != 0) {
      _stock_errno = 0x16;
      stock_doserrno = 0;
      return 0xffffffff;
    }
LAB_00421c11:
    local_10 = 3;
    goto LAB_00421c41;
  }
  if (uVar3 < 0x301) {
    if (uVar3 == 0x300) {
      local_10 = 2;
      goto LAB_00421c41;
    }
    if (uVar3 != 0x200) {
      _stock_errno = 0x16;
      stock_doserrno = 0;
      return 0xffffffff;
    }
LAB_00421c25:
    local_10 = 5;
  }
  else {
    if (uVar3 < 0x501) {
      if (uVar3 != 0x500) {
        if (uVar3 != 0x400) {
          _stock_errno = 0x16;
          stock_doserrno = 0;
          return 0xffffffff;
        }
        goto LAB_00421c11;
      }
    }
    else {
      if (uVar3 == 0x600) goto LAB_00421c25;
      if (uVar3 != 0x700) {
        _stock_errno = 0x16;
        stock_doserrno = 0;
        return 0xffffffff;
      }
    }
    local_10 = 1;
  }
LAB_00421c41:
  DVar7 = 0x80;
  if (((oflag & 0x100) != 0) && ((~stock_umaskval & pmode & 0x80) == 0)) {
    DVar7 = 1;
  }
  if ((oflag & 0x40) != 0) {
    local_14 = local_14 | 0x10000;
    DVar7 = DVar7 | 0x4000000;
  }
  if ((oflag & 0x1000) != 0) {
    DVar7 = DVar7 | 0x100;
  }
  if ((oflag & 0x20) == 0) {
    if ((oflag & 0x10) != 0) {
      DVar7 = DVar7 | 0x10000000;
    }
  }
  else {
    DVar7 = DVar7 | 0x8000000;
  }
  uVar3 = stock_alloc_osfhnd();
  if (uVar3 == 0xffffffff) {
    _stock_errno = 0x18;
    stock_doserrno = 0;
    return 0xffffffff;
  }
  hFile = CreateFileA(path,local_14,local_18,&local_c,local_10,DVar7,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    DVar7 = GetLastError();
    stock_dosmaperr(DVar7);
    return 0xffffffff;
  }
  DVar7 = GetFileType(hFile);
  if (DVar7 != 0) {
    if (DVar7 == 2) {
      bVar6 = bVar6 | 0x40;
    }
    else if (DVar7 == 3) {
      bVar6 = bVar6 | 8;
    }
    __set_osfhnd(uVar3,(long)hFile);
    piVar1 = (int *)((int)&stock_pioinfo + ((int)(uVar3 & 0xffffffe7) >> 3));
    local_14 = (uVar3 & 0x1f) * 8;
    *(byte *)(*piVar1 + 4 + local_14) = bVar6 | 1;
    local_18 = CONCAT31((*(unsigned int *)((char *)&local_18 + 1) & 0xffffff),bVar6) & 0xffffff48;
    if ((((bVar6 & 0x48) == 0) && ((bVar6 & 0x80) != 0)) && ((oflag & 2) != 0)) {
      uVar4 = stock_lseek(uVar3,-1,2);
      if (uVar4 == 0xffffffff) {
        if (stock_doserrno != 0x83) {
          __close(uVar3);
          return 0xffffffff;
        }
      }
      else {
        local_19 = '\0';
        iVar5 = stock_read(uVar3,&local_19,1);
        if (((iVar5 == 0) && (local_19 == '\x1a')) && (iVar5 = __chsize(uVar3,uVar4), iVar5 == -1))
        {
          __close(uVar3);
          return 0xffffffff;
        }
        uVar4 = stock_lseek(uVar3,0,0);
        if (uVar4 == 0xffffffff) {
          __close(uVar3);
          return 0xffffffff;
        }
      }
    }
    if (((char)local_18 == '\0') && ((oflag & 8) != 0)) {
      pbVar2 = (byte *)(*piVar1 + 4 + local_14);
      *pbVar2 = *pbVar2 | 0x20;
    }
    return uVar3;
  }
  CloseHandle(hFile);
  DVar7 = GetLastError();
  stock_dosmaperr(DVar7);
  return 0xffffffff;
#undef local_19
#undef local_18
#undef local_14
#undef local_10
#undef local_c
}



