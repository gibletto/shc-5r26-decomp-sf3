#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_pioinfo
#define stock_pioinfo (*(int * *)(g_sd + 0x15bb0))


// entry: 004380f0
// name : stock_ioinit
// size : 467
// sig  : void stock_ioinit(void)


int __cdecl stock_ioinit(void)

{
  unsigned char _frec_44[68];
#define startup_info (*(_STARTUPINFOA *)(_frec_44 + 0))
  undefined4 *ioinfo;
  DWORD DVar1;
  HANDLE hFile;
  UINT *osfile_p;
  int *piVar2;
  uint fh;
  undefined4 *next_ioinfo;
  byte *handle_p;
  int std_fh;
  UINT inherit_count;
  UINT handle_count;
  
  ioinfo = stock_malloc(0x100);
  if (ioinfo == (undefined4 *)0x0) {
    __amsg_exit(0x1b);
  }
  stock_nhandle = 0x20;
  stock_pioinfo = ioinfo;
  if (ioinfo < ioinfo + 0x40) {
    do {
      *(undefined1 *)(ioinfo + 1) = 0;
      next_ioinfo = ioinfo + 2;
      *ioinfo = 0xffffffff;
      *(undefined1 *)((int)ioinfo + 5) = 10;
      ioinfo = next_ioinfo;
    } while (next_ioinfo < stock_pioinfo + 0x40);
  }
  GetStartupInfoA(&startup_info);
  if ((startup_info.cbReserved2 != 0) && ((UINT *)startup_info.lpReserved2 != (UINT *)0x0)) {
    inherit_count = *(UINT *)startup_info.lpReserved2;
    osfile_p = (UINT *)((int)startup_info.lpReserved2 + 4);
    handle_p = (byte *)(inherit_count + (int)osfile_p);
    if (0x7ff < (int)inherit_count) {
      inherit_count = 0x800;
    }
    handle_count = inherit_count;
    if ((int)stock_nhandle < (int)inherit_count) {
      piVar2 = &DAT_00450bb4;
      do {
        ioinfo = stock_malloc(0x100);
        handle_count = stock_nhandle;
        if (ioinfo == (undefined4 *)0x0) break;
        *piVar2 = (int)ioinfo;
        stock_nhandle = stock_nhandle + 0x20;
        if (ioinfo < ioinfo + 0x40) {
          do {
            *(undefined1 *)(ioinfo + 1) = 0;
            next_ioinfo = ioinfo + 2;
            *ioinfo = 0xffffffff;
            *(undefined1 *)((int)ioinfo + 5) = 10;
            ioinfo = next_ioinfo;
          } while (next_ioinfo < (undefined4 *)(*piVar2 + 0x100));
        }
        piVar2 = piVar2 + 1;
        handle_count = inherit_count;
      } while ((int)stock_nhandle < (int)inherit_count);
    }
    fh = 0;
    if (0 < (int)handle_count) {
      do {
        if (((*(HANDLE *)handle_p != (HANDLE)0xffffffff) && ((*osfile_p & 1) != 0)) &&
           (DVar1 = GetFileType(*(HANDLE *)handle_p), DVar1 != 0)) {
          ioinfo = (undefined4 *)
                   (*(int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3)) + (fh & 0x1f) * 8)
          ;
          *ioinfo = *(undefined4 *)handle_p;
          *(byte *)(ioinfo + 1) = (byte)*osfile_p;
        }
        fh = fh + 1;
        osfile_p = (UINT *)((int)osfile_p + 1);
        handle_p = handle_p + 4;
      } while ((int)fh < (int)handle_count);
    }
  }
  std_fh = 0;
  do {
    piVar2 = stock_pioinfo + std_fh * 2;
    if (*piVar2 == -1) {
      DVar1 = 0xfffffff6;
      *(undefined1 *)(piVar2 + 1) = 0x81;
      if (std_fh != 0) {
        DVar1 = (std_fh == 1) - 0xc;
      }
      hFile = GetStdHandle(DVar1);
      if ((hFile == (HANDLE)0xffffffff) || (DVar1 = GetFileType(hFile), DVar1 == 0)) {
        *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x40;
      }
      else {
        *piVar2 = (int)hFile;
        if ((DVar1 & 0xff) == 2) {
          *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x40;
        }
        else if ((DVar1 & 0xff) == 3) {
          *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 8;
        }
      }
    }
    else {
      *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x80;
    }
    std_fh = std_fh + 1;
  } while (std_fh < 3);
  SetHandleCount(stock_nhandle);
  return;
#undef startup_info
}
