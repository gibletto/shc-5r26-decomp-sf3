#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 00425891
// name : emit_reserve_record
// size : 443
// sig  : void emit_reserve_record(void)


int __cdecl emit_reserve_record(void)

{
  unsigned char _frec_1c[28];
#define size_code (*(char *)(_frec_1c + 0))
#define count_b0 (*(undefined1 *)(_frec_1c + 1))
#define count_b1 (*(undefined1 *)(_frec_1c + 2))
#define count_b2 (*(undefined1 *)(_frec_1c + 3))
#define count_b3 (*(undefined1 *)(_frec_1c + 4))
#define out_channel (*(short *)(_frec_1c + 8))
#define unit_count (*(undefined4 *)(_frec_1c + 12))
#define unit_bytes (*(short *)(_frec_1c + 16))
#define total_bytes (*(int *)(_frec_1c + 20))
  uint nread;
  
  unit_count = 0;
  total_bytes = 0;
  nread = read_file_bytes(g_backend_record_input,&size_code,5);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  unit_count = CONCAT13(count_b3,CONCAT12(count_b2,CONCAT11(count_b1,count_b0)));
  if (size_code == '\0') {
    unit_bytes = 1;
  }
  else if (size_code == '\x01') {
    unit_bytes = 2;
  }
  else {
    unit_bytes = 4;
  }
  out_channel = 0;
  if (g_current_request->code == 1) {
    if ((g_current_request->show & 2) != 0) {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
    }
    if (g_current_section_kind != 3) {
      g_object_record_break = 1;
    }
    *(int *)(&g_section_location_counters)[g_current_section_kind] =
         *(int *)(&g_section_location_counters)[g_current_section_kind] + unit_bytes * unit_count;
    if ((g_current_request->show & 2) != 0) {
      total_bytes = unit_bytes * unit_count;
      list_object_code_value(&total_bytes,2,0);
      out_channel = 3;
    }
    *(int *)(&g_section_object_offsets + g_current_section_kind * 4) =
         *(int *)(&g_section_object_offsets + g_current_section_kind * 4) + unit_bytes * unit_count;
  }
  else {
    out_channel = 2;
  }
  if (out_channel != 0) {
    put_text_at_column(out_channel,&s_dot_RES_00441dec,1);
    write_size_suffix(out_channel,(short)size_code,1);
    write_decimal(out_channel,unit_count,2);
    flush_output_line(out_channel);
  }
  return;
#undef size_code
#undef count_b0
#undef count_b1
#undef count_b2
#undef count_b3
#undef out_channel
#undef unit_count
#undef unit_bytes
#undef total_bytes
}
