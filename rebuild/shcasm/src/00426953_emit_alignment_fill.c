#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 00426953
// name : emit_alignment_fill
// size : 314
// sig  : void __cdecl emit_alignment_fill(int alignment,int fill_bytes)


int __cdecl emit_alignment_fill(int alignment,int fill_bytes)

{
  unsigned char _frec_10[16];
#define nop_count (*(int *)(_frec_10 + 0))
#define out_channel (*(short *)(_frec_10 + 4))
#define nop_bytes (*(uchar (*)[4])(_frec_10 + 8))
  
  if ((fill_bytes < 1) || (0x1f < fill_bytes)) {
    report_message_at_source_line(0,0,0x133d,(char *)0x0);
  }
  if (g_current_request->code == 1) {
    if (g_current_request->endian == '\0') {
      nop_bytes[0] = '\t';
      nop_bytes[1] = '\0';
    }
    else {
      nop_bytes[0] = '\0';
      nop_bytes[1] = '\t';
    }
    nop_count = fill_bytes / 2;
    while( true ) {
      if (nop_count == 0) break;
      append_object_record_bytes(nop_bytes,2,0x1c);
      nop_count = nop_count + -1;
    }
  }
  g_location_counter = g_location_counter + fill_bytes;
  if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
    if ((g_current_request->show & 2) == 0) {
      out_channel = 2;
    }
    else {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
      out_channel = 3;
    }
    put_text_at_column(out_channel,s__ALIGN_00441f7c,1);
    write_decimal(out_channel,alignment,2);
    flush_output_line(out_channel);
  }
  return;
#undef nop_count
#undef out_channel
#undef nop_bytes
}
