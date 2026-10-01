#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 004385e0
// name : stock_read
// size : 611
// sig  : int stock_read(uint fh, char * buf, uint cnt)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_read(uint fh,char *buf,uint cnt)

{
  unsigned char _frec_d[13];
#define peekchr (*(char *)(_frec_d + 0))
#define bytesread (*(DWORD *)(_frec_d + 1))
#define os_read (*(DWORD *)(_frec_d + 5))
#define buf_end (*(char * *)(_frec_d + 9))
  int pio;
  BOOL BVar1;
  DWORD oserrno;
  byte osfile_bits;
  char *src;
  char *next;
  char *dst;
  char ch;
  int *ioinfo_block;
  int ioinfo_ofs;
  byte *osfile;
  
  if (fh < stock_nhandle) {
    ioinfo_block = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3));
    ioinfo_ofs = (fh & 0x1f) * 8;
    pio = *ioinfo_block + ioinfo_ofs;
    if ((*(byte *)(pio + 4) & 1) != 0) {
      bytesread = 0;
      if ((cnt == 0) || ((*(byte *)(pio + 4) & 2) != 0)) {
        return 0;
      }
      src = buf;
      if (((*(byte *)(pio + 4) & 0x48) != 0) && (*(char *)(pio + 5) != '\n')) {
        *buf = *(char *)(pio + 5);
        src = buf + 1;
        cnt = cnt - 1;
        bytesread = 1;
        *(undefined1 *)(*ioinfo_block + 5 + ioinfo_ofs) = 10;
      }
      BVar1 = ReadFile(*(HANDLE *)(*ioinfo_block + ioinfo_ofs),src,cnt,&os_read,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
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
      bytesread = bytesread + os_read;
      osfile = (byte *)(*ioinfo_block + 4 + ioinfo_ofs);
      osfile_bits = *osfile;
      if ((osfile_bits & 0x80) != 0) {
        if ((os_read == 0) || (*buf != '\n')) {
          osfile_bits = osfile_bits & 0xfb;
        }
        else {
          osfile_bits = osfile_bits | 4;
        }
        *osfile = osfile_bits;
        buf_end = buf + bytesread;
        src = buf;
        dst = buf;
        if (buf < buf_end) {
          do {
            ch = *src;
            if (ch == '\x1a') {
              osfile = (byte *)(*ioinfo_block + 4 + ioinfo_ofs);
              osfile_bits = *osfile;
              if ((osfile_bits & 0x40) == 0) {
                *osfile = osfile_bits | 2;
              }
              break;
            }
            if (ch == '\r') {
              if (src < buf_end + -1) {
                next = src + 1;
                if (*next == '\n') {
                  next = src + 2;
                  *dst = '\n';
                }
                else {
                  *dst = '\r';
                }
                goto LAB_004387e4;
              }
              next = src + 1;
              bytesread = 0;
              BVar1 = ReadFile(*(HANDLE *)(*ioinfo_block + ioinfo_ofs),&peekchr,1,&os_read,
                               (LPOVERLAPPED)0x0);
              if (BVar1 == 0) {
                bytesread = GetLastError();
              }
              if ((bytesread != 0) || (os_read == 0)) {
LAB_004387e1:
                *dst = '\r';
                goto LAB_004387e4;
              }
              if ((*(byte *)(*ioinfo_block + 4 + ioinfo_ofs) & 0x48) == 0) {
                if ((dst == buf) && (peekchr == '\n')) {
                  *dst = '\n';
                  goto LAB_004387e4;
                }
                stock_lseek(fh,-1,1);
                if (peekchr != '\n') goto LAB_004387e1;
              }
              else {
                if (peekchr == '\n') {
                  *dst = '\n';
                  goto LAB_004387e4;
                }
                *dst = '\r';
                dst = dst + 1;
                *(char *)(*ioinfo_block + 5 + ioinfo_ofs) = peekchr;
              }
            }
            else {
              next = src + 1;
              *dst = ch;
LAB_004387e4:
              dst = dst + 1;
            }
            src = next;
          } while (next < buf_end);
        }
        bytesread = (int)dst - (int)buf;
      }
      return bytesread;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
#undef peekchr
#undef bytesread
#undef os_read
#undef buf_end
}



