#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_debug_record_cursor
#define g_debug_record_cursor (*(unsigned char * *)(g_sd + 0x13030))
#undef g_debug_record_input
#define g_debug_record_input (*(FILE * *)(g_sd + 0xcf20))
#undef g_debug_symbol_input
#define g_debug_symbol_input (*(FILE * *)(g_sd + 0xcf24))
#undef g_line_range_temp
#define g_line_range_temp (*(FILE * *)(g_sd + 0x128bc))
#undef g_object_record_cursor
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))
#undef g_register_map_temp
#define g_register_map_temp (*(FILE * *)(g_sd + 0x13020))
#undef g_register_variable_input
#define g_register_variable_input (*(FILE * *)(g_sd + 0x128c0))
#undef g_stack_offset_temp
#define g_stack_offset_temp (*(FILE * *)(g_sd + 0xcefc))


// entry: 0040f000
// name : emit_debug_information
// size : 1069
// sig  : void emit_debug_information(void)


int __cdecl emit_debug_information(void)

{
  int iVar1;
  uint read_status;
  uint bytes_read;
  
  flush_source_line_ranges(1);
  if ((g_current_request->optimize != 0) && (g_debug_function_label != 0)) {
    iVar1 = update_register_variable_map();
    close_debug_scope_range(0,iVar1);
    flush_register_variable_map();
    free_expno_register_variable_table();
    close_debug_scope_range(0,0);
    close_debug_scope_range(0,0);
  }
  g_scope_stack[g_scope_top]->end = g_location_counter;
  g_scope_top = g_scope_top + -1;
  g_debug_record_input = stock_fopen(g_current_request->db1_path,&s_rb_00440cd8);
  if (g_debug_record_input == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  g_debug_symbol_input = stock_fopen(g_current_request->db2_path,&s_rb_00440cdc);
  if (g_debug_symbol_input == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  if ((g_current_request->optimize != 0) &&
     (iVar1 = _fclose(g_register_variable_input), iVar1 == -1)) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  iVar1 = stock_fseek(g_line_range_temp,0,0);
  if (iVar1 != 0) {
    report_message_at_source_line(0,0,0x1356,(char *)0x0);
  }
  iVar1 = stock_fseek(g_stack_offset_temp,0,0);
  if (iVar1 != 0) {
    report_message_at_source_line(0,0,0x1356,(char *)0x0);
  }
  iVar1 = stock_fseek(g_register_map_temp,0,0);
  if (iVar1 != 0) {
    report_message_at_source_line(0,0,0x1356,(char *)0x0);
  }
  g_debug_scope_depth = -1;
  g_object_record_cursor = g_object_record_buffer;
  emit_object_header_and_tables();
  bytes_read = read_file_bytes(g_debug_record_input,(char *)&g_debug_record_tag,2);
  if (bytes_read == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  else if ((bytes_read != 0) &&
          (read_status = read_file_bytes(g_debug_record_input,(char *)g_debug_record_body,
                                         g_temp_record_length - 2), read_status == 0xffffffff)) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  while (bytes_read != 0) {
    g_debug_record_cursor = g_debug_record_body;
    g_object_record_cursor = g_object_record_buffer;
    switch(g_debug_record_tag & 0x7f) {
    case 0x32:
      translate_scope_record();
      break;
    default:
      report_message_at_source_line(0,0,0x1357,(char *)0x0);
      break;
    case 0x34:
      translate_debug_symbol_record();
      break;
    case 0x36:
    case 0x48:
    case 0x4a:
    case 0x4c:
    case 0x50:
      translate_short_tagged_record((uint)g_debug_record_tag);
      break;
    case 0x44:
      translate_tag44_record();
      break;
    case 0x4e:
      translate_tag4e_record();
    }
    append_object_record_bytes((uchar *)0x0,0,0xff);
    bytes_read = read_file_bytes(g_debug_record_input,(char *)&g_debug_record_tag,2);
    if (bytes_read == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    else if ((bytes_read != 0) &&
            (read_status = read_file_bytes(g_debug_record_input,(char *)g_debug_record_body,
                                           g_temp_record_length - 2), read_status == 0xffffffff)) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
  }
  g_object_record_cursor = g_object_record_buffer;
  emit_spooled_tag38_records();
  iVar1 = _fclose(g_debug_record_input);
  if (iVar1 == -1) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  iVar1 = _fclose(g_debug_symbol_input);
  if (iVar1 == -1) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  return;
}
