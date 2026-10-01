#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sub_linno
#define g_sub_linno (*(unsigned short *)(g_sd + 0x5360))


// entry: 0041bfa0
// name : write_sub_bytes
// size : 69
// sig  : void write_sub_bytes(FILE * out, char * buf, uint n)


int __cdecl write_sub_bytes(FILE *out,char *buf,uint n)

{
  uint result;
  
  result = write_file_bytes(out,buf,n);
  if (result == 0xffffffff) {
    report_compiler_message(g_sub_filno,(uint)g_sub_linno,0xce7,(char *)0x0);
  }
  return;
}



