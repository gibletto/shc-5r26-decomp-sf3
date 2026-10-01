#include "decls.h"
#include "imports.h"

// entry: 00433180
// name : write_sua_bytes
// size : 69
// sig  : void write_sua_bytes(FILE * out, char * buf, uint n)


int __cdecl write_sua_bytes(FILE *out,char *buf,uint n)

{
  uint written;
  
  written = write_file_bytes(out,buf,n);
  if (written == 0xffffffff) {
    report_compiler_message(g_sua_filno,(uint)g_sua_linno,0xce7,(char *)0x0);
  }
  return;
}



