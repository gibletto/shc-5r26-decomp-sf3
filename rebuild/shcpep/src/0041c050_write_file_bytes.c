#include "decls.h"
#include "imports.h"

// entry: 0041c050
// name : write_file_bytes
// size : 65
// sig  : uint write_file_bytes(FILE * out, char * buf, uint n)


uint __cdecl write_file_bytes(FILE *out,char *buf,uint n)

{
  uint nwritten;
  
  if ((buf != (char *)0x0) && (out != (FILE *)0x0)) {
    if (0 < (int)n) {
      nwritten = __fwrite_lk(buf,n,1,out);
      if (nwritten == 0) {
        n = 0xffffffff;
      }
      return n;
    }
    return 0xffffffff;
  }
  return 0xffffffff;
}



