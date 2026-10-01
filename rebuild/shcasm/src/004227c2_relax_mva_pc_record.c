#include "decls.h"
#include "imports.h"

// entry: 004227c2
// name : relax_mva_pc_record
// size : 339
// sig  : void __cdecl relax_mva_pc_record(layout_record *item,int pass)


int __cdecl relax_mva_pc_record(layout_record *item,int pass)

{
  int displacement;
  char new_size;
  
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
  }
  displacement = compute_branch_displacement(item,pass);
  if ((displacement < 0) || (0x3fe < displacement)) {
    if ((displacement < 0x3ff) || ((0x47d < displacement || (item->size < '\x04')))) {
      new_size = '\x02';
      if (pass == 1) {
        record_size_decision_byte('\x02');
      }
      add_literal_to_pool_table(item->value,item->labels,pass,1);
    }
    else {
      new_size = '\x04';
      if (pass == 1) {
        record_size_decision_byte('\x01');
      }
    }
  }
  else {
    new_size = '\x02';
    if (pass == 1) {
      record_size_decision_byte('\0');
    }
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
