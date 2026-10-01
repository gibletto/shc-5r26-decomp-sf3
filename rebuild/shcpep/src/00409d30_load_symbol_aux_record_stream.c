#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_input
#define g_asa_input (*(FILE * *)(g_sd + 0x5348))
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_last_symbol_record
#define g_last_symbol_record (*(symbol * *)(g_sd + 0x5d28))
#undef g_symbol_record_base
#define g_symbol_record_base (*(symbol * *)(g_sd + 0x6e10))
#undef g_symbol_records
#define g_symbol_records (*(symbol * *)(g_sd + 0x5d10))


// entry: 00409d30
// name : load_symbol_aux_record_stream
// size : 2242
// sig  : void load_symbol_aux_record_stream(char * path, request * req)


int __cdecl load_symbol_aux_record_stream(char *path,request *req)

{
  unsigned char _frec_8[8];
#define n_ranges (*(byte *)(_frec_8 + 0))
#define attr_bits (*(byte *)(_frec_8 + 1))
#define opt_byte (*(byte *)(_frec_8 + 2))
#define local_5 (*(char *)(_frec_8 + 3))
#define value_buf (*(char (*)[4])(_frec_8 + 4))
  byte bVar1;
  short i;
  aux_reg_range *range;
  char *str;
  symbol *sym;
  int iVar2;
  bool done;
  byte *flags_byte;
  
  done = false;
  g_asa_input = open_shared_file(path,&s_open_mode_rb);
  if (g_asa_input == (FILE *)0x0) {
    report_compiler_message(0,0,0xce4,(char *)0x0);
  }
  g_symbol_records = stock_calloc(req->label_count,0x2c);
  g_symbol_record_base = g_symbol_records;
  if (g_symbol_records == (symbol *)0x0) {
    report_compiler_message(0,0,0xbcd,(char *)0x0);
  }
  g_aux_record_table = stock_calloc(req->aux_count,0x44);
  if ((req->aux_count != 0) && (g_aux_record_table == (aux_record *)0x0)) {
    report_compiler_message(0,0,0xbcd,(char *)0x0);
  }
  i = 0;
  do {
    iVar2 = (int)i;
    i = i + 1;
    g_symbol_hash[iVar2] = (symbol *)0x0;
  } while (i < 0x3fd);
  g_last_symbol_record = g_symbol_records;
  g_current_symbol = g_symbol_records;
  g_aux_record_count = 0;
  g_symbol_sequence_counter = 0;
  g_string_pool_cursor = 0;
  g_string_pool_end = 0;
  g_string_pool_block = 0;
  do {
    read_asa_bytes((char *)g_asa_read_buffer,1);
    bVar1 = g_asa_read_buffer[0] & 0x1f;
    switch(bVar1) {
    case 0:
    case 6:
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
      g_current_symbol->type = bVar1;
      g_current_symbol->flags = g_asa_read_buffer[0] & 0xc0;
      read_asa_bytes((char *)g_asa_read_buffer,8);
      *(uchar *)&g_current_symbol->number = g_asa_read_buffer[0];
      *(uchar *)((int)&g_current_symbol->number + 1) = g_asa_read_buffer[1];
      *(uchar *)&g_current_symbol->header_word = g_asa_read_buffer[2];
      *(uchar *)((int)&g_current_symbol->header_word + 1) = g_asa_read_buffer[3];
      *(uchar *)&g_current_symbol->value = g_asa_read_buffer[4];
      *(uchar *)((int)&g_current_symbol->value + 1) = g_asa_read_buffer[5];
      *(uchar *)((int)&g_current_symbol->value + 2) = g_asa_read_buffer[6];
      *(uchar *)((int)&g_current_symbol->value + 3) = g_asa_read_buffer[7];
      g_current_symbol->hash_next = g_symbol_hash[g_current_symbol->number % 0x3fd];
      sym = g_current_symbol;
      g_symbol_sequence_counter = g_symbol_sequence_counter + 1;
      g_symbol_hash[g_current_symbol->number % 0x3fd] = g_current_symbol;
      sym->sequence = g_symbol_sequence_counter;
      if (4 < (g_current_symbol->type & 0x1f)) {
        str = read_asa_counted_string();
        g_current_symbol->name = str;
      }
      if (6 < (g_current_symbol->type & 0x1f)) {
        read_asa_bytes((char *)&attr_bits,1);
        g_current_symbol->attr = g_current_symbol->attr | attr_bits & 1;
        g_current_symbol->attr = g_current_symbol->attr | attr_bits & 2;
        g_current_symbol->attr = g_current_symbol->attr | attr_bits & 4;
        g_current_symbol->attr = g_current_symbol->attr | attr_bits & 8;
        g_current_symbol->attr = g_current_symbol->attr | attr_bits & 0x10;
        g_current_symbol->attr = g_current_symbol->attr | attr_bits & 0x20;
        read_asa_bytes((char *)&g_current_symbol->attr2,1);
        g_last_symbol_record = g_current_symbol;
      }
      break;
    case 0xc:
      g_current_symbol->type = bVar1;
      g_current_symbol->flags = g_asa_read_buffer[0] & 0xc0;
      read_asa_bytes((char *)&g_current_symbol->number,2);
      read_asa_bytes((char *)(g_aux_record_table + g_aux_record_count),4);
      read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].max_stack,4);
      read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].sp_adjust,4);
      read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].saved_regs2,2);
      read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].saved_regs,2);
      read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].saved_mac,1);
      read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].saved_sys,1);
      read_asa_bytes((char *)&n_ranges,1);
      g_aux_record_table[g_aux_record_count].range_count = (ushort)n_ranges;
      g_aux_record_table[g_aux_record_count].ranges = (aux_reg_range *)0x0;
      bVar1 = 0;
      g_aux_record_table[g_aux_record_count].unknown_1c = 0;
      if (n_ranges != 0) {
        do {
          range = alloc_zeroed(0x10);
          if (range == (aux_reg_range *)0x0) {
            report_compiler_message(0,0,0xbcd,(char *)0x0);
          }
          bVar1 = bVar1 + 1;
          range->next = g_aux_record_table[g_aux_record_count].ranges;
          g_aux_record_table[g_aux_record_count].ranges = range;
          read_asa_bytes(&range->before_reg,1);
          read_asa_bytes(&range->after_reg,1);
          read_asa_bytes((char *)&range->start_expno,4);
          read_asa_bytes((char *)&range->end_expno,4);
        } while (bVar1 < n_ranges);
      }
      read_asa_bytes((char *)&opt_byte,2);
      if (opt_byte == 1) {
        g_aux_record_table[g_aux_record_count].flags =
             g_aux_record_table[g_aux_record_count].flags | 0x8000;
      }
      if (local_5 == '\x01') {
        flags_byte = (byte *)((int)&g_aux_record_table[g_aux_record_count].flags + 1);
        *flags_byte = *flags_byte | 0x40;
      }
      read_asa_bytes((char *)&opt_byte,1);
      if ((opt_byte & 0x80) != 0) {
        if ((opt_byte & 3) == 0) {
          flags_byte = (byte *)((int)&g_aux_record_table[g_aux_record_count].flags + 1);
          *flags_byte = *flags_byte | 8;
          read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].stack_value,4);
        }
        else {
          if ((opt_byte & 3) == 1) {
            flags_byte = (byte *)((int)&g_aux_record_table[g_aux_record_count].flags + 1);
            *flags_byte = *flags_byte | 0x10;
          }
          else {
            if ((opt_byte & 3) != 3) {
              report_compiler_message(0,0,0x131a,(char *)0x0);
              goto LAB_0040a35f;
            }
            flags_byte = (byte *)((int)&g_aux_record_table[g_aux_record_count].flags + 1);
            *flags_byte = *flags_byte | 0x18;
          }
          read_asa_bytes(value_buf,4);
          *(short *)&g_aux_record_table[g_aux_record_count].stack_value = (*(unsigned short *)((char *)&value_buf + 0));
        }
      }
