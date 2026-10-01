#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e650
// name : write_ofb_label_record
// size : 79
// sig  : void write_ofb_label_record(psd * rec)


int __cdecl write_ofb_label_record(psd *rec)

{
  unsigned char _frec_4[4];
#define out_rec (*(psd_op *)(_frec_4 + 0))
#define local_3 (*(undefined1 *)(_frec_4 + 1))
#define local_2 (*(undefined1 *)(_frec_4 + 2))
  uint written;
  
  out_rec = rec->op;
  local_3 = *(undefined1 *)&rec->ea1;
  local_2 = *(undefined1 *)((int)&rec->ea1 + 1);
  written = write_file_bytes(g_ofb_record_out,(char *)&out_rec,3);
  if (written == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_rec
#undef local_3
#undef local_2
}



