#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_umaskval
#define stock_umaskval (*(unsigned int *)(g_sd + 0x81b8))


// entry: 00438d10
// name : stock_sopen
// size : 981
// sig  : uint stock_sopen(char * path, uint oflag, int shflag, uint pmode)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stock_sopen(char *path,uint oflag,int shflag,uint pmode)

{
  unsigned char _frec_19[25];
#define peek_ch (*(char *)(_frec_19 + 0))
#define local_18 (*(DWORD *)(_frec_19 + 1))
#define local_14 (*(uint *)(_frec_19 + 5))
#define create_disp (*(DWORD *)(_frec_19 + 9))
#define sec_attr (*(_SECURITY_ATTRIBUTES *)(_frec_19 + 13))
  uint uVar1;
  HANDLE hFile;
  uint pos;
  int status;
  byte fileflags;
  DWORD DVar2;
  int *ioinfo_block;
  byte *osfile;
  
  sec_attr.lpSecurityDescriptor = (LPVOID)0x0;
  sec_attr.nLength = 0xc;
  sec_attr.bInheritHandle = (BOOL)((oflag & 0x80) == 0);
  if ((oflag & 0x8000) == 0) {
    fileflags = 0x80;
    if ((oflag & 0x4000) == 0) {
      fileflags = (stock_fmode == 0x8000) - 1U & 0x80;
    }
  }
  else {
    fileflags = 0;
  }
  uVar1 = oflag & 3;
  if (uVar1 == 0) {
    local_14 = 0x80000000;
  }
  else if (uVar1 == 1) {
    local_14 = 0x40000000;
  }
  else {
    if (uVar1 != 2) {
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
  uVar1 = oflag & 0x700;
  if (uVar1 < 0x101) {
    if (uVar1 == 0x100) {
      create_disp = 4;
      goto LAB_00438eb1;
    }
    if (uVar1 != 0) {
      _stock_errno = 0x16;
      stock_doserrno = 0;
      return 0xffffffff;
    }
LAB_00438e81:
    create_disp = 3;
    goto LAB_00438eb1;
  }
  if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      create_disp = 2;
      goto LAB_00438eb1;
    }
    if (uVar1 != 0x200) {
      _stock_errno = 0x16;
      stock_doserrno = 0;
      return 0xffffffff;
    }
LAB_00438e95:
    create_disp = 5;
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
          _stock_errno = 0x16;
          stock_doserrno = 0;
          return 0xffffffff;
        }
        goto LAB_00438e81;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_00438e95;
      if (uVar1 != 0x700) {
        _stock_errno = 0x16;
        stock_doserrno = 0;
        return 0xffffffff;
      }
    }
    create_disp = 1;
  }
LAB_00438eb1:
  DVar2 = 0x80;
  if (((oflag & 0x100) != 0) && ((~stock_umaskval & pmode & 0x80) == 0)) {
    DVar2 = 1;
  }
  if ((oflag & 0x40) != 0) {
    local_14 = local_14 | 0x10000;
    DVar2 = DVar2 | 0x4000000;
  }
  if ((oflag & 0x1000) != 0) {
    DVar2 = DVar2 | 0x100;
  }
  if ((oflag & 0x20) == 0) {
    if ((oflag & 0x10) != 0) {
      DVar2 = DVar2 | 0x10000000;
    }
  }
  else {
    DVar2 = DVar2 | 0x8000000;
  }
  uVar1 = stock_alloc_osfhnd();
  if (uVar1 == 0xffffffff) {
    _stock_errno = 0x18;
    stock_doserrno = 0;
    return 0xffffffff;
  }
  hFile = CreateFileA(path,local_14,local_18,&sec_attr,create_disp,DVar2,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    DVar2 = GetLastError();
    stock_dosmaperr(DVar2);
    return 0xffffffff;
  }
  DVar2 = GetFileType(hFile);
  if (DVar2 != 0) {
    if (DVar2 == 2) {
      fileflags = fileflags | 0x40;
    }
    else if (DVar2 == 3) {
      fileflags = fileflags | 8;
    }
    __set_osfhnd(uVar1,(intptr_t)hFile);
    ioinfo_block = (int *)((int)&stock_pioinfo + ((int)(uVar1 & 0xffffffe7) >> 3));
    local_14 = (uVar1 & 0x1f) * 8;
    *(byte *)(*ioinfo_block + 4 + local_14) = fileflags | 1;
    local_18 = CONCAT31((*(unsigned int *)((char *)&local_18 + 1) & 0xffffff),fileflags) & 0xffffff48;
    if ((((fileflags & 0x48) == 0) && ((fileflags & 0x80) != 0)) && ((oflag & 2) != 0)) {
      pos = stock_lseek(uVar1,-1,2);
      if (pos == 0xffffffff) {
        if (stock_doserrno != 0x83) {
          __close(uVar1);
          return 0xffffffff;
        }
      }
      else {
        peek_ch = '\0';
        status = stock_read(uVar1,&peek_ch,1);
        if (((status == 0) && (peek_ch == '\x1a')) && (status = __chsize(uVar1,pos), status == -1))
        {
          __close(uVar1);
          return 0xffffffff;
        }
        pos = stock_lseek(uVar1,0,0);
        if (pos == 0xffffffff) {
          __close(uVar1);
          return 0xffffffff;
        }
      }
    }
    if (((char)local_18 == '\0') && ((oflag & 8) != 0)) {
      osfile = (byte *)(*ioinfo_block + 4 + local_14);
      *osfile = *osfile | 0x20;
    }
    return uVar1;
  }
  CloseHandle(hFile);
  DVar2 = GetLastError();
  stock_dosmaperr(DVar2);
  return 0xffffffff;
#undef peek_ch
#undef local_18
#undef local_14
#undef create_disp
#undef sec_attr
}



