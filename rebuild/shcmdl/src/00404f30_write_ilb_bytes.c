#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_tree_out_file
#define g_tree_out_file (*(FILE * *)(g_sd + 0x26860))


// entry: 00404f30
// name : write_ilb_bytes
// size : 44
// sig  : void write_ilb_bytes(uint size, char * buf)


int __cdecl write_ilb_bytes(uint size,char *buf)

{
  uint written;
  
  written = write_bytes(g_tree_out_file,buf,size);
  if (written == 0xffffffff) {
    fatal_error(0xce7);
  }
  return;
}



