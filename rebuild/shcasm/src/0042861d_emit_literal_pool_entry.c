#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 0042861d
// name : emit_literal_pool_entry
// size : 1148
// sig  : void __cdecl emit_literal_pool_entry(uint value,label_ref *refs,int size_code)


int __cdecl emit_literal_pool_entry(uint value,label_ref *refs,int size_code)

{
  unsigned char _frec_14[20];
#define has_offset (*(ushort *)(_frec_14 + 0))
#define reloc_value (*(uint *)(_frec_14 + 4))
#define swapped_value (*(uint *)(_frec_14 + 8))
#define cur_ref (*(label_ref * *)(_frec_14 + 12))
  bool need_plus;
  
  if (g_current_request->code == 1) {
    if ((g_current_request->show & 2) != 0) {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
      put_text_at_column(3,s__DATA_00442094,1);
      write_size_suffix(3,(short)size_code,1);
    }
    if (0x800 < g_section_data_bytes + 0x200) {
      flush_reloc_records();
    }
    if ((size_code < 1) || (2 < size_code)) {
      report_message_at_source_line(0,0,0x134d,(char *)0x0);
    }
    else {
      if (refs == (label_ref *)0x0) {
        if (g_current_request->endian == '\0') {
          append_sized_value_to_data_record((uchar *)&value,(short)size_code);
        }
        else {
          byte_swap_value(&swapped_value,&value,size_code);
          append_sized_value_to_data_record((uchar *)&swapped_value,(short)size_code);
        }
        if ((g_current_request->show & 2) != 0) {
          list_object_code_value((int *)&value,(short)size_code,0);
          put_text_at_column(3,&s_H_apos_0044209c,2);
          if (size_code == 2) {
            write_hex_long(3,value,2);
          }
          else {
            write_hex_word(3,value,2);
          }
        }
      }
      else {
        reloc_value = emit_relocation_expression
                                (refs,value,
                                 *(int *)(&g_section_location_counters)[g_current_section_kind],
                                 (-(uint)(size_code == 2) & 0x10) + 0x10,0,1);
        if (g_current_request->endian == '\0') {
          append_sized_value_to_data_record((uchar *)&reloc_value,(short)size_code);
        }
        else {
          byte_swap_value(&swapped_value,&reloc_value,size_code);
          append_sized_value_to_data_record((uchar *)&swapped_value,(short)size_code);
        }
        if ((g_current_request->show & 2) != 0) {
          reloc_value = value;
          list_object_code_value((int *)&reloc_value,2,1);
          need_plus = value != 0;
          if (need_plus) {
            put_text_at_column(3,&s_H_apos_004420a0,2);
            write_hex_long(3,value,2);
          }
          has_offset = (ushort)need_plus;
          print_label_ref_expression_to_listing(refs,has_offset);
        }
      }
      if (size_code == 2) {
        g_location_counter = g_location_counter + 4;
      }
      else {
        g_location_counter = g_location_counter + 2;
      }
    }
    if ((g_current_request->show & 2) != 0) {
      flush_output_line(3);
    }
  }
  else {
    put_text_at_column(2,s__DATA_004420a4,1);
    write_size_suffix(2,(short)size_code,1);
    if ((size_code < 1) || (2 < size_code)) {
      report_message_at_source_line(0,0,0x134d,(char *)0x0);
    }
    else {
      if (refs == (label_ref *)0x0) {
        put_text_at_column(2,&s_H_apos_004420ac,2);
        if (size_code == 2) {
          write_hex_long(2,value,2);
        }
        else {
          write_hex_word(2,value,2);
        }
      }
      else {
        need_plus = value != 0;
        if (need_plus) {
          put_text_at_column(2,&s_H_apos_004420b0,2);
          write_hex_long(2,value,2);
        }
        for (cur_ref = refs; cur_ref != (label_ref *)0x0; cur_ref = cur_ref->next) {
          if ((need_plus) && (0 < cur_ref->labno1)) {
            put_char_at_column(2,'+',2);
          }
          write_label_name(2,cur_ref->labno1,2);
          if (cur_ref->labno2 != 0) {
            if (0 < cur_ref->labno2) {
              put_char_at_column(2,'+',2);
            }
            write_label_name(2,cur_ref->labno2,2);
          }
          need_plus = true;
        }
      }
      if (size_code == 2) {
        g_location_counter = g_location_counter + 4;
      }
      else {
        g_location_counter = g_location_counter + 2;
      }
    }
    flush_output_line(2);
  }
  return;
#undef has_offset
#undef reloc_value
#undef swapped_value
#undef cur_ref
}
