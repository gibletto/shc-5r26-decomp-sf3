#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e8e0
// name : write_ofb_exit_record
// size : 126
// sig  : void write_ofb_exit_record(psd * rec, int location, short pool_size)


int __cdecl write_ofb_exit_record(psd *rec,int location,short pool_size)

{
  unsigned char _frec_8[8];
#define out_rec (*(psd_op *)(_frec_8 + 0))
#define out_size (*(undefined1 *)(_frec_8 + 1))
#define out_location (*(undefined1 *)(_frec_8 + 2))
#define local_5 (*(undefined1 *)(_frec_8 + 3))
#define local_4 (*(undefined1 *)(_frec_8 + 4))
#define local_3 (*(undefined1 *)(_frec_8 + 5))
#define out_pool_size (*(short *)(_frec_8 + 6))
  short sVar1;
  uint uVar2;
  
  out_rec = rec->op;
  sVar1 = compute_record_code_size(rec);
  out_size = (undefined1)sVar1;
  out_location = (undefined1)location;
  local_5 = (*(unsigned char *)((char *)&location + 1));
  local_4 = (*(unsigned char *)((char *)&location + 2));
  local_3 = (*(unsigned char *)((char *)&location + 3));
  out_pool_size = pool_size;
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_rec,8);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_rec
#undef out_size
#undef out_location
#undef local_5
#undef local_4
#undef local_3
#undef out_pool_size
}



