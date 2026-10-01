#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e800
// name : write_ofb_transfer_record
// size : 137
// sig  : void write_ofb_transfer_record(psd * rec, int location, short pool_size)


int __cdecl write_ofb_transfer_record(psd *rec,int location,short pool_size)

{
  unsigned char _frec_c[12];
#define out_rec (*(psd_op *)(_frec_c + 0))
#define out_size (*(undefined1 *)(_frec_c + 1))
#define out_location (*(undefined1 *)(_frec_c + 2))
#define local_9 (*(undefined1 *)(_frec_c + 3))
#define local_8 (*(undefined1 *)(_frec_c + 4))
#define local_7 (*(undefined1 *)(_frec_c + 5))
#define out_pool_size (*(short *)(_frec_c + 6))
#define out_flg (*(byte *)(_frec_c + 8))
  short sVar1;
  uint uVar2;
  
  out_rec = rec->op;
  sVar1 = compute_record_code_size(rec);
  out_size = (undefined1)sVar1;
  local_9 = (*(unsigned char *)((char *)&location + 1));
  out_location = (undefined1)location;
  local_8 = (*(unsigned char *)((char *)&location + 2));
  local_7 = (*(unsigned char *)((char *)&location + 3));
  out_flg = rec->flg & 0x40;
  out_pool_size = pool_size;
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_rec,9);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_rec
#undef out_size
#undef out_location
#undef local_9
#undef local_8
#undef local_7
#undef out_pool_size
#undef out_flg
}



