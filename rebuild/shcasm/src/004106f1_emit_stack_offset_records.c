#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_stack_offset_temp
#define g_stack_offset_temp (*(FILE * *)(g_sd + 0xcefc))


// entry: 004106f1
// name : emit_stack_offset_records
// size : 281
// sig  : void emit_stack_offset_records(void)


int __cdecl emit_stack_offset_records(void)

{
  unsigned char _frec_14[20];
#define offset_count (*(uint *)(_frec_14 + 0))
#define count_b0 (*(uchar *)(_frec_14 + 4))
#define count_b1 (*(uchar *)(_frec_14 + 5))
#define count_b2 (*(uchar *)(_frec_14 + 6))
#define count_b3 (*(uchar *)(_frec_14 + 7))
#define label_word (*(ushort (*)[2])(_frec_14 + 8))
#define label_b0 (*(uchar *)(_frec_14 + 12))
#define label_b1 (*(uchar *)(_frec_14 + 13))
  symbol *func_sym;
  uint read_status;
  
  func_sym = find_symbol_by_id(g_debug_function_label);
  offset_count = g_aux_record_table[func_sym->aux_index].stack_offset_count;
  label_word[0] = g_debug_function_label - 0xb6;
  store_u16_big_endian(label_word,(ushort *)&label_b0);
  g_object_record_buffer[0] = label_b0;
  g_object_record_buffer[1] = label_b1;
  store_u32_big_endian(&offset_count,(uint *)&count_b0);
  g_object_record_buffer[2] = count_b0;
  g_object_record_buffer[3] = count_b1;
  g_object_record_buffer[4] = count_b2;
  g_object_record_buffer[5] = count_b3;
  append_object_record_bytes(g_object_record_buffer,6,0x3a);
  while( true ) {
    if (offset_count == 0) break;
    offset_count = offset_count - 1;
    read_status = read_file_bytes(g_stack_offset_temp,(char *)g_object_record_buffer,8);
    if (read_status == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    append_object_record_bytes(g_object_record_buffer,8,0x3a);
  }
  offset_count = offset_count - 1;
  append_object_record_bytes((uchar *)0x0,0,0xff);
  return;
#undef offset_count
#undef count_b0
#undef count_b1
#undef count_b2
#undef count_b3
#undef label_word
#undef label_b0
#undef label_b1
}
