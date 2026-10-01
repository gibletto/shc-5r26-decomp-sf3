#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_inline_asm_input
#define g_inline_asm_input (*(FILE * *)(g_sd + 0xf8f0))
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))
#undef g_source_listing_input
#define g_source_listing_input (*(FILE * *)(g_sd + 0xe744))
#undef g_symbol_base
#define g_symbol_base (*(symbol * *)(g_sd + 0x1314c))


// entry: 00411ea0
// name : run_assembler_passes
// size : 2751
// sig  : void run_assembler_passes(void)


int __cdecl run_assembler_passes(void)

{
  unsigned char _frec_24[36];
#define first_op (*(uchar (*)[4])(_frec_24 + 0))
#define bytes_read (*(uint *)(_frec_24 + 4))
#define cur_section (*(request_section * *)(_frec_24 + 8))
#define i (*(ushort *)(_frec_24 + 12))
#define empty_input (*(short *)(_frec_24 + 16))
#define sym_kind (*(short *)(_frec_24 + 20))
#define lit_header (*(char (*)[4])(_frec_24 + 24))
#define backend_path (*(char * *)(_frec_24 + 28))
  uint read_status;
  request_section *sym_section;
  
  g_next_export_index = 0;
  g_next_import_index = 0;
  empty_input = 0;
  g_new_symbol_count = 0;
  for (i = 0; i < 0x20; i = i + 1) {
    (&g_runtime_routine_imported)[(short)i] = 0;
  }
  for (i = 0; i < 0x100; i = i + 1) {
    *(undefined4 *)(&g_runtime_routine_import_index + (short)i * 4) = 0;
  }
  if (g_current_request->optimize == 0) {
    backend_path = g_current_request->sua_path;
  }
  else {
    backend_path = g_current_request->sub_path;
  }
  g_backend_record_input = stock_fopen(backend_path,&s_rb_00440d40);
  if (g_backend_record_input == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  g_backend_continuation_opened = 0;
  read_status = read_file_bytes(g_backend_record_input,(char *)first_op,1);
  if (read_status == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  g_lit_input = stock_fopen(g_current_request->lit_path,&s_rb_00440d44);
  if (g_lit_input == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  read_status = read_file_bytes(g_lit_input,lit_header,1);
  if (read_status == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  if ((g_current_request->show & 2) != 0) {
    open_output_stream(3);
  }
  if (g_current_request->code == 1) {
    open_output_stream(1);
  }
  else if (g_current_request->code == 2) {
    open_output_stream(2);
    g_inline_asm_input = stock_fopen(g_current_request->asl_path,&s_rb_00440d48);
    if (g_inline_asm_input == (FILE *)0x0) {
      report_message_at_source_line(0,0,0xce4,(char *)0x0);
    }
  }
  g_source_listing_at_end = '\0';
  if (((g_current_request->show & 2) != 0) && ((g_current_request->show & 0x11) != 0)) {
    g_source_listing_input = stock_fopen(g_current_request->obl_path,&s_rb_00440d4c);
    if (g_source_listing_input == (FILE *)0x0) {
      report_message_at_source_line(0,0,0xce4,(char *)0x0);
    }
    bytes_read = read_file_bytes(g_source_listing_input,(char *)&g_source_listing_file,2);
    if (bytes_read == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    else if (bytes_read == 0) {
      g_source_listing_at_end = '\x01';
    }
    else {
      read_status = read_file_bytes(g_source_listing_input,(char *)&g_source_listing_line,4);
      if (read_status == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
    }
  }
  g_object_record_tag = 0;
  if (g_current_request->debug != 0) {
    init_debug_info_state();
  }
  emit_object_record_kind_table();
  emit_object_module_header_record();
  g_section_count = 0;
  if (g_program_size == 0) {
    if (first_op[0] != '\f') {
      empty_input = 1;
    }
    if ((g_current_request->show & 2) != 0) {
      emit_listing_page_header();
    }
  }
  if (g_program_size == 0) {
    g_current_request->sections->layout->section_number[0] = g_section_count;
    g_section_count = g_section_count + 1;
  }
  else {
    for (i = 0; (short)i < 4; i = i + 1) {
      for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
          cur_section = cur_section->next) {
        if (cur_section->size[(short)i] != 0) {
          cur_section->layout->section_number[(short)i] = g_section_count;
          g_section_count = g_section_count + 1;
        }
      }
    }
  }
  g_extra_section_needed = '\0';
  i = 0;
  do {
    if (g_current_request->label_count <= (int)(short)i) {
LAB_00412385:
      if (g_extra_section_needed == '\x01') {
        g_current_request->sections->next->layout->section_number[2] = g_section_count;
        g_section_count = g_section_count + 1;
      }
      g_current_request->sections->next->layout->section_number[3] =
           g_current_request->sections->next->layout->section_number[2];
      g_current_request->sections->next->layout->section_number[1] =
           g_current_request->sections->next->layout->section_number[3];
      g_current_request->sections->next->next->layout->section_number[3] =
           g_current_request->sections->next->next->layout->section_number[2];
      g_current_request->sections->next->next->layout->section_number[1] =
           g_current_request->sections->next->next->layout->section_number[3];
      count_import_and_export_symbols();
      emit_object_unit_record();
      if (g_program_size == 0) {
        emit_section_definition_record(0,g_current_request->sections);
      }
      else {
        for (i = 0; (short)i < 4; i = i + 1) {
          for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
              cur_section = cur_section->next) {
            if (cur_section->size[(short)i] != 0) {
              emit_section_definition_record(i,cur_section);
            }
          }
        }
      }
      if (g_extra_section_needed == '\x01') {
        emit_section_definition_record(2,g_current_request->sections->next);
      }
      for (i = 0; (int)(short)i < g_current_request->label_count; i = i + 1) {
        sym_kind = (short)(char)g_symbol_base[(short)i].kind;
        if (((sym_kind == 10) || (sym_kind == 0xb)) && ((g_symbol_base[(short)i].flags & 0x40) == 0)
           ) {
          emit_import_symbol(g_symbol_base[(short)i].number);
        }
      }
      emit_runtime_routine_imports();
      for (i = 0; (int)(short)i < g_current_request->label_count; i = i + 1) {
        sym_kind = (short)(char)g_symbol_base[(short)i].kind;
        switch(sym_kind) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 0xf:
          sym_section = find_section_by_id(g_current_request,g_symbol_base[(short)i].section_id);
          g_symbol_base[(short)i].section_number = sym_section->layout->section_number[0];
          break;
        case 6:
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
          break;
        case 7:
          sym_section = find_section_by_id(g_current_request,g_symbol_base[(short)i].section_id);
          g_symbol_base[(short)i].section_number = sym_section->layout->section_number[1];
          break;
        case 8:
          sym_section = find_section_by_id(g_current_request,g_symbol_base[(short)i].section_id);
          g_symbol_base[(short)i].section_number = sym_section->layout->section_number[2];
          break;
        case 9:
          sym_section = find_section_by_id(g_current_request,g_symbol_base[(short)i].section_id);
          g_symbol_base[(short)i].section_number = sym_section->layout->section_number[3];
        }
        if ((((sym_kind == 7) || (sym_kind == 8)) || ((sym_kind == 9 || (sym_kind == 0xc)))) &&
           ((g_symbol_base[(short)i].flags & 0x80) != 0)) {
          emit_export_symbol(g_symbol_base[(short)i].number);
        }
      }
      if (empty_input == 0) {
        if ((((first_op[0] == '\f') || (first_op[0] == '\r')) || (first_op[0] == '\x0e')) ||
           (first_op[0] == '\x0f')) {
          g_backend_first_record = first_op[0];
          read_backend_record_payload
                    (g_backend_record_input,(psd *)&g_backend_first_record,first_op[0]);
          if ((first_op[0] != '\f') || (g_current_request->sections->size[0] != 0)) {
            switch_section((psd *)&g_backend_first_record);
          }
          emit_final_asm_record_stream();
        }
      }
      else if (g_current_request->code != 1) {
        put_text_at_column(2,&s_dot_END_00440d50,1);
        flush_output_line(2);
      }
      if (g_current_request->code == 1) {
        flush_reloc_records();
        if (g_current_request->debug != 0) {
          emit_debug_information();
        }
        append_object_record_bytes((uchar *)0x0,0,0xff);
        *g_output_channels[1].buffer = -1;
        g_output_channels[1].cursor = g_output_channels[1].cursor + 2;
        finish_object_record(0x7f);
      }
      if (g_current_request->asm_debug == '\x01') {
        free_line_directive_list(1);
      }
      free_size_decision_stream_buffer();
      if ((g_current_request->show & 2) != 0) {
        pad_listing_page();
        close_output_stream(3);
      }
      if (g_current_request->code == 1) {
        close_output_stream(1);
      }
      else {
        close_output_stream(2);
      }
      return;
    }
    if ((((g_symbol_base[(short)i].flags & 0x40) == 0) && ((g_symbol_base[(short)i].attr & 3) != 0))
       && (g_current_request->sections->next->size[2] == 0)) {
      g_extra_section_needed = '\x01';
      goto LAB_00412385;
    }
    i = i + 1;
  } while( true );
#undef first_op
#undef bytes_read
#undef cur_section
#undef i
#undef empty_input
#undef sym_kind
#undef lit_header
#undef backend_path
}
