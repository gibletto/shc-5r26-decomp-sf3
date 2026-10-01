#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 0042836b
// name : emit_literal_pool
// size : 690
// sig  : void emit_literal_pool(void)


int __cdecl emit_literal_pool(void)

{
  unsigned char _frec_14[20];
#define out_channel (*(short *)(_frec_14 + 0))
#define lit_entry (*(literal_entry * *)(_frec_14 + 4))
#define pad_bytes (*(int *)(_frec_14 + 8))
#define pool_label_sym (*(symbol * *)(_frec_14 + 12))
  uint sign_mask;
  
  out_channel = 0;
  pool_label_sym = find_symbol_by_id(g_literal_pool_label);
  if ((g_current_section_kind == 0) &&
     (*(int *)g_section_location_counters != pool_label_sym->value)) {
    emit_alignment_fill(0x20,pool_label_sym->value - *(int *)g_section_location_counters);
  }
  if ((g_current_request->code != 1) || ((g_current_request->show & 2) != 0)) {
    if ((g_current_request->show & 2) == 0) {
      out_channel = 2;
    }
    else {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
      out_channel = 3;
    }
    write_label_name(out_channel,g_literal_pool_label,0);
    put_text_at_column(out_channel,&s_sp_00442088,3);
    flush_output_line(out_channel);
  }
  for (lit_entry = g_word_literal_table.head; lit_entry != (literal_entry *)0x0;
      lit_entry = lit_entry->next) {
    emit_literal_pool_entry(lit_entry->value,lit_entry->labels,1);
  }
  if ((g_long_literal_table.head != (literal_entry *)0x0) &&
     (sign_mask = g_location_counter >> 0x1f,
     ((g_location_counter ^ sign_mask) - sign_mask & 3 ^ sign_mask) != sign_mask)) {
    if (g_current_request->code == 1) {
      if ((g_current_request->show & 2) != 0) {
        format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
      }
      g_object_record_break = 1;
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + 2;
      if ((g_current_request->show & 2) != 0) {
        pad_bytes = 2;
        list_object_code_value(&pad_bytes,2,0);
      }
      *(int *)(&g_section_object_offsets + g_current_section_kind * 4) =
           *(int *)(&g_section_object_offsets + g_current_section_kind * 4) + 2;
    }
    else {
      *(int *)(&g_section_location_counters)[g_current_section_kind] =
           *(int *)(&g_section_location_counters)[g_current_section_kind] + 2;
    }
    if (out_channel != 0) {
      put_text_at_column(out_channel,&s_dot_RES_0044208c,1);
      write_size_suffix(out_channel,1,1);
      write_decimal(out_channel,1,2);
      flush_output_line(out_channel);
    }
  }
  for (lit_entry = g_long_literal_table.head; lit_entry != (literal_entry *)0x0;
      lit_entry = lit_entry->next) {
    emit_literal_pool_entry(lit_entry->value,lit_entry->labels,2);
  }
  clear_pool_literal_table(&g_word_literal_table);
  clear_pool_literal_table(&g_long_literal_table);
  return;
#undef out_channel
#undef lit_entry
#undef pad_bytes
#undef pool_label_sym
}
