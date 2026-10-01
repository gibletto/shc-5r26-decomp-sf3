#include "decls.h"
#include "imports.h"

// entry: 0040dd0b
// name : print_pc_relative_literal_comment
// size : 541
// sig  : void __cdecl print_pc_relative_literal_comment(short channel,psd *rec)


int __cdecl print_pc_relative_literal_comment(short channel,psd *rec)

{
  symbol *pool_sym;
  int offset;
  bool need_plus;
  int skip;
  literal_entry *lit;
  label_ref *ref;
  
  if ((rec->flg & 3) == 2) {
    lit = g_long_literal_table.head;
    pool_sym = find_symbol_by_id(rec->ea1->labels->labno1);
    offset = rec->ea1->disp - ((int)pool_sym->layout_records - pool_sym->value);
    skip = (int)(offset + (offset >> 0x1f & 3U)) >> 2;
  }
  else {
    lit = g_word_literal_table.head;
    skip = rec->ea1->disp / 2;
  }
  while (skip != 0) {
    lit = lit->next;
    skip = skip + -1;
  }
  put_text_at_column(channel,&s_semi_sp_0043c7b8,3);
  if (lit->labels == (label_ref *)0x0) {
    put_text_at_column(channel,&s_H_apos_0043c7bc,3);
    if ((rec->flg & 3) == 2) {
      write_hex_long(channel,lit->value,3);
    }
    else {
      write_hex_word(channel,lit->value,3);
    }
  }
  else {
    need_plus = lit->value != 0;
    if (need_plus) {
      put_text_at_column(channel,&s_H_apos_0043c7c0,3);
      write_hex_long(channel,lit->value,3);
    }
    for (ref = lit->labels; ref != (label_ref *)0x0; ref = ref->next) {
      if ((need_plus) && (0 < ref->labno1)) {
        put_char_at_column(channel,'+',3);
      }
      write_label_name(channel,ref->labno1,3);
      if (ref->labno2 != 0) {
        if (0 < ref->labno2) {
          put_char_at_column(channel,'+',3);
        }
        write_label_name(channel,ref->labno2,3);
      }
      need_plus = true;
    }
  }
  return;
}