LAB_0040a35f:
      read_asa_bytes((char *)&opt_byte,1);
      if ((opt_byte & 0x80) != 0) {
        flags_byte = (byte *)((int)&g_aux_record_table[g_aux_record_count].flags + 1);
        *flags_byte = *flags_byte | 0x20;
        read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].unknown_byte,1);
      }
      str = read_asa_counted_string();
      g_current_symbol->name = str;
      read_asa_bytes((char *)&g_aux_record_table[g_aux_record_count].asb_word,4);
      read_asa_bytes((char *)&attr_bits,1);
      g_current_symbol->attr = g_current_symbol->attr | attr_bits & 1;
      g_current_symbol->attr = g_current_symbol->attr | attr_bits & 2;
      g_current_symbol->attr = g_current_symbol->attr | attr_bits & 4;
      g_current_symbol->attr = g_current_symbol->attr | attr_bits & 8;
      g_current_symbol->attr = g_current_symbol->attr | attr_bits & 0x10;
      g_current_symbol->attr = g_current_symbol->attr | attr_bits & 0x20;
      read_asa_bytes((char *)g_aux_record_table[g_aux_record_count].asb_bytes,0x17);
      read_asa_bytes(&g_aux_record_table[g_aux_record_count].reg28,1);
      g_current_symbol->aux_index = (short)g_aux_record_count;
      g_aux_record_count = g_aux_record_count + 1;
      g_symbol_sequence_counter = g_symbol_sequence_counter + 1;
      g_current_symbol->sequence = g_symbol_sequence_counter;
      g_last_symbol_record = g_current_symbol;
      sym = find_symbol_record(g_current_symbol->number);
      if (sym == (symbol *)0x0) {
        report_compiler_message(0,0,0x131b,(char *)0x0);
      }
      sym->name = g_current_symbol->name;
      sym->aux_index = g_current_symbol->aux_index;
      sym->attr = g_current_symbol->attr;
      break;
    case 0xd:
      if ((g_last_symbol_record == g_symbol_record_base) &&
         (g_symbol_records != g_symbol_record_base)) {
        g_last_symbol_record = g_current_symbol + -1;
      }
      done = true;
      read_asa_bytes((char *)&g_last_labno,2);
      break;
    case 0xe:
      if ((g_last_symbol_record == g_symbol_record_base) &&
         (g_symbol_records != g_symbol_record_base)) {
        g_last_symbol_record = g_current_symbol + -1;
      }
      read_asa_bytes((char *)&g_asa_trailer_value1,2);
      read_asa_bytes((char *)&g_asa_trailer_value2,2);
      read_asa_bytes(&g_asa_trailer_bytes,0x20);
      break;
    default:
      report_compiler_message(0,0,0x131c,(char *)0x0);
    }
    if (g_current_symbol->type != '\0') {
      g_current_symbol = g_current_symbol + 1;
    }
    if (done) {
      g_aux_record_count = 0;
      iVar2 = _fclose(g_asa_input);
      if (iVar2 != 0) {
        report_compiler_message(0,0,0xce5,(char *)0x0);
      }
      return;
    }
  } while( true );
#undef n_ranges
#undef attr_bits
#undef opt_byte
#undef local_5
#undef value_buf
}



