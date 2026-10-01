#include "decls.h"
#include "imports.h"

// entry: 00438aa0
// name : stock_getdcwd
// size : 302
// sig  : char * stock_getdcwd(uint drive, char * buf, int maxlen)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * __cdecl stock_getdcwd(uint drive,char *buf,int maxlen)

{
  unsigned char _frec_10c[1048];
#define drvstr (*(char (*)[4])(_frec_10c + 0))
#define file_part (*(LPSTR *)(_frec_10c + 4))
#define dirbuf (*(CHAR (*)[260])(_frec_10c + 8))
  int valid;
  DWORD path_len;
  uint uVar1;
  uint n;
  char *src;
  char *pcVar2;
  char ch;
  
  if (drive == 0) {
    path_len = GetCurrentDirectoryA(0x104,dirbuf);
  }
  else {
    valid = __validdrive(drive);
    if (valid == 0) {
      stock_doserrno = 0xf;
      _stock_errno = 0xd;
      return (char *)0x0;
    }
    drvstr[0] = (char)drive + '@';
    drvstr[1] = 0x3a;
    drvstr[2] = 0x2e;
    drvstr[3] = 0;
    path_len = GetFullPathNameA(drvstr,0x104,dirbuf,&file_part);
  }
  if ((path_len == 0) || (uVar1 = path_len + 1, 0x104 < uVar1)) {
    return (char *)0x0;
  }
  if (buf == (char *)0x0) {
    if ((int)uVar1 <= maxlen) {
      uVar1 = maxlen;
    }
    buf = stock_malloc(uVar1);
    if (buf == (char *)0x0) {
      _stock_errno = 0xc;
      return (char *)0x0;
    }
  }
  else if (maxlen < (int)uVar1) {
    _stock_errno = 0x22;
    return (char *)0x0;
  }
  uVar1 = 0xffffffff;
  src = dirbuf;
  do {
    pcVar2 = src;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar2 = src + 1;
    ch = *src;
    src = pcVar2;
  } while (ch != '\0');
  uVar1 = ~uVar1;
  src = pcVar2 + -uVar1;
  pcVar2 = buf;
  for (n = uVar1 >> 2; n != 0; n = n - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)src;
    src = src + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar2 = *src;
    src = src + 1;
    pcVar2 = pcVar2 + 1;
  }
  return buf;
#undef drvstr
#undef file_part
#undef dirbuf
}



