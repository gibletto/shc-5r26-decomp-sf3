#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))


// entry: 004281b0
// name : add_literal_to_pool_table
// size : 310
// sig  : void __cdecl add_literal_to_pool_table(uint value,label_ref *refs,int pass,int is_long)


int __cdecl add_literal_to_pool_table(uint value,label_ref *refs,int pass,int is_long)

{
  unsigned char _frec_c[12];
#define labno_byte_hi (*(char *)(_frec_c + 0))
#define labno_byte_lo (*(char *)(_frec_c + 1))
#define lit_table (*(literal_table * *)(_frec_c + 4))
  symbol *pool_label_sym;
  int found;
  
  if (((pass == 1) && (g_word_literal_table_pass1.count == 0)) &&
     (g_long_literal_table_pass1.count == 0)) {
    if (g_last_label_number == 0x7fff) {
      report_message_at_source_line(0,0,0xbc8,(char *)0x0);
    }
    g_last_label_number = g_last_label_number + 1;
    g_literal_pool_label = g_last_label_number;
    pool_label_sym = create_symbol_entry('\x0f','\0',g_last_label_number);
    pool_label_sym->section_id = g_layout_section_pass1->id;
    store_u16_big_endian((ushort *)&g_literal_pool_label,(ushort *)&labno_byte_hi);
    record_size_decision_byte(labno_byte_hi);
    record_size_decision_byte(labno_byte_lo);
  }
  if (pass == 0) {
    if (is_long == 0) {
      lit_table = &g_word_literal_table;
    }
    else {
      lit_table = &g_long_literal_table;
    }
  }
  else if (is_long == 0) {
    lit_table = &g_word_literal_table_pass1;
  }
  else {
    lit_table = &g_long_literal_table_pass1;
  }
  found = find_pool_literal(lit_table,value,refs);
  if (found == 0) {
    add_pool_literal(lit_table,value,refs);
  }
  return;
#undef labno_byte_hi
#undef labno_byte_lo
#undef lit_table
}
