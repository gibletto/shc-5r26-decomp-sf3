#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofa_record_out
#define g_ofa_record_out (*(FILE * *)(g_sd + 0x1e5e8))


// entry: 0041a6a0
// name : write_ofa_enter_record
// size : 78
// sig  : void write_ofa_enter_record(psd * rec)


int __cdecl write_ofa_enter_record(psd *rec)

{
  unsigned char _frec_2[4];
#define out_op (*(psd_op *)(_frec_2 + 0))
#define out_size (*(undefined1 *)(_frec_2 + 1))
  int code_size;
  uint written;
  
  out_op = rec->op;
  code_size = compute_record_code_size(rec);
  out_size = (undefined1)code_size;
  written = write_file_bytes(g_ofa_record_out,(char *)&out_op,2);
  if (written == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef out_op
#undef out_size
}



