#include "decls.h"
#include "imports.h"

// entry: 00422915
// name : relax_movi_record
// size : 429
// sig  : void __cdecl relax_movi_record(layout_record *item,int pass)


int __cdecl relax_movi_record(layout_record *item,int pass)

{
  int iVar1;
  int word_literal;
  char new_size;
  
  if ((((item->flg & 3) == 0) || ((item->flg & 3) == 1)) && ((item->misc & 0x40) != 0)) {
    new_size = '\x04';
  }
  else {
    new_size = '\x02';
  }
  if (item->labels == (label_ref *)0x0) {
    iVar1 = item->value;
    if ((iVar1 < -0x80) || (0x7f < iVar1)) {
      if ((iVar1 < -0x8000) || (0x7fff < iVar1)) {
        add_literal_to_pool_table(item->value,item->labels,pass,1);
      }
      else {
        add_literal_to_pool_table(item->value,item->labels,pass,0);
      }
    }
  }
  else {
    iVar1 = get_marked_symbol_attr_low_bits(item->labels);
    if (((char)iVar1 == '\0') &&
       (word_literal = is_word_symbol_literal(item->value,item->labels), word_literal == 0)) {
      add_literal_to_pool_table(item->value,item->labels,pass,1);
    }
    else if ((char)iVar1 != '\x01') {
      add_literal_to_pool_table(item->value,item->labels,pass,0);
    }
  }
  if ((item->flg & 0x40) != 0) {
    new_size = new_size + -2;
  }
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  return;
}
