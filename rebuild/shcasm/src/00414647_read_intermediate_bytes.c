#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_intermediate_file
#define g_intermediate_file (*(FILE * *)(g_sd + 0x9308))


// entry: 00414647
// name : read_intermediate_bytes
// size : 63
// sig  : void __cdecl read_intermediate_bytes(char *buf,uint size)


int __cdecl read_intermediate_bytes(char *buf,uint size)

{
  uint read_status;
  
  read_status = read_file_bytes(g_intermediate_file,buf,size);
  if (read_status == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  return;
}
