#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))
#undef g_last_labno
#define g_last_labno (*(unsigned char *)(g_sd + 0x5be8))


// entry: 0040f400
// name : write_asb_label_count_record
// size : 74
// sig  : void write_asb_label_count_record(void)


int __cdecl write_asb_label_count_record(void)

{
  unsigned char _frec_4[4];
#define tag (*(char *)(_frec_4 + 0))
#define local_3 (*(undefined1 *)(_frec_4 + 1))
#define local_2 (*(undefined1 *)(_frec_4 + 2))
  uint written;
  
  local_3 = (undefined1)g_last_labno;
  local_2 = (*(unsigned char *)((char *)&g_last_labno + 1));
  tag = '\r';
  written = write_file_bytes(g_asb_output,&tag,3);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  return;
#undef tag
#undef local_3
#undef local_2
}



