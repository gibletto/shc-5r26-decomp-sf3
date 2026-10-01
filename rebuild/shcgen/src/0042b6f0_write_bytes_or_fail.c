#include "decls.h"
#include "imports.h"

// entry: 0042b6f0
// name : write_bytes_or_fail
// size : 50
// sig  : void write_bytes_or_fail(char * buf, uint size, FILE * out)


int __cdecl write_bytes_or_fail(char *buf,uint size,FILE *out)

{
  uint bytes_written;
  
  bytes_written = write_file_bytes(out,buf,size);
  if (bytes_written == 0xffffffff) {
    report_codegen_message(0xce7,1,0,0,(char *)0x0);
  }
  return;
}



