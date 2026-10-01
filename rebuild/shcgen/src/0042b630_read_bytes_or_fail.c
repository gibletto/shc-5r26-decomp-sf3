#include "decls.h"
#include "imports.h"

// entry: 0042b630
// name : read_bytes_or_fail
// size : 79
// sig  : void read_bytes_or_fail(char * buf, uint size, FILE * in)


int __cdecl read_bytes_or_fail(char *buf,uint size,FILE *in)

{
  uint bytes_read;
  
  bytes_read = read_file_bytes(in,buf,size);
  if (bytes_read == 0xffffffff) {
    report_codegen_message(0xce6,1,0,0,(char *)0x0);
    return;
  }
  if (bytes_read != size) {
    report_codegen_message(0x1252,1,0,0,(char *)0x0);
  }
  return;
}



