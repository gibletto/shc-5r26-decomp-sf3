#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_intermediate_file
#define g_intermediate_file (*(FILE * *)(g_sd + 0x9308))
#undef g_last_attributed_symbol
#define g_last_attributed_symbol (*(symbol * *)(g_sd + 0xfb1c))
#undef g_name_chunk_cursor
#define g_name_chunk_cursor (*(char * *)(g_sd + 0x930c))
#undef g_name_chunk_end
#define g_name_chunk_end (*(char * *)(g_sd + 0x9310))
#undef g_string_pool_chunk
#define g_string_pool_chunk (*(char * *)(g_sd + 0x9314))
#undef g_symbol_base
#define g_symbol_base (*(symbol * *)(g_sd + 0x1314c))
#undef g_symbol_table
#define g_symbol_table (*(symbol * *)(g_sd + 0xf8f4))
#undef g_symbol_table_next
#define g_symbol_table_next (*(symbol * *)(g_sd + 0x10c70))


// entry: 00413ab0
// name : load_intermediate_record_stream
// size : 2910
// sig  : void __cdecl load_intermediate_record_stream(char *path,request *req)


int __cdecl load_intermediate_record_stream(char *path,request *req)

{
  unsigned char _frec_28[40];
#define flag_byte (*(byte *)(_frec_28 + 0))
#define flag_byte2 (*(char *)(_frec_28 + 1))
#define stack_value_buf (*(char (*)[4])(_frec_28 + 4))
#define i (*(byte *)(_frec_28 + 8))
#define done (*(int *)(_frec_28 + 12))
#define attr_byte (*(byte (*)[4])(_frec_28 + 16))
#define range (*(aux_reg_range * *)(_frec_28 + 20))
#define hashed_sym (*(symbol * *)(_frec_28 + 24))
#define bucket (*(short *)(_frec_28 + 28))
#define n_ranges (*(byte (*)[4])(_frec_28 + 32))
  byte stack_kind;
  char *name_text;
  int close_status;
  
  done = 0;
  g_intermediate_file = stock_fopen(path,&s_rb_00440d58);
  if (g_intermediate_file == (FILE *)0x0) {
    report_message_at_source_line(0,0,0xce4,(char *)0x0);
  }
  g_symbol_table = stock_calloc(req->label_count,0x2c);
  g_symbol_base = g_symbol_table;
  if (g_symbol_table == (symbol *)0x0) {
    report_message_at_source_line(0,0,0xbcd,(char *)0x0);
  }
  g_aux_record_table = stock_calloc(req->aux_count,0x44);
  if ((req->aux_count != 0) && (g_aux_record_table == (aux_record *)0x0)) {
    report_message_at_source_line(0,0,0xbcd,(char *)0x0);
  }
  for (bucket = 0; bucket < 0x3fd; bucket = bucket + 1) {
    g_symbol_hash[bucket] = (symbol *)0x0;
  }
  g_last_attributed_symbol = g_symbol_table;
  g_symbol_table_next = g_symbol_table;
  g_loaded_aux_count = 0;
  g_symbol_ordinal = 0;
  g_name_chunk_cursor = (char *)0x0;
  g_name_chunk_end = (char *)0x0;
  g_string_pool_chunk = (char *)0x0;
  while (done == 0) {
    read_intermediate_bytes((char *)g_intermediate_record_header,1);
    switch(g_intermediate_record_header[0] & 0x1f) {
    case 0:
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
      g_symbol_table_next->kind = g_intermediate_record_header[0] & 0x1f;
      g_symbol_table_next->flags = g_intermediate_record_header[0] & 0xc0;
      read_intermediate_bytes((char *)g_intermediate_record_header,8);
      *(uchar *)&g_symbol_table_next->number = g_intermediate_record_header[0];
      *(uchar *)((int)&g_symbol_table_next->number + 1) = g_intermediate_record_header[1];
      *(uchar *)&g_symbol_table_next->section_id = g_intermediate_record_header[2];
      *(uchar *)((int)&g_symbol_table_next->section_id + 1) = g_intermediate_record_header[3];
      *(uchar *)&g_symbol_table_next->value = g_intermediate_record_header[4];
      *(uchar *)((int)&g_symbol_table_next->value + 1) = g_intermediate_record_header[5];
      *(uchar *)((int)&g_symbol_table_next->value + 2) = g_intermediate_record_header[6];
      *(uchar *)((int)&g_symbol_table_next->value + 3) = g_intermediate_record_header[7];
      g_symbol_table_next->hash_next = g_symbol_hash[(int)g_symbol_table_next->number % 0x3fd];
      g_symbol_hash[(int)g_symbol_table_next->number % 0x3fd] = g_symbol_table_next;
      g_symbol_ordinal = g_symbol_ordinal + 1;
      g_symbol_table_next->sequence = g_symbol_ordinal;
      if (4 < (g_symbol_table_next->kind & 0x1f)) {
        name_text = read_intermediate_string();
        g_symbol_table_next->name = name_text;
      }
      if (6 < (g_symbol_table_next->kind & 0x1f)) {
        read_intermediate_bytes((char *)attr_byte,1);
        g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 1;
        g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 2;
        g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 4;
        g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 8;
        g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 0x10;
        g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 0x20;
        read_intermediate_bytes((char *)&g_symbol_table_next->attr2,1);
        g_last_attributed_symbol = g_symbol_table_next;
      }
      break;
    case 6:
      break;
    case 0xc:
      g_symbol_table_next->kind = g_intermediate_record_header[0] & 0x1f;
      g_symbol_table_next->flags = g_intermediate_record_header[0] & 0xc0;
      read_intermediate_bytes((char *)&g_symbol_table_next->number,2);
      read_intermediate_bytes((char *)(g_aux_record_table + g_loaded_aux_count),4);
      read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].max_stack,4);
      read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].sp_adjust,4);
      read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].saved_regs2,2);
      read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].saved_regs,2);
      read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].saved_mac,1);
      read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].saved_sys,1);
      read_intermediate_bytes((char *)n_ranges,1);
      g_aux_record_table[g_loaded_aux_count].range_count = (ushort)n_ranges[0];
      g_aux_record_table[g_loaded_aux_count].ranges = (aux_reg_range *)0x0;
      g_aux_record_table[g_loaded_aux_count].stack_offset_count = 0;
      for (i = 0; i < n_ranges[0]; i = i + 1) {
        range = pool_alloc(0x10);
        if (range == (aux_reg_range *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        range->next = g_aux_record_table[g_loaded_aux_count].ranges;
        g_aux_record_table[g_loaded_aux_count].ranges = range;
        read_intermediate_bytes(&range->before_reg,1);
        read_intermediate_bytes(&range->after_reg,1);
        read_intermediate_bytes((char *)&range->start_expno,4);
        read_intermediate_bytes((char *)&range->end_expno,4);
      }
      read_intermediate_bytes((char *)&flag_byte,2);
      if (flag_byte == 1) {
        g_aux_record_table[g_loaded_aux_count].flags =
             g_aux_record_table[g_loaded_aux_count].flags | 0x8000;
      }
      if (flag_byte2 == '\x01') {
        g_aux_record_table[g_loaded_aux_count].flags =
             g_aux_record_table[g_loaded_aux_count].flags | 0x4000;
      }
      read_intermediate_bytes((char *)&flag_byte,1);
      if ((flag_byte & 0x80) != 0) {
        stack_kind = flag_byte & 3;
        if (stack_kind == 0) {
          g_aux_record_table[g_loaded_aux_count].flags =
               g_aux_record_table[g_loaded_aux_count].flags | 0x800;
          read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].stack_value,4);
        }
        else if (stack_kind == 1) {
          g_aux_record_table[g_loaded_aux_count].flags =
               g_aux_record_table[g_loaded_aux_count].flags | 0x1000;
          read_intermediate_bytes(stack_value_buf,4);
          *(short *)&g_aux_record_table[g_loaded_aux_count].stack_value = (*(unsigned short *)((char *)&stack_value_buf + 0));
        }
        else if (stack_kind == 3) {
          g_aux_record_table[g_loaded_aux_count].flags =
               g_aux_record_table[g_loaded_aux_count].flags | 0x1800;
          read_intermediate_bytes(stack_value_buf,4);
          *(short *)&g_aux_record_table[g_loaded_aux_count].stack_value = (*(unsigned short *)((char *)&stack_value_buf + 0));
        }
        else {
          report_message_at_source_line(0,0,0x131a,(char *)0x0);
        }
      }
      read_intermediate_bytes((char *)&flag_byte,1);
      if ((flag_byte & 0x80) != 0) {
        g_aux_record_table[g_loaded_aux_count].flags =
             g_aux_record_table[g_loaded_aux_count].flags | 0x2000;
        read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].trap_number,1);
      }
      name_text = read_intermediate_string();
      g_symbol_table_next->name = name_text;
      read_intermediate_bytes((char *)&g_aux_record_table[g_loaded_aux_count].expno_count,4);
      read_intermediate_bytes((char *)attr_byte,1);
      g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 1;
      g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 2;
      g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 4;
      g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 8;
      g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 0x10;
      g_symbol_table_next->attr = g_symbol_table_next->attr | attr_byte[0] & 0x20;
      read_intermediate_bytes
                ((char *)g_aux_record_table[g_loaded_aux_count].runtime_routines_used,0x17);
      read_intermediate_bytes(&g_aux_record_table[g_loaded_aux_count].reg28,1);
      g_symbol_table_next->aux_index = (short)g_loaded_aux_count;
      g_loaded_aux_count = g_loaded_aux_count + 1;
      g_symbol_ordinal = g_symbol_ordinal + 1;
      g_symbol_table_next->sequence = g_symbol_ordinal;
      g_last_attributed_symbol = g_symbol_table_next;
      hashed_sym = find_symbol_entry_by_id(g_symbol_table_next->number);
      if (hashed_sym == (symbol *)0x0) {
        report_message_at_source_line(0,0,0x131b,(char *)0x0);
      }
      hashed_sym->name = g_symbol_table_next->name;
      hashed_sym->aux_index = g_symbol_table_next->aux_index;
      hashed_sym->attr = g_symbol_table_next->attr;
      break;
    case 0xd:
      if ((g_last_attributed_symbol == g_symbol_base) && (g_symbol_table != g_symbol_base)) {
        g_last_attributed_symbol = g_symbol_table_next + -1;
      }
      read_intermediate_bytes((char *)&g_last_label_number,2);
      done = 1;
      break;
    case 0xe:
      if ((g_last_attributed_symbol == g_symbol_base) && (g_symbol_table != g_symbol_base)) {
        g_last_attributed_symbol = g_symbol_table_next + -1;
      }
      read_intermediate_bytes((char *)&g_export_symbol_count,2);
      read_intermediate_bytes(&DAT_0044bc68,2);
      read_intermediate_bytes(&g_runtime_routines_used,0x20);
      break;
    default:
      report_message_at_source_line(0,0,0x131c,(char *)0x0);
    }
    if (g_symbol_table_next->kind != '\0') {
      g_symbol_table_next = g_symbol_table_next + 1;
    }
  }
  g_loaded_aux_count = 0;
  close_status = _fclose(g_intermediate_file);
  if (close_status != 0) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  return;
#undef flag_byte
#undef flag_byte2
#undef stack_value_buf
#undef i
#undef done
#undef attr_byte
#undef range
#undef hashed_sym
#undef bucket
#undef n_ranges
}
