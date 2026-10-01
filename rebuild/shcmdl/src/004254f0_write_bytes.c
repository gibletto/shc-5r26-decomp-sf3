#include "decls.h"
#include "imports.h"

// entry: 004254f0
// name : write_bytes
// size : 65
// sig  : uint write_bytes(FILE * fp, char * buf, uint size)


uint __cdecl write_bytes(FILE *fp,char *buf,uint size)

{
  uint count;
  
  if ((buf != (char *)0x0) && (fp != (FILE *)0x0)) {
    if (0 < (int)size) {
      count = stock_fwrite_lk(buf,size,1,fp);
      if (count == 0) {
        size = 0xffffffff;
      }
      return size;
    }
    return 0xffffffff;
  }
  return 0xffffffff;
}



