#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_stream
#define g_backend_stream (*(FILE * *)(g_sd + 0x8f98))


// entry: 0040305c
// name : read_backend_stream_bytes
// size : 78
// sig  : uint read_backend_stream_bytes(char * buf, uint count)


uint __cdecl read_backend_stream_bytes(char *buf,uint count)

{
  uint nread;
  
  nread = read_file_bytes(g_backend_stream,buf,count);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  return nread;
}



