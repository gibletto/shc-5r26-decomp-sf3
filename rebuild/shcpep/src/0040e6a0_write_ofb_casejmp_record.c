#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e6a0
// name : write_ofb_casejmp_record
// size : 196
// sig  : void write_ofb_casejmp_record(psd * rec, int location)


int __cdecl write_ofb_casejmp_record(psd *rec,int location)

{
  unsigned char _frec_14[20];
#define out_rec (*(psd_op *)(_frec_14 + 0))
#define out_size (*(undefined1 *)(_frec_14 + 1))
#define out_location (*(undefined1 *)(_frec_14 + 2))
#define local_11 (*(undefined1 *)(_frec_14 + 3))
#define local_10 (*(undefined1 *)(_frec_14 + 4))
#define local_f (*(undefined1 *)(_frec_14 + 5))
#define local_e (*(undefined1 *)(_frec_14 + 6))
#define local_d (*(undefined1 *)(_frec_14 + 7))
#define local_c (*(undefined1 *)(_frec_14 + 8))
#define local_b (*(undefined1 *)(_frec_14 + 9))
#define local_a (*(undefined1 *)(_frec_14 + 10))
#define local_9 (*(undefined1 *)(_frec_14 + 11))
#define local_8 (*(undefined1 *)(_frec_14 + 12))
#define local_7 (*(undefined1 *)(_frec_14 + 13))
#define local_6 (*(undefined1 *)(_frec_14 + 14))
#define local_5 (*(undefined1 *)(_frec_14 + 15))
#define local_4 (*(undefined1 *)(_frec_14 + 16))
#define local_3 (*(undefined1 *)(_frec_14 + 17))
  short sVar1;
  uint uVar2;
  
  out_rec = rec->op;
  sVar1 = compute_record_code_size(rec);
  out_size = (undefined1)sVar1;
  local_11 = (*(unsigned char *)((char *)&location + 1));
  local_10 = (*(unsigned char *)((char *)&location + 2));
  out_location = (undefined1)location;
  local_e = (undefined1)rec->filno;
  local_d = *(undefined1 *)((int)&rec->filno + 1);
  local_b = *(undefined1 *)((int)&rec->linno + 1);
  local_f = (*(unsigned char *)((char *)&location + 3));
  local_c = (undefined1)rec->linno;
  local_a = *(undefined1 *)&rec->ea1;
  local_9 = *(undefined1 *)((int)&rec->ea1 + 1);
  local_8 = *(undefined1 *)((int)&rec->ea1 + 2);
  local_7 = *(undefined1 *)((int)&rec->ea1 + 3);
  local_6 = *(undefined1 *)&rec->ea2;
  local_5 = *(undefined1 *)((int)&rec->ea2 + 1);
  local_4 = *(undefined1 *)((int)&rec->ea2 + 2);
  local_3 = *(undefined1 *)((int)&rec->ea2 + 3);
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_rec,0x12);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_rec
#undef out_size
#undef out_location
#undef local_11
#undef local_10
#undef local_f
#undef local_e
#undef local_d
#undef local_c
#undef local_b
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
}



