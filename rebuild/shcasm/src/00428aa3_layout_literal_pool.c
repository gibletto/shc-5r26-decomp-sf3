#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))


// entry: 00428aa3
// name : layout_literal_pool
// size : 1238
// sig  : void __cdecl layout_literal_pool(layout_record *rec,int pass)


int __cdecl layout_literal_pool(layout_record *rec,int pass)

{
  unsigned char _frec_14[20];
#define long_align_pad (*(int *)(_frec_14 + 0))
#define align_pad (*(int *)(_frec_14 + 4))
#define new_pool_size (*(int *)(_frec_14 + 8))
#define pool_flag (*(char (*)[4])(_frec_14 + 12))
  uint uVar1;
  symbol *pool_sym;
  symbol *pool_sym_again;
  uint sign_mask;
  int literal_bytes;
  
  if (rec->pool_size == 0) {
    if (pass != 0) {
      return;
    }
    if ((rec->misc & 2) != 0) {
      return;
    }
    uVar1 = read_file_bytes(g_lit_input,pool_flag,1);
    if (uVar1 != 0xffffffff) {
      return;
    }
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
    return;
  }
  if (pass == 0) {
    uVar1 = read_file_bytes(g_lit_input,pool_flag,1);
    if (uVar1 == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (pool_flag[0] != '\x01') {
      if (g_current_request->align16 == '\0') {
        g_layout_shrink_pass0 = g_layout_shrink_pass0 + rec->pool_size;
        rec->pool_size = 0;
        return;
      }
      g_layout_shrink_pass0 = g_layout_shrink_pass0 + rec->pool_size + -0xe;
      rec->pool_size = 0xe;
      return;
    }
    literal_bytes = g_long_literal_table.count * 4 + g_word_literal_table.count * 2;
    new_pool_size = literal_bytes + 2;
    if ((g_current_request->flags_13d & 8) == 0) {
      if (g_current_request->align16 != '\0') {
        new_pool_size = literal_bytes + 0x10;
      }
    }
    else {
      new_pool_size = literal_bytes + 0x3e;
    }
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + (rec->pool_size - new_pool_size);
  }
  else {
    if (((g_current_request->flags_13d & 8) != 0) && (rec->pool_size == 0x3e)) {
      g_layout_shrink_pass1 = g_layout_shrink_pass1 + rec->pool_size;
      rec->pool_size = 0;
      return;
    }
    if ((g_current_request->align16 != '\0') && (rec->pool_size == 0xe)) {
      new_pool_size = 0;
      uVar1 = (int)rec->size + rec->location;
      sign_mask = (int)uVar1 >> 0x1f;
      if (((uVar1 ^ sign_mask) - sign_mask & 0xf ^ sign_mask) != sign_mask) {
        uVar1 = (int)rec->size + rec->location;
        sign_mask = (int)uVar1 >> 0x1f;
        new_pool_size = 0x10 - (((uVar1 ^ sign_mask) - sign_mask & 0xf ^ sign_mask) - sign_mask);
      }
      g_layout_shrink_pass1 = g_layout_shrink_pass1 + (rec->pool_size - new_pool_size);
      rec->pool_size = (short)new_pool_size;
      return;
    }
    if ((g_current_request->flags_13d & 8) == 0) {
      if ((g_long_literal_table_pass1.count == 0) ||
         (uVar1 = (int)rec->size + g_word_literal_table_pass1.count * 2 + rec->location,
         sign_mask = (int)uVar1 >> 0x1f,
         ((uVar1 ^ sign_mask) - sign_mask & 3 ^ sign_mask) == sign_mask)) {
        long_align_pad = 0;
      }
      else {
        long_align_pad = 2;
      }
    }
    else {
      uVar1 = g_word_literal_table_pass1.count >> 0x1f;
      if (((g_word_literal_table_pass1.count ^ uVar1) - uVar1 & 1 ^ uVar1) == uVar1) {
        long_align_pad = 0;
      }
      else {
        long_align_pad = 2;
      }
    }
    align_pad = 0;
    if (((g_current_request->flags_13d & 8) != 0) &&
       (uVar1 = (int)rec->size + rec->location, sign_mask = (int)uVar1 >> 0x1f,
       ((uVar1 ^ sign_mask) - sign_mask & 0x1f ^ sign_mask) != sign_mask)) {
      uVar1 = (int)rec->size + rec->location;
      sign_mask = (int)uVar1 >> 0x1f;
      align_pad = 0x20 - (((uVar1 ^ sign_mask) - sign_mask & 0x1f ^ sign_mask) - sign_mask);
    }
    new_pool_size =
         g_long_literal_table_pass1.count * 4 + g_word_literal_table_pass1.count * 2 + align_pad +
         long_align_pad;
    if ((g_current_request->flags_13d & 8) == 0) {
      if ((g_current_request->align16 != '\0') &&
         (uVar1 = (int)rec->size + rec->location + new_pool_size, sign_mask = (int)uVar1 >> 0x1f,
         ((uVar1 ^ sign_mask) - sign_mask & 0xf ^ sign_mask) != sign_mask)) {
        uVar1 = (int)rec->size + rec->location + new_pool_size;
        sign_mask = (int)uVar1 >> 0x1f;
        new_pool_size =
             new_pool_size +
             (0x10 - (((uVar1 ^ sign_mask) - sign_mask & 0xf ^ sign_mask) - sign_mask));
      }
    }
    else {
      uVar1 = (int)rec->size + rec->location + new_pool_size;
      sign_mask = (int)uVar1 >> 0x1f;
      if (((uVar1 ^ sign_mask) - sign_mask & 0x1f ^ sign_mask) != sign_mask) {
        uVar1 = (int)rec->size + rec->location + new_pool_size;
        sign_mask = (int)uVar1 >> 0x1f;
        new_pool_size =
             new_pool_size +
             (0x20 - (((uVar1 ^ sign_mask) - sign_mask & 0x1f ^ sign_mask) - sign_mask));
      }
    }
    if ((g_word_literal_table_pass1.count != 0) || (g_long_literal_table_pass1.count != 0)) {
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_sym->value = (int)rec->size + rec->location + align_pad;
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_sym_again = find_symbol_by_id(g_literal_pool_label);
      pool_sym->layout_records =
           (layout_record *)
           (pool_sym_again->value + g_word_literal_table_pass1.count * 2 + long_align_pad);
    }
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + (rec->pool_size - new_pool_size);
  }
  rec->pool_size = (short)new_pool_size;
  if (pass == 0) {
    clear_pool_literal_table(&g_word_literal_table);
    clear_pool_literal_table(&g_long_literal_table);
  }
  else {
    clear_pool_literal_table(&g_word_literal_table_pass1);
    clear_pool_literal_table(&g_long_literal_table_pass1);
  }
  return;
#undef long_align_pad
#undef align_pad
#undef new_pool_size
#undef pool_flag
}
