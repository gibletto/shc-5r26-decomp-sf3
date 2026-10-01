#include "decls.h"
#include "imports.h"

// entry: 004331d0
// name : read_file_bytes
// size : 86
// sig  : uint read_file_bytes(FILE * in, char * buf, uint n)


uint __cdecl read_file_bytes(FILE *in,char *buf,uint n)

{
  uint got;
  
  if ((buf == (char *)0x0) || (in == (FILE *)0x0)) {
    got = 0xffffffff;
  }
  else {
    if ((int)n < 1) {
      return 0xffffffff;
    }
    got = __fread_lk(buf,1,n,in);
    if (got == 0) {
      if (feof(in)) {
        return (!ferror(in)) - 1;
      }
      return 0xffffffff;
    }
  }
  return got;
}



