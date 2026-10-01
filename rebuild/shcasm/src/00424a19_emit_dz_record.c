#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 00424a19
// name : emit_dz_record
// size : 678
// sig  : void emit_dz_record(void)


int __cdecl emit_dz_record(void)

{
  unsigned char _frec_18[24];
#define size_code (*(char *)(_frec_18 + 0))
#define count_b0 (*(undefined1 *)(_frec_18 + 1))
#define count_b1 (*(undefined1 *)(_frec_18 + 2))
#define count_b2 (*(undefined1 *)(_frec_18 + 3))
#define count_b3 (*(undefined1 *)(_frec_18 + 4))
#define out_channel (*(short *)(_frec_18 + 8))
#define unit_count (*(undefined4 *)(_frec_18 + 12))
#define unit_bytes (*(short *)(_frec_18 + 16))
  uint nread;
  
  unit_count = 0;
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
    if (unit_count < 2) {
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + unit_bytes * unit_count;
      append_sized_value_to_data_record(&DAT_0043cdfc,unit_bytes / 2);
      if ((g_current_request->show & 2) != 0) {
        list_object_code_value((int *)&DAT_0043cdfc,unit_bytes / 2,0);
        out_channel = 3;
      }
    }
    else {
      flush_reloc_records();
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + unit_bytes * unit_count;
      append_object_record_byte(0xc0,0x9c);
      append_sized_value_to_repeat_data_record
                (*(int *)(&g_section_object_offsets + g_current_section_kind * 4),2);
      append_sized_value_to_repeat_data_record(unit_count,2);
      append_object_record_byte((uchar)unit_bytes,0x9c);
      append_sized_value_to_repeat_data_record(0,unit_bytes / 2);
      flush_reloc_records();
      if ((g_current_request->show & 2) != 0) {
        list_object_code_value(&unit_count,2,0);
        list_object_code_byte((char)unit_bytes,0);
        list_object_code_value((int *)&DAT_0043cdfc,unit_bytes / 2,0);
        out_channel = 3;
      }
      *(int *)(&g_section_object_offsets + g_current_section_kind * 4) =
           *(int *)(&g_section_object_offsets + g_current_section_kind * 4) +
           unit_bytes * unit_count;
    }
  }
  else {
    out_channel = 2;
  }
  if (out_channel != 0) {
    put_text_at_column(out_channel,s__DATAB_00441ddc,1);
    write_size_suffix(out_channel,(short)size_code,1);
    write_decimal(out_channel,unit_count,2);
    put_text_at_column(out_channel,&s_comma_0_00441e6c,2);
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
}
