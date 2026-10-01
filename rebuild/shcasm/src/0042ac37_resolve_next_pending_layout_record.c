#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_layout_pending_records
#define g_layout_pending_records (*(layout_record * *)(g_sd + 0xcca8))
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))
#undef g_layout_symbol_pass0
#define g_layout_symbol_pass0 (*(symbol * *)(g_sd + 0xccf8))
#undef g_layout_symbol_pass1
#define g_layout_symbol_pass1 (*(symbol * *)(g_sd + 0xccac))
#undef g_layout_symbol_pending_records
#define g_layout_symbol_pending_records (*(layout_record * *)(g_sd + 0x13018))


// entry: 0042ac37
// name : resolve_next_pending_layout_record
// size : 697
// sig  : int resolve_next_pending_layout_record(void)


int __cdecl resolve_next_pending_layout_record(void)

{
  bool had_records;
  uint progressed;
  symbol *prev_sym;
  
  if (g_layout_pending_records == (layout_record *)0x0) {
    if (g_layout_symbol_pending_records == (layout_record *)0x0) {
      if (((g_layout_symbol_pass1 <= g_layout_symbol_pass0) &&
          (g_layout_symbol_pass1->section_id != 0)) &&
         (g_layout_symbol_pass1->section_id != g_layout_section_pass1->id)) {
        g_layout_section_pass1->layout->shrink_pass1 = g_layout_shrink_pass1;
        g_layout_section_pass1 =
             find_section_by_id(g_current_request,g_layout_symbol_pass1->section_id);
        g_layout_shrink_pass1 = g_layout_section_pass1->layout->shrink_pass1;
      }
      while ((g_layout_symbol_pass1->layout_records == (layout_record *)0x0 &&
             (g_layout_symbol_pass1 <= g_layout_symbol_pass0))) {
        g_layout_symbol_pass1->value = g_layout_symbol_pass1->value - g_layout_shrink_pass1;
        prev_sym = g_layout_symbol_pass1;
        g_layout_symbol_pass1 = g_layout_symbol_pass1 + 1;
        if ((g_layout_symbol_pass1 <= g_layout_symbol_pass0) &&
           (prev_sym[1].section_id != g_layout_section_pass1->id)) {
          g_layout_section_pass1->layout->shrink_pass1 = g_layout_shrink_pass1;
          g_layout_section_pass1 =
               find_section_by_id(g_current_request,g_layout_symbol_pass1->section_id);
          g_layout_shrink_pass1 = g_layout_section_pass1->layout->shrink_pass1;
        }
        g_layout_symbol_labno_pass1 = g_layout_symbol_pass1->number;
        if (g_layout_symbol_pass1->kind == '\x01') {
          g_function_label_pass1 = g_layout_symbol_labno_pass1;
        }
      }
      if (g_layout_symbol_pass0 < g_layout_symbol_pass1) {
        g_layout_symbol_pending_records = (layout_record *)0x0;
      }
      else {
        g_layout_symbol_pass1->value = g_layout_symbol_pass1->value - g_layout_shrink_pass1;
        g_layout_symbol_pending_records = g_layout_symbol_pass1->layout_records;
      }
    }
    had_records = g_layout_symbol_pending_records != (layout_record *)0x0;
    if (had_records) {
      g_layout_symbol_pending_records = resolve_layout_record(g_layout_symbol_pending_records);
    }
    prev_sym = g_layout_symbol_pass1;
    progressed = (uint)had_records;
    if (g_layout_symbol_pending_records == (layout_record *)0x0) {
      g_layout_symbol_pass1 = g_layout_symbol_pass1 + 1;
      if ((g_layout_symbol_pass1 <= g_layout_symbol_pass0) &&
         (prev_sym[1].section_id != g_layout_section_pass1->id)) {
        g_layout_section_pass1->layout->shrink_pass1 = g_layout_shrink_pass1;
        g_layout_section_pass1 =
             find_section_by_id(g_current_request,g_layout_symbol_pass1->section_id);
        g_layout_shrink_pass1 = g_layout_section_pass1->layout->shrink_pass1;
      }
      g_layout_symbol_labno_pass1 = g_layout_symbol_pass1->number;
      if (g_layout_symbol_pass1->kind == '\x01') {
        g_function_label_pass1 = g_layout_symbol_labno_pass1;
      }
    }
  }
  else {
    g_layout_pending_records = resolve_layout_record(g_layout_pending_records);
    progressed = 1;
  }
  return progressed;
}



