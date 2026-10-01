#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e9e0
// name : write_ofb_op2e_record
// size : 98
// sig  : void write_ofb_op2e_record(psd * rec)


int __cdecl write_ofb_op2e_record(psd *rec)

{
  unsigned char _frec_100[256];
#define out_rec (*(psd_op *)(_frec_100 + 0))
#define out_size (*(undefined1 *)(_frec_100 + 1))
#define out_flg (*(byte *)(_frec_100 + 2))
  short sVar1;
  uint uVar2;
  
  out_rec = rec->op;
  sVar1 = compute_record_code_size(rec);
  out_size = (undefined1)sVar1;
  out_flg = rec->flg & 0xe3;
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_rec,3);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_rec
#undef out_size
#undef out_flg
}



