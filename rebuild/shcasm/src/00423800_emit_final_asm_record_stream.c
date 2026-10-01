#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x10b2c))
#undef g_inline_asm_input
#define g_inline_asm_input (*(FILE * *)(g_sd + 0xf8f0))
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))
#undef g_source_listing_input
#define g_source_listing_input (*(FILE * *)(g_sd + 0xe744))


// entry: 00423800
// name : emit_final_asm_record_stream
// size : 1869
// sig  : uint emit_final_asm_record_stream(void)


uint __cdecl emit_final_asm_record_stream(void)

{
  unsigned char _frec_20[32];
#define i (*(int *)(_frec_20 + 0))
#define cur_rec (*(psd *)(_frec_20 + 4))
  int status;
  uint uVar1;
  uint extraout_EAX;
  
  g_superscalar_draining = 0;
  g_superscalar_records_read = 0;
  g_pipeline_end_of_stream = 0;
  g_superscalar_stream_ended = 0;
  stock_memcpy(&cur_rec,&g_zero_psd,0x18);
  while (status = read_next_backend_record(&cur_rec,0), status != 0) {
    if ((g_current_request->code == 1) && (0x800 < g_section_data_bytes + 0x200)) {
      flush_reloc_records();
    }
    if ((g_current_request->asm_debug == '\x01') && (g_current_section_kind == 0)) {
      if ((((cur_rec.op == OP_BRA) ||
           (((((cur_rec.op == OP_BSR || (cur_rec.op == OP_BT_S)) || (cur_rec.op == OP_BF_S)) ||
             ((cur_rec.op == OP_BSRF || (cur_rec.op == OP_BRAF)))) || (cur_rec.op == OP_JMP)))) ||
          (((cur_rec.op == OP_JSR || (cur_rec.op == OP_RTS)) || (cur_rec.op == OP_RTE)))) &&
         (g_delay_slot_record.op != OP_NOP)) {
        emit_line_directive_for_record(&g_delay_slot_record);
      }
      emit_line_directive_for_record(&cur_rec);
    }
    if ((((g_current_request->show & 2) != 0) && ((g_current_request->show & 0x11) != 0)) &&
       (g_source_listing_at_end == '\0')) {
      copy_source_lines_to_listing(cur_rec.op,cur_rec.filno,cur_rec.linno);
    }
    switch(cur_rec.op) {
    case OP_DC:
      emit_dc_record();
      break;
    case OP_DZ:
      emit_dz_record();
      break;
    case OP_DS:
      emit_reserve_record();
      break;
    case OP_DSTR:
      emit_string_data_record();
      break;
    case OP_PRGRAM:
    case OP_CONST:
    case OP_DATA:
    case OP_BSS:
      if ((((g_current_request->show & 2) != 0) && ((g_current_request->show & 0x11) != 0)) &&
         ((g_source_listing_at_end == '\0' && (cur_rec.op != OP_PRGRAM)))) {
        copy_source_lines_to_listing('\0',0x7fff,0xffff);
      }
      switch_section(&cur_rec);
      g_inline_asm_needs_label = 0;
      break;
    case OP_B_ASM:
      emit_inline_asm_block(&cur_rec);
      break;
    case OP_C_JMP:
      expand_switch_jump(&cur_rec);
      break;
    default:
      assemble_instruction(&cur_rec);
      break;
    case OP_BBGN:
      if (g_current_request->debug != 0) {
        open_debug_scope_range(0);
      }
      break;
    case OP_BEND:
      if (g_current_request->debug != 0) {
        close_debug_scope_range(0,0);
      }
      break;
    case OP_LABEL:
    case OP_CLABEL:
    case OP_DLABEL:
    case OP_FLABEL:
      emit_label_record(&cur_rec);
      g_inline_asm_needs_label = 0;
      break;
    case OP_LINE:
      emit_line_comment(&cur_rec);
      break;
    case OP_SWBGN:
    case OP_SWEND: ;
    }
    if ((g_current_request->debug != 0) && (g_current_section_kind == 0)) {
      update_debug_info_for_record(&cur_rec);
    }
    if ((((((cur_rec.op == OP_BRA) || (cur_rec.op == OP_BSR)) || (cur_rec.op == OP_BT_S)) ||
         (((cur_rec.op == OP_BF_S || (cur_rec.op == OP_BSRF)) ||
          ((cur_rec.op == OP_BRAF || ((cur_rec.op == OP_JMP || (cur_rec.op == OP_JSR)))))))) ||
        (cur_rec.op == OP_RTS)) || (cur_rec.op == OP_RTE)) {
      if (g_delay_slot_record.op == OP_NOP) {
        g_delay_slot_record.flg = 'B';
        g_delay_slot_record.expno = cur_rec.expno;
        g_delay_slot_record.filno = cur_rec.filno;
        g_delay_slot_record.linno = cur_rec.linno;
      }
      if ((((g_current_request->show & 2) != 0) && ((g_current_request->show & 0x11) != 0)) &&
         (g_source_listing_at_end == '\0')) {
        copy_source_lines_to_listing
                  (g_delay_slot_record.op,g_delay_slot_record.filno,g_delay_slot_record.linno);
      }
      assemble_instruction(&g_delay_slot_record);
      if (g_current_request->debug != 0) {
        update_debug_info_for_record(&g_delay_slot_record);
      }
      if (g_delay_slot_record.ea1 != (ea *)0x0) {
        free_ea_operand(g_delay_slot_record.ea1);
      }
      if (g_delay_slot_record.ea2 != (ea *)0x0) {
        free_ea_operand(g_delay_slot_record.ea2);
      }
      stock_memcpy(&g_delay_slot_record,&g_zero_psd,0x18);
      if (g_next_delay_slot_record.op != OP_DUMMY_00) {
        stock_memcpy(&g_delay_slot_record,&g_next_delay_slot_record,0x18);
        stock_memcpy(&g_next_delay_slot_record,&g_zero_psd,0x18);
      }
    }
    if (((cur_rec.flg & 0x10) != 0) &&
       ((g_word_literal_table.count != 0 || (g_long_literal_table.count != 0)))) {
      emit_literal_pool();
    }
    if (OP_SWEND < cur_rec.op) {
      if (cur_rec.ea1 != (ea *)0x0) {
        free_ea_operand(cur_rec.ea1);
      }
      if (cur_rec.ea2 != (ea *)0x0) {
        free_ea_operand(cur_rec.ea2);
      }
    }
    stock_memcpy(&cur_rec,&g_zero_psd,0x18);
  }
  if ((((g_current_request->show & 2) != 0) && ((g_current_request->show & 0x11) != 0)) &&
     (g_source_listing_at_end == '\0')) {
    copy_source_lines_to_listing('\0',0x7fff,0xffff);
  }
  if (g_extra_section_needed == '\x01') {
    cur_rec.op = OP_DATA;
    cur_rec.filno = 2;
    switch_section(&cur_rec);
  }
  if (g_current_section != (request_section *)0x0) {
    for (i = 0; i < 4; i = i + 1) {
      g_current_section->layout->section_number[i] = g_section_numbers[i];
      g_current_section->layout->location[i] = *(int *)(&g_section_location_counters)[i];
      g_current_section->layout->object_offset[i] = *(int *)(&g_section_object_offsets + i * 4);
    }
  }
  if (g_current_request->code != 1) {
    put_text_at_column(2,&s_dot_END_00441e60,1);
    flush_output_line(2);
  }
  status = _fclose(g_backend_record_input);
  if (status == -1) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  status = _fclose(g_lit_input);
  if (status == -1) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  if ((g_current_request->code == 2) && (status = _fclose(g_inline_asm_input), status == -1)) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  uVar1 = (uint)(short)g_current_request->show;
  if ((((uVar1 & 2) != 0) && (uVar1 = (uint)(short)g_current_request->show, (uVar1 & 0x11) != 0)) &&
     (uVar1 = _fclose(g_source_listing_input), uVar1 == 0xffffffff)) {
    (extraout_EAX = (uint)report_message_at_source_line(0,0,0xce5,(char *)0x0));
    uVar1 = extraout_EAX;
  }
  return uVar1;
#undef i
#undef cur_rec
}
