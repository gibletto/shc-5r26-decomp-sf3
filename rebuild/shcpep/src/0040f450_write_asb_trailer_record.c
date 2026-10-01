#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_trailer_value1
#define g_asa_trailer_value1 (*(unsigned char *)(g_sd + 0x5d00))
#undef g_asa_trailer_value2
#define g_asa_trailer_value2 (*(unsigned char *)(g_sd + 0x6d48))
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))


// entry: 0040f450
// name : write_asb_trailer_record
// size : 137
// sig  : void write_asb_trailer_record(void)


int __cdecl write_asb_trailer_record(void)

{
  unsigned char _frec_8[8];
#define tag (*(char *)(_frec_8 + 0))
#define local_7 (*(undefined1 *)(_frec_8 + 1))
#define local_6 (*(undefined1 *)(_frec_8 + 2))
#define local_5 (*(undefined1 *)(_frec_8 + 3))
#define local_4 (*(undefined1 *)(_frec_8 + 4))
  uint written;
  
  local_7 = (undefined1)g_asa_trailer_value1;
  local_6 = (*(unsigned char *)((char *)&g_asa_trailer_value1 + 1));
  local_5 = (undefined1)g_asa_trailer_value2;
  local_4 = (*(unsigned char *)((char *)&g_asa_trailer_value2 + 1));
  tag = '\x0e';
  written = write_file_bytes(g_asb_output,&tag,5);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  written = write_file_bytes(g_asb_output,&g_asa_trailer_bytes,0x20);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  return;
#undef tag
#undef local_7
#undef local_6
#undef local_5
#undef local_4
}



