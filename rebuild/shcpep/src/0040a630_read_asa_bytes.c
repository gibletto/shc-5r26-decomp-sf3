#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_input
#define g_asa_input (*(FILE * *)(g_sd + 0x5348))


// entry: 0040a630
// name : read_asa_bytes
// size : 52
// sig  : void read_asa_bytes(char * buf, uint size)


int __cdecl read_asa_bytes(char *buf,uint size)

{
  uint rc;
  
  rc = read_file_bytes(g_asa_input,buf,size);
  if (rc == 0xffffffff) {
    report_compiler_message(0,0,0xce6,(char *)0x0);
  }
  return;
}



