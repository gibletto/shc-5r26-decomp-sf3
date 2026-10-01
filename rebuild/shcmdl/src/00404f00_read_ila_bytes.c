#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_tree_in_file
#define g_tree_in_file (*(FILE * *)(g_sd + 0x26eec))


// entry: 00404f00
// name : read_ila_bytes
// size : 48
// sig  : void read_ila_bytes(uint size, char * buf)


int __cdecl read_ila_bytes(uint size,char *buf)

{
  uint nread;
  
  nread = read_bytes(g_tree_in_file,buf,size);
  if ((nread == 0) || (nread == 0xffffffff)) {
    fatal_error(0xce6);
  }
  return;
}



