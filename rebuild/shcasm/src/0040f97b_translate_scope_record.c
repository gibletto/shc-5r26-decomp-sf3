#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x10b2c))
#undef g_debug_record_cursor
#define g_debug_record_cursor (*(unsigned short * *)(g_sd + 0x13030))
#undef g_debug_record_input
#define g_debug_record_input (*(FILE * *)(g_sd + 0xcf20))
#undef g_object_record_cursor
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))
#undef g_stack_offset_temp
#define g_stack_offset_temp (*(FILE * *)(g_sd + 0xcefc))


// entry: 0040f97b
// name : translate_scope_record
// size : 1970
// sig  : void translate_scope_record(void)


int __cdecl translate_scope_record(void)

{
  unsigned char _frec_128[296];
#define scope_length (*(uint *)(_frec_128 + 0))
#define saved_scope_kind (*(byte *)(_frec_128 + 4))
#define frame_info_len (*(int *)(_frec_128 + 8))
#define skipped_name (*(char (*)[256])(_frec_128 + 12))
#define bytes_read (*(uint *)(_frec_128 + 268))
#define cur_section (*(request_section * *)(_frec_128 + 272))
#define func_aux_ix (*(short *)(_frec_128 + 276))
#define frame_offset (*(uint *)(_frec_128 + 280))
#define scope_end_found (*(int *)(_frec_128 + 284))
#define name_length (*(ushort *)(_frec_128 + 288))
  short saved_reg_count;
  uint read_status;
  symbol *func_sym;
  ushort *dest;
  byte frame_flags;
  
  g_object_record_buffer[0] = *(uchar *)g_debug_record_cursor;
  g_debug_record_cursor = (ushort *)((int)g_debug_record_cursor + 1);
  g_object_record_buffer[1] = (uchar)g_current_request->optimize;
  if (((int)(char)g_object_record_buffer[0] & 0x80U) == 0) {
    if (((g_object_record_buffer[0] & 0x7f) == 3) && (g_drop_function_debug == 1)) {
      scope_end_found = 0;
      while (scope_end_found == 0) {
        bytes_read = read_file_bytes(g_debug_record_input,(char *)&g_debug_record_tag,2);
        if (bytes_read == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        else if ((bytes_read != 0) &&
                (read_status = read_file_bytes(g_debug_record_input,(char *)g_debug_record_body,
                                               g_temp_record_length - 2), read_status == 0xffffffff)
                ) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if ((g_debug_record_tag & 0x7f) == 0x34) {
          name_length = (ushort)g_debug_record_body[3];
          if ((name_length != 0) &&
             (read_status = read_file_bytes(g_debug_record_input,skipped_name,
                                            (int)(short)name_length), read_status == 0xffffffff)) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
        }
        else if (((g_debug_record_tag & 0x7f) == 0x32) && ((g_debug_record_body[0] & 0x7f) == 3)) {
          free_debug_symbol_table();
          scope_end_found = 1;
        }
      }
    }
    else {
      g_debug_scope_depth = g_debug_scope_depth + 1;
      if ((g_current_request->optimize == 0) ||
         (((g_object_record_buffer[0] & 0x7f) == 0 || ((g_object_record_buffer[0] & 0x7f) == 3)))) {
        if ((g_object_record_buffer[0] & 0x7f) == 0) {
          g_object_record_buffer[2] = '\0';
          g_object_record_buffer[3] = '\0';
        }
        else {
          dest = (ushort *)(g_object_record_buffer + 2);
          func_sym = find_symbol_by_id(g_debug_function_label);
          store_u16_big_endian((ushort *)&func_sym->section_number,dest);
        }
        g_scope_stack[g_scope_top + 1] = g_scope_stack[g_scope_top]->child;
        g_scope_top = g_scope_top + 1;
        store_u32_big_endian
                  ((uint *)g_scope_stack[g_scope_top],(uint *)(g_object_record_buffer + 4));
        if ((g_object_record_buffer[0] & 0x7f) == 0) {
          scope_length = 0;
          for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
              cur_section = cur_section->next) {
            scope_length = cur_section->size[0] + scope_length;
          }
        }
        else {
          scope_length = g_scope_stack[g_scope_top]->end - g_scope_stack[g_scope_top]->start;
        }
        store_u32_big_endian(&scope_length,(uint *)(g_object_record_buffer + 8));
        g_object_record_buffer[0xc] = (uchar)*g_debug_record_cursor;
        g_debug_record_cursor = (ushort *)((int)g_debug_record_cursor + 1);
        frame_info_len = 0;
        frame_flags = g_object_record_buffer[0xd];
        if ((g_object_record_buffer[0] & 0x7f) == 3) {
          func_sym = find_symbol_by_id(g_debug_function_label);
          func_aux_ix = func_sym->aux_index;
          if ((((int)(short)g_aux_record_table[func_aux_ix].flags & 0x8000U) == 0) &&
             ((g_aux_record_table[func_aux_ix].flags & 0x4000) == 0)) {
            g_object_record_buffer[0xd] = 0x80;
            saved_reg_count = count_saved_registers(func_aux_ix);
            frame_offset = -(saved_reg_count * 4 + 4);
            store_u32_big_endian(&frame_offset,(uint *)(g_object_record_buffer + 0xe));
            frame_info_len = 5;
          }
          else {
            g_object_record_buffer[0xd] = '\0';
            frame_info_len = 1;
          }
          frame_flags = g_object_record_buffer[0xd];
          if (((g_aux_record_table[func_aux_ix].flags & 0x4000) != 0) &&
             (frame_flags = g_object_record_buffer[0xd] | 0x40,
             (g_aux_record_table[func_aux_ix].flags & 0x1800) != 0)) {
            g_object_record_buffer[0xd] = g_object_record_buffer[0xd] | 0x60;
            read_status = read_file_bytes(g_stack_offset_temp,
                                          (char *)(g_object_record_buffer + frame_info_len + 0xd),4)
            ;
            if (read_status == 0xffffffff) {
              report_message_at_source_line(0,0,0xce6,(char *)0x0);
            }
            g_aux_record_table[func_aux_ix].stack_offset_count =
                 g_aux_record_table[func_aux_ix].stack_offset_count + -1;
            frame_info_len = frame_info_len + 4;
            frame_flags = g_object_record_buffer[0xd];
          }
        }
        g_object_record_buffer[0xd] = frame_flags;
        store_u16_big_endian
                  (g_debug_record_cursor,(ushort *)(g_object_record_buffer + frame_info_len + 0xd));
        g_debug_record_cursor = g_debug_record_cursor + 1;
        g_object_record_cursor = g_object_record_cursor + frame_info_len + 0xf;
        append_object_record_bytes
                  (g_object_record_buffer,frame_info_len + 0xf,(uint)g_debug_record_tag);
      }
      if ((g_object_record_buffer[0] & 0x7f) == 3) {
        emit_stack_offset_records();
        if (g_current_request->optimize != 0) {
          g_object_record_buffer[0] = '\x04';
          g_object_record_buffer[1] = (uchar)g_current_request->optimize;
          dest = (ushort *)(g_object_record_buffer + 2);
          func_sym = find_symbol_by_id(g_debug_function_label);
          store_u16_big_endian((ushort *)&func_sym->section_number,dest);
          g_scope_stack[g_scope_top + 1] = g_scope_stack[g_scope_top]->child;
          g_scope_top = g_scope_top + 1;
          store_u32_big_endian
                    ((uint *)g_scope_stack[g_scope_top],(uint *)(g_object_record_buffer + 4));
          scope_length = g_scope_stack[g_scope_top]->end - g_scope_stack[g_scope_top]->start;
          store_u32_big_endian(&scope_length,(uint *)(g_object_record_buffer + 8));
          g_object_record_buffer[0xc] = '\x01';
          store_u16_big_endian
                    ((ushort *)&g_debug_word_1001,(ushort *)(g_object_record_buffer + 0xd));
          append_object_record_bytes(g_object_record_buffer,0xf,0x32);
          append_object_record_bytes((uchar *)0x0,0,0xff);
        }
        if (g_function_debug_loaded == 0) {
          load_debug_symbol_tables();
          g_function_debug_loaded = 1;
        }
      }
    }
  }
  else {
    g_debug_scope_depth = g_debug_scope_depth + -1;
    if ((g_current_request->optimize != 0) && ((g_object_record_buffer[0] & 0x7f) == 3)) {
      saved_scope_kind = g_object_record_buffer[0];
      emit_block_scope_records();
      (&g_current_section)[g_scope_top]->size[1] = (int)g_scope_stack[g_scope_top]->next;
      g_scope_stack[g_scope_top] = (debug_scope *)(&g_current_section)[g_scope_top]->size[1];
      g_scope_top = g_scope_top + -1;
      g_object_record_buffer[0] = 0x84;
      append_object_record_bytes(g_object_record_buffer,1,0x32);
      append_object_record_bytes((uchar *)0x0,0,0xff);
      g_object_record_buffer[0] = saved_scope_kind;
    }
    if (((g_current_request->optimize == 0) || ((g_object_record_buffer[0] & 0x7f) == 0)) ||
       ((g_object_record_buffer[0] & 0x7f) == 3)) {
      (&g_current_section)[g_scope_top]->size[1] = (int)g_scope_stack[g_scope_top]->next;
      g_scope_stack[g_scope_top] = (debug_scope *)(&g_current_section)[g_scope_top]->size[1];
      g_scope_top = g_scope_top + -1;
      g_object_record_cursor = g_object_record_cursor + 1;
    }
    if (((g_current_request->optimize == 0) || ((g_object_record_buffer[0] & 0x7f) == 0)) ||
       ((g_object_record_buffer[0] & 0x7f) == 3)) {
      append_object_record_bytes(g_object_record_buffer,1,(uint)g_debug_record_tag);
    }
    if ((g_object_record_buffer[0] & 0x7f) == 3) {
      free_debug_symbol_table();
      free_debug_location_table();
      g_function_debug_loaded = 0;
    }
  }
  return;
#undef scope_length
#undef saved_scope_kind
#undef frame_info_len
#undef skipped_name
#undef bytes_read
#undef cur_section
#undef func_aux_ix
#undef frame_offset
#undef scope_end_found
#undef name_length
}
