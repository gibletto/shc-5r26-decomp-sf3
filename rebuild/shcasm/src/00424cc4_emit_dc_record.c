#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 00424cc4
// name : emit_dc_record
// size : 2685
// sig  : void emit_dc_record(void)


int __cdecl emit_dc_record(void)

{
  unsigned char _frec_38[56];
#define long_value (*(uint *)(_frec_38 + 0))
#define size_code (*(char (*)[4])(_frec_38 + 4))
#define word_value (*(short (*)[2])(_frec_38 + 8))
#define ref_count (*(int *)(_frec_38 + 12))
#define offset_written (*(ushort *)(_frec_38 + 16))
#define item_count (*(int *)(_frec_38 + 20))
#define next_ref (*(label_ref * *)(_frec_38 + 24))
#define byte_value (*(uchar (*)[4])(_frec_38 + 28))
#define cur_ref (*(label_ref * *)(_frec_38 + 32))
#define out_value (*(uint *)(_frec_38 + 36))
#define swapped_value (*(uint *)(_frec_38 + 40))
#define ref_head (*(label_ref *)(_frec_38 + 44))
  uint nread;
  int bytes_added;
  bool has_offset;
  
  nread = read_file_bytes(g_backend_record_input,size_code,1);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  nread = read_file_bytes(g_backend_record_input,(char *)&item_count,4);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  if (g_current_request->code == 1) {
    if ((g_current_request->show & 2) != 0) {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
      put_text_at_column(3,s__DATA_00441de4,1);
      write_size_suffix(3,(short)size_code[0],1);
    }
    if (size_code[0] == '\0') {
      for (; 0 < item_count; item_count = item_count + -1) {
        nread = read_file_bytes(g_backend_record_input,(char *)byte_value,1);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_backend_record_input,(char *)&ref_count,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (0x800 < g_section_data_bytes + 0x200) {
          flush_reloc_records();
        }
        if (ref_count == 0) {
          append_object_record_byte(byte_value[0],0x1c);
          *(int *)(&g_section_location_counters)[g_current_section_kind] =
               *(int *)(&g_section_location_counters)[g_current_section_kind] + 1;
          if ((g_current_request->show & 2) != 0) {
            list_object_code_byte(byte_value[0],0);
            put_text_at_column(3,&s_H_apos_00441e70,2);
            write_hex_byte(3,(int)(char)byte_value[0],2);
            if (item_count != 1) {
              put_char_at_column(3,',',2);
            }
          }
        }
        else {
          report_message_at_source_line(0,0,0x133c,(char *)0x0);
        }
      }
    }
    else if (size_code[0] == '\x01') {
      for (; 0 < item_count; item_count = item_count + -1) {
        nread = read_file_bytes(g_backend_record_input,(char *)word_value,2);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_backend_record_input,(char *)&ref_count,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (0x800 < g_section_data_bytes + 0x200) {
          flush_reloc_records();
        }
        if (ref_count == 0) {
          out_value = (uint)word_value[0];
          if (g_current_request->endian == '\0') {
            bytes_added = append_sized_value_to_data_record((uchar *)&out_value,1);
            *(int *)(&g_section_location_counters)[g_current_section_kind] =
                 *(int *)(&g_section_location_counters)[g_current_section_kind] + bytes_added;
          }
          else {
            byte_swap_value(&swapped_value,&out_value,1);
            bytes_added = append_sized_value_to_data_record((uchar *)&swapped_value,1);
            *(int *)(&g_section_location_counters)[g_current_section_kind] =
                 *(int *)(&g_section_location_counters)[g_current_section_kind] + bytes_added;
          }
          if ((g_current_request->show & 2) != 0) {
            list_object_code_value((int *)word_value,1,0);
            put_text_at_column(3,&s_H_apos_00441e74,2);
            write_hex_word(3,(int)word_value[0],2);
            if (item_count != 1) {
              put_char_at_column(3,',',2);
            }
          }
        }
        else {
          report_message_at_source_line(0,0,0x133c,(char *)0x0);
        }
      }
    }
    else if (size_code[0] == '\x02') {
      for (; 0 < item_count; item_count = item_count + -1) {
        nread = read_file_bytes(g_backend_record_input,(char *)&long_value,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_backend_record_input,(char *)&ref_count,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (0x800 < g_section_data_bytes + 0x200) {
          flush_reloc_records();
        }
        if (ref_count == 0) {
          if (g_current_request->endian == '\0') {
            bytes_added = append_sized_value_to_data_record((uchar *)&long_value,2);
            *(int *)(&g_section_location_counters)[g_current_section_kind] =
                 *(int *)(&g_section_location_counters)[g_current_section_kind] + bytes_added;
          }
          else {
            byte_swap_value(&swapped_value,&long_value,2);
            bytes_added = append_sized_value_to_data_record((uchar *)&swapped_value,2);
            *(int *)(&g_section_location_counters)[g_current_section_kind] =
                 *(int *)(&g_section_location_counters)[g_current_section_kind] + bytes_added;
          }
          if ((g_current_request->show & 2) != 0) {
            list_object_code_value((int *)&long_value,2,0);
            put_text_at_column(3,&s_H_apos_00441e78,2);
            write_hex_long(3,long_value,2);
            if (item_count != 1) {
              put_char_at_column(3,',',2);
            }
          }
        }
        else {
          ref_head.next = (label_ref *)0x0;
          ref_head.labno1 = 0;
          ref_head.labno2 = 0;
          read_label_ref_list((short)ref_count,&ref_head);
          out_value = emit_relocation_expression
                                (&ref_head,long_value,
                                 *(int *)(&g_section_location_counters)[g_current_section_kind],0x20
                                 ,0,1);
          if (g_current_request->endian == '\0') {
            bytes_added = append_sized_value_to_data_record((uchar *)&out_value,2);
            *(int *)(&g_section_location_counters)[g_current_section_kind] =
                 *(int *)(&g_section_location_counters)[g_current_section_kind] + bytes_added;
          }
          else {
            byte_swap_value(&swapped_value,&out_value,2);
            bytes_added = append_sized_value_to_data_record((uchar *)&swapped_value,2);
            *(int *)(&g_section_location_counters)[g_current_section_kind] =
                 *(int *)(&g_section_location_counters)[g_current_section_kind] + bytes_added;
          }
          if ((g_current_request->show & 2) != 0) {
            list_object_code_value((int *)&long_value,2,1);
            offset_written = 0;
            has_offset = long_value != 0;
            if (has_offset) {
              put_text_at_column(3,&s_H_apos_00441e7c,2);
              write_hex_long(3,long_value,2);
            }
            offset_written = (ushort)has_offset;
            print_label_ref_expression_to_listing(&ref_head,offset_written);
            if (item_count != 1) {
              put_char_at_column(3,',',2);
            }
          }
          cur_ref = ref_head.next;
          while (cur_ref != (label_ref *)0x0) {
            next_ref = cur_ref->next;
            pool_free(cur_ref,8);
            cur_ref = next_ref;
          }
        }
      }
    }
    if ((g_current_request->show & 2) != 0) {
      flush_output_line(3);
    }
  }
  else {
    put_text_at_column(2,s__DATA_00441de4,1);
    write_size_suffix(2,(short)size_code[0],1);
    if (size_code[0] == '\0') {
      for (; 0 < item_count; item_count = item_count + -1) {
        nread = read_file_bytes(g_backend_record_input,(char *)byte_value,1);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_backend_record_input,(char *)&ref_count,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (ref_count == 0) {
          put_text_at_column(2,&s_H_apos_00441e80,2);
          write_hex_byte(2,(int)(char)byte_value[0],2);
        }
        else {
          offset_written = 0;
          has_offset = byte_value[0] != '\0';
          if (has_offset) {
            put_text_at_column(2,&s_H_apos_00441e84,2);
            write_hex_byte(2,(int)(char)byte_value[0],2);
          }
          offset_written = (ushort)has_offset;
          print_label_sum_from_backend_stream(2,(short)ref_count,offset_written);
        }
        if (item_count != 1) {
          put_char_at_column(2,',',2);
        }
      }
    }
    else if (size_code[0] == '\x01') {
      for (; 0 < item_count; item_count = item_count + -1) {
        nread = read_file_bytes(g_backend_record_input,(char *)word_value,2);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_backend_record_input,(char *)&ref_count,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (ref_count == 0) {
          put_text_at_column(2,&s_H_apos_00441e88,2);
          write_hex_word(2,(int)word_value[0],2);
        }
        else {
          offset_written = 0;
          has_offset = word_value[0] != 0;
          if (has_offset) {
            put_text_at_column(2,&s_H_apos_00441e8c,2);
            write_hex_word(2,(int)word_value[0],2);
          }
          offset_written = (ushort)has_offset;
          print_label_sum_from_backend_stream(2,(short)ref_count,offset_written);
        }
        if (item_count != 1) {
          put_char_at_column(2,',',2);
        }
      }
    }
    else if (size_code[0] == '\x02') {
      for (; 0 < item_count; item_count = item_count + -1) {
        nread = read_file_bytes(g_backend_record_input,(char *)&long_value,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_backend_record_input,(char *)&ref_count,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (ref_count == 0) {
          put_text_at_column(2,&s_H_apos_00441e90,2);
          write_hex_long(2,long_value,2);
        }
        else {
          offset_written = 0;
          has_offset = long_value != 0;
          if (has_offset) {
            put_text_at_column(2,&s_H_apos_00441e94,2);
            write_hex_long(2,long_value,2);
          }
          offset_written = (ushort)has_offset;
          print_label_sum_from_backend_stream(2,(short)ref_count,offset_written);
        }
        if (item_count != 1) {
          put_char_at_column(2,',',2);
        }
      }
    }
    flush_output_line(2);
  }
  return;
#undef long_value
#undef size_code
#undef word_value
#undef ref_count
#undef offset_written
#undef item_count
#undef next_ref
#undef byte_value
#undef cur_ref
#undef out_value
#undef swapped_value
#undef ref_head
}
