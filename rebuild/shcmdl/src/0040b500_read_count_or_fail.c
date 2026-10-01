#include "decls.h"
#include "imports.h"

// entry: 0040b500
// name : read_count_or_fail
// size : 48
// sig  : uint read_count_or_fail(FILE * fp, char * buf, uint size)


uint __cdecl read_count_or_fail(FILE *fp,char *buf,uint size)

{
  uint got;
  
  got = read_bytes(fp,buf,size);
  if (got == 0xffffffff) {
    fatal_error(0xce6);
  }
  return got;
}



