#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 00425a51
// name : emit_string_data_record
// size : 1372
// sig  : void emit_string_data_record(void)


int __cdecl emit_string_data_record(void)

{
  unsigned char _frec_20[32];
#define line_len (*(short *)(_frec_20 + 0))
#define remaining (*(int *)(_frec_20 + 8))
#define string_len (*(int *)(_frec_20 + 12))
#define in_quote (*(short *)(_frec_20 + 16))
#define line_width (*(short *)(_frec_20 + 20))
#define ch_byte (*(uchar (*)[4])(_frec_20 + 24))
  short unprintable;
  uint nread;
  bool in_hex_line;
  
  nread = read_file_bytes(g_backend_record_input,(char *)&string_len,4);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  if (g_current_request->code == 1) {
    in_hex_line = false;
    in_quote = 0;
    remaining = string_len;
    line_width = ((short)g_output_channels[3].end - (short)g_column_starts[2]) + -1;
    while (0 < remaining) {
      nread = read_file_bytes(g_backend_record_input,(char *)ch_byte,1);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      if (0x800 < g_section_data_bytes + 0x200) {
        flush_reloc_records();
      }
      append_object_record_byte(ch_byte[0],0x1c);
      if ((g_current_request->show & 2) != 0) {
        unprintable = is_unprintable_char((short)(char)ch_byte[0]);
        if (unprintable == 0) {
          if (in_hex_line) {
            flush_output_line(3);
            in_hex_line = false;
          }
          if (in_quote == 0) {
            format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
            put_text_at_column(3,s__SDATA_00441df4,1);
            line_len = 1;
            put_char_at_column(3,'\"',2);
            in_quote = 1;
          }
          else if ((int)((int)line_width - (uint)(ch_byte[0] == '\"')) <= (int)line_len) {
            put_char_at_column(3,'\"',2);
            flush_output_line(3);
            format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
            put_text_at_column(3,s__SDATA_00441df4,1);
            line_len = 1;
            put_char_at_column(3,'\"',2);
          }
          list_object_code_byte(ch_byte[0],0);
          unprintable = line_len + 1;
          if (ch_byte[0] == '\"') {
            put_char_at_column(3,'\"',2);
            unprintable = line_len + 2;
          }
          line_len = unprintable;
          put_char_at_column(3,ch_byte[0],2);
        }
        else {
          if (in_quote == 1) {
            put_char_at_column(3,'\"',2);
            flush_output_line(3);
            in_quote = 0;
          }
          if (in_hex_line) {
            put_char_at_column(3,',',2);
          }
          else {
            format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
            put_text_at_column(3,s__DATA_B_00441e98,1);
            in_hex_line = true;
          }
          list_object_code_byte(ch_byte[0],0);
          put_text_at_column(3,&s_H_apos_00441ea0,2);
          write_hex_byte(3,(int)(char)ch_byte[0],2);
        }
      }
      remaining = remaining + -1;
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + 1;
    }
    if ((g_current_request->show & 2) != 0) {
      if (in_quote == 1) {
        put_char_at_column(3,'\"',2);
      }
      flush_output_line(3);
    }
  }
  else {
    in_hex_line = false;
    in_quote = 0;
    line_width = ((short)g_output_channels[2].end - (short)g_column_starts[2]) + -1;
    for (remaining = string_len; 0 < remaining; remaining = remaining + -1) {
      nread = read_file_bytes(g_backend_record_input,(char *)ch_byte,1);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      unprintable = is_unprintable_char((short)(char)ch_byte[0]);
      if (unprintable == 0) {
        if (in_hex_line) {
          flush_output_line(2);
          in_hex_line = false;
        }
        if (in_quote == 0) {
          put_text_at_column(2,s__SDATA_00441df4,1);
          line_len = 1;
          put_char_at_column(2,'\"',2);
          in_quote = 1;
        }
        else if ((int)((int)line_width - (uint)(ch_byte[0] == '\"')) <= (int)line_len) {
          put_char_at_column(2,'\"',2);
          flush_output_line(2);
          put_text_at_column(2,s__SDATA_00441df4,1);
          line_len = 1;
          put_char_at_column(2,'\"',2);
        }
        unprintable = line_len + 1;
        if (ch_byte[0] == '\"') {
          put_char_at_column(2,'\"',2);
          unprintable = line_len + 2;
        }
        line_len = unprintable;
        put_char_at_column(2,ch_byte[0],2);
      }
      else {
        if (in_quote == 1) {
          put_char_at_column(2,'\"',2);
          flush_output_line(2);
          in_quote = 0;
        }
        if (in_hex_line) {
          put_char_at_column(2,',',2);
        }
        else {
          put_text_at_column(2,s__DATA_B_00441ea4,1);
          in_hex_line = true;
        }
        put_text_at_column(2,&s_H_apos_00441eac,2);
        write_hex_byte(2,(int)(char)ch_byte[0],2);
      }
    }
    if (in_quote == 1) {
      put_char_at_column(2,'\"',2);
    }
    flush_output_line(2);
  }
  return;
#undef line_len
#undef remaining
#undef string_len
#undef in_quote
#undef line_width
#undef ch_byte
}
