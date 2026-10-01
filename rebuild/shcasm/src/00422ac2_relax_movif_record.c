#include "decls.h"
#include "imports.h"

// entry: 00422ac2
// name : relax_movif_record
// size : 166
// sig  : void __cdecl relax_movif_record(layout_record *item,int pass)


int __cdecl relax_movif_record(layout_record *item,int pass)

{
  char new_size;
  
  if ((item->flg & 0x20) == 0) {
    new_size = '\x04';
  }
  else {
    new_size = '\x06';
  }
  add_literal_to_pool_table(item->value,item->labels,pass,1);
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
