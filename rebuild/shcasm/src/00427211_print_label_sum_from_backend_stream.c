#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))


// entry: 00427211
// name : print_label_sum_from_backend_stream
// size : 173
// sig  : void __cdecl print_label_sum_from_backend_stream(short stream,short count,short continued)


int __cdecl print_label_sum_from_backend_stream(short stream,short count,short continued)

{
  unsigned char _frec_c[12];
#define i (*(short *)(_frec_c + 0))
#define term_labno (*(short (*)[2])(_frec_c + 4))
  uint nread;
  
  for (i = 0; i < count; i = i + 1) {
    nread = read_file_bytes(g_backend_record_input,(char *)term_labno,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if ((continued == 1) && (0 < term_labno[0])) {
      put_char_at_column(stream,'+',2);
    }
    write_label_name(stream,term_labno[0],2);
    continued = 1;
  }
  return;
#undef i
#undef term_labno
}
