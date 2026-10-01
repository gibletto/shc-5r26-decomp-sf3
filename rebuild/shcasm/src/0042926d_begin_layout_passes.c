#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_aux_index
#define g_current_aux_index (*(int *)(g_sd + 0xf8ec))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_layout_pending_records
#define g_layout_pending_records (*(layout_record * *)(g_sd + 0xcca8))
#undef g_layout_section_pass0
#define g_layout_section_pass0 (*(request_section * *)(g_sd + 0xcc9c))
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))
#undef g_layout_symbol_pass0
#define g_layout_symbol_pass0 (*(symbol * *)(g_sd + 0xccf8))
#undef g_layout_symbol_pass1
#define g_layout_symbol_pass1 (*(symbol * *)(g_sd + 0xccac))
#undef g_layout_symbol_pending_records
#define g_layout_symbol_pending_records (*(layout_record * *)(g_sd + 0x13018))
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))
#undef g_ofb_input
#define g_ofb_input (*(FILE * *)(g_sd + 0xd12c))
#undef g_symbol_base
#define g_symbol_base (*(symbol * *)(g_sd + 0x1314c))


// entry: 0042926d
// name : begin_layout_passes
// size : 905
// sig  : void begin_layout_passes(void)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl begin_layout_passes(void)

{
  unsigned char _frec_10[20];
#define tail_item (*(layout_record * *)(_frec_10 + 0))
#define tag_byte (*(psd_op (*)[4])(_frec_10 + 4))
#define input_path (*(char * *)(_frec_10 + 8))
  uint nread;
  layout_record *item;
  symbol *label_sym;
  
  g_ofb_at_end = 0;
  for (g_layout_symbol_pass0 = g_symbol_base; 5 < (g_layout_symbol_pass0->kind & 0x1f);
      g_layout_symbol_pass0 = g_layout_symbol_pass0 + 1) {
  }
  g_layout_symbol_pass1 = g_layout_symbol_pass0;
  g_layout_section_pass0 = find_section_by_id(g_current_request,1);
  g_layout_shrink_pass0 = g_layout_section_pass0->layout->shrink_pass0;
  g_layout_section_pass1 = find_section_by_id(g_current_request,1);
  g_layout_shrink_pass1 = g_layout_section_pass1->layout->shrink_pass1;
  g_layout_symbol_labno_pass1 = g_layout_symbol_pass1->number;
  if (g_layout_symbol_pass1->kind == '\x01') {
    g_function_label_pass1 = g_layout_symbol_labno_pass1;
  }
  g_layout_symbol_pending_records = (layout_record *)0x0;
  if (g_current_request->optimize == 0) {
    input_path = g_current_request->ofa_path;
  }
  else {
    input_path = g_current_request->ofb_path;
  }
  g_ofb_input = stock_fopen(input_path,&s_rb_004420b4);
  item = g_layout_pending_records;
  if (g_ofb_input == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
    item = g_layout_pending_records;
  }
  do {
    g_layout_pending_records = item;
    nread = read_file_bytes(g_ofb_input,(char *)tag_byte,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
LAB_004294fa:
      if (g_ofb_at_end == 0) {
        nread = read_file_bytes(g_ofb_input,(char *)&g_ofb_current_label,2);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        label_sym = find_symbol_by_id(g_ofb_current_label);
        if (label_sym->kind == '\x01') {
          g_function_label_pass0 = g_ofb_current_label;
          label_sym = find_symbol_by_id(g_ofb_current_label);
          _g_current_aux_index = (int)label_sym->aux_index;
        }
      }
      allocate_spool_buffer();
      g_lit_input = stock_fopen(g_current_request->lit_path,&s_rb_004420b8);
      if (g_lit_input == (FILE *)0x0) {
        report_message_at_source_line(0,0,0xce4,(char *)0x0);
      }
      nread = read_file_bytes(g_lit_input,(char *)tag_byte,1);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      return;
    }
    if (nread == 0) {
      g_ofb_at_end = 1;
      goto LAB_004294fa;
    }
    if (tag_byte[0] != OP_B_ASM) goto LAB_004294fa;
    item = alloc_layout_record();
    item->op = tag_byte[0];
    nread = read_file_bytes(g_ofb_input,(char *)&item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    relax_inline_asm_record(item,0);
    if (g_layout_pending_records != (layout_record *)0x0) {
      for (tail_item = g_layout_pending_records; tail_item->next != (layout_record *)0x0;
          tail_item = tail_item->next) {
      }
      tail_item->next = item;
      item = g_layout_pending_records;
    }
  } while( true );
#undef tail_item
#undef tag_byte
#undef input_path
}
