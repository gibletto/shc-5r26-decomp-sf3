#include "decls.h"
#include "imports.h"

// entry: 00433230
// name : write_file_bytes
// size : 65
// sig  : uint write_file_bytes(FILE * out, char * buf, uint n)


uint __cdecl write_file_bytes(FILE *out,char *buf,uint n)

{
  uint written;
  
  if ((buf != (char *)0x0) && (out != (FILE *)0x0)) {
    if (0 < (int)n) {
      written = stock_fwrite(buf,n,1,out);
      if (written == 0) {
        n = 0xffffffff;
      }
      return n;
    }
    return 0xffffffff;
  }
  return 0xffffffff;
}



