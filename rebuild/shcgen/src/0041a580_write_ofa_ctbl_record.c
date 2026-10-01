#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofa_record_out
#define g_ofa_record_out (*(FILE * *)(g_sd + 0x1e5e8))


// entry: 0041a580
// name : write_ofa_ctbl_record
// size : 135
// sig  : void write_ofa_ctbl_record(psd * rec, int location)


int __cdecl write_ofa_ctbl_record(psd *rec,int location)

{
  unsigned char _frec_f[15];
#define uStack_f (*(undefined1 *)(_frec_f + 0))
#define uStack_e (*(undefined1 *)(_frec_f + 1))
#define uStack_d (*(undefined1 *)(_frec_f + 2))
#define out_op (*(psd_op *)(_frec_f + 3))
#define local_b (*(undefined1 *)(_frec_f + 4))
#define local_a (*(undefined1 *)(_frec_f + 5))
#define local_9 (*(undefined1 *)(_frec_f + 6))
#define local_8 (*(undefined1 *)(_frec_f + 7))
#define local_7 (*(undefined1 *)(_frec_f + 8))
#define local_6 (*(undefined1 *)(_frec_f + 9))
#define local_5 (*(undefined1 *)(_frec_f + 10))
#define local_4 (*(undefined1 *)(_frec_f + 11))
  int table_bytes;
  uint written;
  
  out_op = rec->op;
  table_bytes = (int)rec->filno << 2;
  local_b = (undefined1)table_bytes;
  uStack_f = (undefined1)((uint)table_bytes >> 8);
  uStack_e = (undefined1)((uint)table_bytes >> 0x10);
  uStack_d = (undefined1)((uint)table_bytes >> 0x18);
  local_a = uStack_f;
  local_9 = uStack_e;
  local_8 = uStack_d;
  local_7 = (undefined1)location;
  local_6 = (*(unsigned char *)((char *)&location + 1));
  local_5 = (*(unsigned char *)((char *)&location + 2));
  local_4 = (*(unsigned char *)((char *)&location + 3));
  written = write_file_bytes(g_ofa_record_out,(char *)&out_op,9);
  if (written == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef uStack_f
#undef uStack_e
#undef uStack_d
#undef out_op
#undef local_b
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
}



