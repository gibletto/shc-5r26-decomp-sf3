#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00408830
// name : write_asa_label_count_record
// size : 72
// sig  : void write_asa_label_count_record(char kind)


int __cdecl write_asa_label_count_record(char kind)

{
  unsigned char _frec_3[3];
#define rec_kind (*(char *)(_frec_3 + 0))
#define label_total (*(undefined2 *)(_frec_3 + 1))
  
  rec_kind = kind;
  write_bytes_or_fail(&rec_kind,1,g_asa_file);
  label_total = (undefined2)g_request->label_count;
  write_bytes_or_fail((char *)&label_total,2,g_asa_file);
  return;
#undef rec_kind
#undef label_total
}



