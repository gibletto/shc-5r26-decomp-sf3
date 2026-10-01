#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_doserrno
#define stock_doserrno (*(unsigned int *)(g_sd + 0x81b4))
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 00438850
// name : stock_write
// size : 555
// sig  : int stock_write(uint fh, char * buf, uint cnt)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl stock_write(uint fh,char *buf,uint cnt)

{
  unsigned char _frec_418[1048];
#define dosretval (*(uint *)(_frec_418 + 0))
#define os_written (*(DWORD *)(_frec_418 + 4))
#define ioinfo_block (*(int * *)(_frec_418 + 8))
#define ioinfo_ofs (*(int *)(_frec_418 + 12))
#define charcount (*(DWORD *)(_frec_418 + 16))
#define lfbuf (*(char (*)[1028])(_frec_418 + 20))
  BOOL BVar1;
  char *dst;
  int lfcount;
  char *src;
  char ch;
  byte osfile;
  
  if (fh < stock_nhandle) {
    ioinfo_block = (int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3));
    ioinfo_ofs = (fh & 0x1f) * 8;
    osfile = *(byte *)(*ioinfo_block + 4 + ioinfo_ofs);
    if ((osfile & 1) != 0) {
      lfcount = 0;
      charcount = 0;
      if (cnt == 0) {
        return 0;
      }
      if ((osfile & 0x20) != 0) {
        stock_lseek(fh,0,2);
      }
      if ((*(byte *)((undefined4 *)(ioinfo_ofs + *ioinfo_block) + 1) & 0x80) == 0) {
        BVar1 = WriteFile(*(HANDLE *)(ioinfo_ofs + *ioinfo_block),buf,cnt,&os_written,
                          (LPOVERLAPPED)0x0);
        if (BVar1 == 0) {
LAB_00438995:
          dosretval = GetLastError();
        }
        else {
          dosretval = 0;
          charcount = os_written;
        }
      }
      else {
        dosretval = 0;
        src = buf;
        do {
          if (cnt <= (uint)((int)src - (int)buf)) break;
          dst = lfbuf;
          do {
            if (cnt <= (uint)((int)src - (int)buf)) break;
            ch = *src;
            src = src + 1;
            if (ch == '\n') {
              *dst = '\r';
              lfcount = lfcount + 1;
              dst = dst + 1;
            }
            *dst = ch;
            dst = dst + 1;
          } while ((int)dst - (int)lfbuf < 0x400);
          BVar1 = WriteFile(*(HANDLE *)(*ioinfo_block + ioinfo_ofs),lfbuf,(int)dst - (int)lfbuf,
                            &os_written,(LPOVERLAPPED)0x0);
          if (BVar1 == 0) goto LAB_00438995;
          charcount = charcount + os_written;
        } while ((int)dst - (int)lfbuf <= (int)os_written);
      }
      if (charcount != 0) {
        return charcount - lfcount;
      }
      if (dosretval == 0) {
        if (((*(byte *)(*ioinfo_block + 4 + ioinfo_ofs) & 0x40) != 0) && (*buf == '\x1a')) {
          return 0;
        }
        _stock_errno = 0x1c;
        stock_doserrno = 0;
        return -1;
      }
      if (dosretval != 5) {
        stock_dosmaperr(dosretval);
        return -1;
      }
      _stock_errno = 9;
      stock_doserrno = dosretval;
      return -1;
    }
  }
  _stock_errno = 9;
  stock_doserrno = 0;
  return -1;
#undef dosretval
#undef os_written
#undef ioinfo_block
#undef ioinfo_ofs
#undef charcount
#undef lfbuf
}



