#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 00417bfa
// name : emit_switch_table_entry
// size : 1071
// sig  : void __cdecl emit_switch_table_entry(short table_label,short base_label,int short_entries)


int __cdecl emit_switch_table_entry(short table_label,short base_label,int short_entries)

{
  unsigned char _frec_28[40];
#define zero_addend (*(int *)(_frec_28 + 0))
#define entry_size (*(char *)(_frec_28 + 4))
#define short_value (*(undefined2 (*)[2])(_frec_28 + 8))
#define target_label (*(short (*)[2])(_frec_28 + 12))
#define entry_value (*(uint *)(_frec_28 + 16))
#define swapped_value (*(uint *)(_frec_28 + 20))
#define target_ref (*(label_ref *)(_frec_28 + 24))
#define local_8 (*(char (*)[4])(_frec_28 + 32))
  uint read_status;
  int iVar1;
  symbol *label_sym;
  
  zero_addend = 0;
  if (short_entries == 0) {
    entry_size = '\x02';
  }
  else {
    entry_size = '\x01';
  }
  read_status = read_file_bytes(g_backend_record_input,local_8,1);
  if (read_status == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  read_status = read_file_bytes(g_backend_record_input,(char *)target_label,2);
  if (read_status == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  if (g_current_request->code == 1) {
    if ((g_current_request->show & 2) != 0) {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
      put_text_at_column(3,s__DATA_00441958,1);
      write_size_suffix(3,(short)entry_size,1);
    }
    if (0x800 < g_section_data_bytes + 0x200) {
      flush_reloc_records();
    }
    target_ref.next = (label_ref *)0x0;
    target_ref.labno1 = target_label[0];
    if ((short_entries == 0) && (g_current_request->cpu == 0)) {
      target_ref.labno2 = 0;
      entry_value = emit_relocation_expression
                              (&target_ref,zero_addend,
                               *(int *)(&g_section_location_counters)[g_current_section_kind],0x20,0
                               ,1);
      if (g_current_request->endian == '\0') {
        iVar1 = append_sized_value_to_data_record((uchar *)&entry_value,2);
        *(int *)(&g_section_location_counters)[g_current_section_kind] =
             *(int *)(&g_section_location_counters)[g_current_section_kind] + iVar1;
      }
      else {
        byte_swap_value(&swapped_value,&entry_value,2);
        iVar1 = append_sized_value_to_data_record((uchar *)&swapped_value,2);
        *(int *)(&g_section_location_counters)[g_current_section_kind] =
             *(int *)(&g_section_location_counters)[g_current_section_kind] + iVar1;
      }
    }
    else {
      if (g_current_request->cpu == 0) {
        target_ref.labno2 = -table_label;
        label_sym = find_symbol_by_id(target_label[0]);
        iVar1 = label_sym->value;
        label_sym = find_symbol_by_id(table_label);
        entry_value = iVar1 - label_sym->value;
      }
      else {
        target_ref.labno2 = -base_label;
        label_sym = find_symbol_by_id(target_label[0]);
        iVar1 = label_sym->value;
        label_sym = find_symbol_by_id(base_label);
        entry_value = iVar1 - label_sym->value;
      }
      short_value[0] = (undefined2)entry_value;
      if (g_current_request->endian == '\0') {
        iVar1 = append_sized_value_to_data_record((uchar *)&entry_value,(short_entries == 0) + 1);
        *(int *)(&g_section_location_counters)[g_current_section_kind] =
             *(int *)(&g_section_location_counters)[g_current_section_kind] + iVar1;
      }
      else {
        byte_swap_value(&swapped_value,&entry_value,(short_entries == 0) + 1);
        iVar1 = append_sized_value_to_data_record((uchar *)&swapped_value,(short_entries == 0) + 1);
        *(int *)(&g_section_location_counters)[g_current_section_kind] =
             *(int *)(&g_section_location_counters)[g_current_section_kind] + iVar1;
      }
    }
    if ((g_current_request->show & 2) != 0) {
      if ((short_entries == 0) && (g_current_request->cpu == 0)) {
        list_object_code_value(&zero_addend,2,1);
      }
      else if (short_entries == 0) {
        list_object_code_value((int *)&entry_value,2,1);
      }
      else {
        list_object_code_value((int *)short_value,1,0);
      }
      print_label_ref_expression_to_listing(&target_ref,0);
      flush_output_line(3);
    }
  }
  else {
    put_text_at_column(2,s__DATA_00441958,1);
    write_size_suffix(2,(short)entry_size,1);
    write_label_name(2,target_label[0],2);
    if ((short_entries == 1) || (g_current_request->cpu != 0)) {
      put_char_at_column(2,'-',2);
      if (g_current_request->cpu == 0) {
        write_label_name(2,table_label,2);
      }
      else {
        write_label_name(2,base_label,2);
      }
    }
    flush_output_line(2);
    if (short_entries == 0) {
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + 4;
    }
    else {
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + 2;
    }
  }
  return;
#undef zero_addend
#undef entry_size
#undef short_value
#undef target_label
#undef entry_value
#undef swapped_value
#undef target_ref
#undef local_8
}
