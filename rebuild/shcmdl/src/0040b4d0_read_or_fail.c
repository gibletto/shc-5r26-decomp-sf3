#include "decls.h"
#include "imports.h"

// entry: 0040b4d0
// name : read_or_fail
// size : 42
// sig  : void read_or_fail(FILE * fp, char * buf, uint size)


int __cdecl read_or_fail(FILE *fp,char *buf,uint size)

{
  uint got;
  
  got = read_bytes(fp,buf,size);
  if (got == 0xffffffff) {
    fatal_error(0xce6);
  }
  return;
}



