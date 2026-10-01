#include "decls.h"
#include "imports.h"

// entry: 0042de91
// name : write_pool_flush_flag
// size : 66
// sig  : void __cdecl write_pool_flush_flag(FILE *lit_out)


int __cdecl write_pool_flush_flag(FILE *lit_out)

{
  unsigned char _frec_8[8];
#define flag_byte (*(char (*)[4])(_frec_8 + 0))
  uint written;
  
  flag_byte[0] = '\x01';
  written = write_file_bytes(lit_out,flag_byte,1);
  if (written == 0xffffffff) {
    report_message_at_source_line(0,0,0xce7,(char *)0x0);
  }
  return;
#undef flag_byte
}
