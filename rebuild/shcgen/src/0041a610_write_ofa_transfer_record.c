#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofa_record_out
#define g_ofa_record_out (*(FILE * *)(g_sd + 0x1e5e8))


// entry: 0041a610
// name : write_ofa_transfer_record
// size : 137
// sig  : void write_ofa_transfer_record(psd * rec, int location, short pool_size)


int __cdecl write_ofa_transfer_record(psd *rec,int location,short pool_size)

{
  unsigned char _frec_c[12];
#define out_op (*(psd_op *)(_frec_c + 0))
#define out_size (*(undefined1 *)(_frec_c + 1))
#define local_a (*(undefined1 *)(_frec_c + 2))
#define local_9 (*(undefined1 *)(_frec_c + 3))
#define local_8 (*(undefined1 *)(_frec_c + 4))
#define local_7 (*(undefined1 *)(_frec_c + 5))
#define out_pool_size (*(short *)(_frec_c + 6))
#define out_flg (*(byte *)(_frec_c + 8))
  int code_size;
  uint written;
  
  out_op = rec->op;
  code_size = compute_record_code_size(rec);
  out_size = (undefined1)code_size;
  local_9 = (*(unsigned char *)((char *)&location + 1));
  local_a = (undefined1)location;
  local_8 = (*(unsigned char *)((char *)&location + 2));
  local_7 = (*(unsigned char *)((char *)&location + 3));
  out_flg = rec->flg & 0x40;
  out_pool_size = pool_size;
  written = write_file_bytes(g_ofa_record_out,(char *)&out_op,9);
  if (written == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_op
#undef out_size
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef out_pool_size
#undef out_flg
}



