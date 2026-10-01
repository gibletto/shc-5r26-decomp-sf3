#include "decls.h"
#include "imports.h"

// entry: 004212d9
// name : resize_case_table_record
// size : 175
// sig  : void __cdecl resize_case_table_record(layout_record *table,int pass,int short_entries)


int __cdecl resize_case_table_record(layout_record *table,int pass,int short_entries)

{
  int new_size;
  
  if (pass == 0) {
    table->location = table->location - g_layout_shrink_pass0;
  }
  else {
    table->location = table->location - g_layout_shrink_pass1;
  }
  if (table->labels == (label_ref *)short_entries) {
    new_size = table->value;
  }
  else {
    new_size = table->value / 2;
  }
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + (table->value - new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + (table->value - new_size);
  }
  table->value = new_size;
  table->labels = (label_ref *)short_entries;
  return;
}
