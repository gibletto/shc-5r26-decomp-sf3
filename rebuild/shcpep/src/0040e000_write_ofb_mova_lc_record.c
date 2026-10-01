#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e000
// name : write_ofb_mova_lc_record
// size : 161
// sig  : void write_ofb_mova_lc_record(psd * rec)


int __cdecl write_ofb_mova_lc_record(psd *rec)

{
  unsigned char _frec_c[12];
#define out_rec (*(psd_op *)(_frec_c + 0))
#define out_size (*(undefined1 *)(_frec_c + 1))
#define out_flg (*(byte *)(_frec_c + 2))
#define local_9 (*(undefined1 *)(_frec_c + 3))
#define local_8 (*(undefined1 *)(_frec_c + 4))
#define local_7 (*(undefined1 *)(_frec_c + 5))
#define local_6 (*(undefined1 *)(_frec_c + 6))
#define local_5 (*(undefined1 *)(_frec_c + 7))
#define local_4 (*(undefined1 *)(_frec_c + 8))
#define local_3 (*(undefined1 *)(_frec_c + 9))
#define local_2 (*(undefined1 *)(_frec_c + 10))
  short sVar1;
  uint uVar2;
  ea *loc_ea;
  
  out_rec = rec->op;
  sVar1 = compute_record_code_size(rec);
  out_size = (undefined1)sVar1;
  out_flg = rec->flg & 0xe3;
  if (rec->ea2->base == '\0') {
    out_flg = out_flg | 0x10;
  }
  loc_ea = rec->ea1;
  local_9 = (undefined1)loc_ea->disp;
  local_8 = *(undefined1 *)((int)&loc_ea->disp + 1);
  local_5 = (undefined1)rec->sptravel;
  local_7 = *(undefined1 *)((int)&loc_ea->disp + 2);
  local_4 = *(undefined1 *)((int)&rec->sptravel + 1);
  local_6 = *(undefined1 *)((int)&loc_ea->disp + 3);
  local_3 = *(undefined1 *)((int)&rec->sptravel + 2);
  local_2 = *(undefined1 *)((int)&rec->sptravel + 3);
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_rec,0xb);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_rec
#undef out_size
#undef out_flg
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
#undef local_2
}



