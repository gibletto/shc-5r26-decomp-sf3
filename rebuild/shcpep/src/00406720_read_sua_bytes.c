#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sua_read_file
#define g_sua_read_file (*(FILE * *)(g_sd + 0x5238))


// entry: 00406720
// name : read_sua_bytes
// size : 58
// sig  : uint read_sua_bytes(char * buf, uint count)


uint __cdecl read_sua_bytes(char *buf,uint count)

{
  uint result;
  
  result = read_file_bytes(g_sua_read_file,buf,count);
  if (result == 0xffffffff) {
    report_compiler_message(0,0,0xce6,(char *)0x0);
  }
  return result;
}



