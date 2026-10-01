#include "decls.h"
#include "imports.h"

// entry: 00418fc0
// name : write_final_literal_pool_flag
// size : 58
// sig  : void write_final_literal_pool_flag(FILE * lit_out)


int __cdecl write_final_literal_pool_flag(FILE *lit_out)

{
  unsigned char _frec_1[1];
#define flag (*(char *)(_frec_1 + 0))
  uint written;
  
  flag = '\x01';
  written = write_file_bytes(lit_out,&flag,1);
  if (written == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef flag
}



