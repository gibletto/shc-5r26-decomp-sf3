#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e960
// name : write_ofb_end_record
// size : 125
// sig  : void write_ofb_end_record(psd * rec, int location)


int __cdecl write_ofb_end_record(psd *rec,int location)

{
  unsigned char _frec_c[12];
#define out_rec (*(psd_op *)(_frec_c + 0))
#define out_location (*(undefined1 *)(_frec_c + 1))
#define local_a (*(undefined1 *)(_frec_c + 2))
#define local_9 (*(undefined1 *)(_frec_c + 3))
#define local_8 (*(undefined1 *)(_frec_c + 4))
#define local_7 (*(undefined1 *)(_frec_c + 5))
#define local_6 (*(undefined1 *)(_frec_c + 6))
#define local_5 (*(undefined1 *)(_frec_c + 7))
#define local_4 (*(undefined1 *)(_frec_c + 8))
  uint uVar1;
  
  out_rec = rec->op;
  out_location = (undefined1)location;
  local_a = (*(unsigned char *)((char *)&location + 1));
  local_9 = (*(unsigned char *)((char *)&location + 2));
  local_7 = *(undefined1 *)&rec->ea2;
  local_8 = (*(unsigned char *)((char *)&location + 3));
  local_6 = *(undefined1 *)((int)&rec->ea2 + 1);
  local_5 = *(undefined1 *)((int)&rec->ea2 + 2);
  local_4 = *(undefined1 *)((int)&rec->ea2 + 3);
  uVar1 = write_file_bytes(g_ofb_record_out,(char *)&out_rec,9);
  if (uVar1 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_rec
#undef out_location
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
}



