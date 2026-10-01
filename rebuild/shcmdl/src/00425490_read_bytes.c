#include "decls.h"
#include "imports.h"

// entry: 00425490
// name : read_bytes
// size : 86
// sig  : uint read_bytes(FILE * fp, char * buf, uint size)


uint __cdecl read_bytes(FILE *fp,char *buf,uint size)

{
  uint count;
  
  if ((buf == (char *)0x0) || (fp == (FILE *)0x0)) {
    count = 0xffffffff;
  }
  else {
    if ((int)size < 1) {
      return 0xffffffff;
    }
    count = __fread_lk(buf,1,size,fp);
    if (count == 0) {
      if (feof(fp)) {
        return (!ferror(fp)) - 1;
      }
      return 0xffffffff;
    }
  }
  return count;
}



