#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))


// entry: 0040f120
// name : write_asb_tag6_record
// size : 56
// sig  : void write_asb_tag6_record(void)


int __cdecl write_asb_tag6_record(void)

{
  unsigned char _frec_1[1];
#define tag (*(char *)(_frec_1 + 0))
  uint written;
  
  tag = '\x06';
  written = write_file_bytes(g_asb_output,&tag,1);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  return;
#undef tag
}



