#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 0041793f
// name : emit_switch_table
// size : 684
// sig  : void __cdecl emit_switch_table(short table_label,short base_label,int short_entries)


int __cdecl emit_switch_table(short table_label,short base_label,int short_entries)

{
  unsigned char _frec_1c[28];
#define out_stream (*(short *)(_frec_1c + 0))
#define i (*(int *)(_frec_1c + 4))
#define pad_value (*(int *)(_frec_1c + 8))
#define entry_count (*(short (*)[2])(_frec_1c + 12))
#define local_c (*(char (*)[4])(_frec_1c + 16))
#define local_8 (*(char (*)[4])(_frec_1c + 20))
  uint uVar1;
  
  out_stream = 0;
  if (g_current_request->code == 1) {
    if ((g_current_request->show & 2) != 0) {
      out_stream = 3;
    }
  }
  else {
    out_stream = 2;
  }
  if (((short_entries == 0) || (g_current_request->cpu != 0)) &&
     (uVar1 = g_location_counter >> 0x1f,
     ((g_location_counter ^ uVar1) - uVar1 & 3 ^ uVar1) != uVar1)) {
    if (g_current_request->code == 1) {
      if ((g_current_request->show & 2) != 0) {
        format_listing_location(g_location_counter);
      }
      g_object_record_break = 1;
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + 2;
      if ((g_current_request->show & 2) != 0) {
        pad_value = 2;
        list_object_code_value(&pad_value,2,0);
      }
      *(int *)(&g_section_object_offsets + g_current_section_kind * 4) =
           *(int *)(&g_section_object_offsets + g_current_section_kind * 4) + 2;
    }
    else {
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + 2;
    }
    if (out_stream != 0) {
      put_text_at_column(out_stream,&s_dot_RES_00441960,1);
      write_size_suffix(out_stream,1,1);
      write_decimal(out_stream,1,2);
      flush_output_line(out_stream);
    }
  }
  if ((g_current_request->code != 1) || ((g_current_request->show & 2) != 0)) {
    if ((g_current_request->show & 2) != 0) {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
    }
    write_label_name(out_stream,table_label,0);
    flush_output_line(out_stream);
  }
  uVar1 = read_file_bytes(g_backend_record_input,local_c,1);
  if (uVar1 == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  uVar1 = read_file_bytes(g_backend_record_input,(char *)entry_count,2);
  if (uVar1 == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  uVar1 = read_file_bytes(g_backend_record_input,local_8,2);
  if (uVar1 == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  for (i = 0; i < entry_count[0]; i = i + 1) {
    emit_switch_table_entry(table_label,base_label,short_entries);
  }
  return;
#undef out_stream
#undef i
#undef pad_value
#undef entry_count
#undef local_c
#undef local_8
}
