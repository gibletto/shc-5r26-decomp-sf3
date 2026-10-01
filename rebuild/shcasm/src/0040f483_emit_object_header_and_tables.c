#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_object_language_tag_c
#define g_object_language_tag_c (*(unsigned char * *)(g_sd + 0x8030))
#undef g_object_language_tag_cpp
#define g_object_language_tag_cpp (*(unsigned char * *)(g_sd + 0x8060))
#undef g_object_record_cursor
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))


// entry: 0040f483
// name : emit_object_header_and_tables
// size : 1267
// sig  : void emit_object_header_and_tables(void)


int __cdecl emit_object_header_and_tables(void)

{
  unsigned char _frec_128[296];
#define full_path (*(uint (*)[65])(_frec_128 + 0))
#define src_file (*(request_source_file * *)(_frec_128 + 260))
#define file_count (*(ushort (*)[2])(_frec_128 + 264))
#define end_marker (*(ushort (*)[4])(_frec_128 + 268))
#define cur_section (*(request_section * *)(_frec_128 + 276))
#define i (*(int *)(_frec_128 + 284))
#define zero_offset (*(uint *)(_frec_128 + 288))
  char *pcVar1;
  uint path_len;
  
  g_object_record_buffer[0] = 'H';
  if (g_current_request->optimize != 0) {
    g_object_record_buffer[0] = 'h';
  }
  store_u16_big_endian((ushort *)&g_object_header_word,(ushort *)(g_object_record_buffer + 1));
  store_u16_big_endian((ushort *)&g_section_count,(ushort *)(g_object_record_buffer + 3));
  append_object_record_bytes(g_object_record_buffer,5,0x30);
  zero_offset = 0;
  if (g_program_size == 0) {
    store_u16_big_endian
              ((ushort *)g_current_request->sections->layout,(ushort *)g_object_record_buffer);
    store_u32_big_endian(&zero_offset,(uint *)(g_object_record_buffer + 2));
    store_u32_big_endian
              ((uint *)g_current_request->sections->size,(uint *)(g_object_record_buffer + 6));
    append_object_record_bytes(g_object_record_buffer,10,0x30);
  }
  else {
    for (i = 0; i < 4; i = i + 1) {
      for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
          cur_section = cur_section->next) {
        if (cur_section->size[i] != 0) {
          store_u16_big_endian
                    ((ushort *)(cur_section->layout->section_number + i),
                     (ushort *)g_object_record_buffer);
          store_u32_big_endian(&zero_offset,(uint *)(g_object_record_buffer + 2));
          store_u32_big_endian((uint *)(cur_section->size + i),(uint *)(g_object_record_buffer + 6))
          ;
          append_object_record_bytes(g_object_record_buffer,10,0x30);
        }
      }
    }
  }
  if (g_extra_section_needed == '\x01') {
    store_u16_big_endian
              ((ushort *)(g_current_request->sections->next->layout->section_number + 2),
               (ushort *)g_object_record_buffer);
    store_u32_big_endian(&zero_offset,(uint *)(g_object_record_buffer + 2));
    store_u32_big_endian
              ((uint *)(g_current_request->sections->next->size + 2),
               (uint *)(g_object_record_buffer + 6));
    append_object_record_bytes(g_object_record_buffer,10,0x30);
  }
  if (g_current_request->cpp_block == (request_cpp_block *)0x0) {
    copy_to_counted_string((char *)g_object_record_buffer,g_object_language_tag_c);
  }
  else {
    copy_to_counted_string((char *)g_object_record_buffer,g_object_language_tag_cpp);
  }
  append_object_record_bytes(g_object_record_buffer,(char)g_object_record_buffer[0] + 1,0x30);
  g_object_record_buffer[0] = g_current_request->compile_date[9];
  g_object_record_buffer[1] = g_current_request->compile_date[10];
  month_name_to_digits((char *)(g_object_record_buffer + 2),g_current_request->compile_date + 3);
  g_object_record_buffer[4] = g_current_request->compile_date[0];
  g_object_record_buffer[5] = g_current_request->compile_date[1];
  g_object_record_buffer[6] = g_current_request->compile_date[0xc];
  g_object_record_buffer[7] = g_current_request->compile_date[0xd];
  g_object_record_buffer[8] = g_current_request->compile_date[0xf];
  g_object_record_buffer[9] = g_current_request->compile_date[0x10];
  g_object_record_buffer[10] = g_current_request->compile_date[0x12];
  g_object_record_buffer[0xb] = g_current_request->compile_date[0x13];
  append_object_record_bytes(g_object_record_buffer,0xc,0x30);
  g_object_record_cursor = g_object_record_buffer;
  store_u16_big_endian((ushort *)&g_debug_word_1001,(ushort *)g_object_record_buffer);
  file_count[0] = 0;
  for (src_file = g_current_request->source_files; src_file != (request_source_file *)0x0;
      src_file = src_file->next) {
    file_count[0] = file_count[0] + 1;
  }
  store_u16_big_endian(file_count,(ushort *)(g_object_record_buffer + 2));
  append_object_record_bytes(g_object_record_buffer,4,0x40);
  i = 1;
  do {
    if ((short)file_count[0] < i) {
LAB_0040f94e:
      end_marker[0] = 0;
      store_u16_big_endian(end_marker,(ushort *)g_object_record_buffer);
      append_object_record_bytes(g_object_record_buffer,2,0x40);
      return;
    }
    for (src_file = g_current_request->source_files;
        (src_file != (request_source_file *)0x0 && (src_file->filno != i));
        src_file = src_file->next) {
    }
    if (src_file == (request_source_file *)0x0) {
      report_message_at_source_line(0,0,0x1358,(char *)0x0);
      goto LAB_0040f94e;
    }
    g_object_record_buffer[0] = '\0';
    append_object_record_bytes(g_object_record_buffer,1,0x40);
    pcVar1 = get_full_path(src_file->name,(char *)full_path);
    if (pcVar1 == (char *)0x0) {
      g_object_record_buffer[0] = (uchar)src_file->name_len;
      stock_strcpy((uint *)(g_object_record_buffer + 1),(uint *)src_file->name);
    }
    else {
      path_len = stock_strlen((char *)full_path);
      g_object_record_buffer[0] = (uchar)path_len;
      stock_strcpy((uint *)(g_object_record_buffer + 1),full_path);
    }
    append_object_record_bytes(g_object_record_buffer,g_object_record_buffer[0] + 1,0x40);
    i = i + 1;
  } while( true );
#undef full_path
#undef src_file
#undef file_count
#undef end_marker
#undef cur_section
#undef i
#undef zero_offset
}
