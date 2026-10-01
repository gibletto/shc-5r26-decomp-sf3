#include "decls.h"
#include "imports.h"

// entry: 00404800
// name : write_symbol_bytes
// size : 42
// sig  : void write_symbol_bytes(FILE * fp, char * buf, uint size)


int __cdecl write_symbol_bytes(FILE *fp,char *buf,uint size)

{
  uint written;
  
  written = write_bytes(fp,buf,size);
  if (written == 0xffffffff) {
    fatal_error(0xce7);
  }
  return;
}



