#include "decls.h"
#include "imports.h"

// entry: 0042dd9b
// name : clear_pool_literal_table
// size : 246
// sig  : void __cdecl clear_pool_literal_table(literal_table *table)


int __cdecl clear_pool_literal_table(literal_table *table)

{
  int bucket_no;
  int freed_count;
  literal_entry *cur_lit;
  label_ref *cur_ref;
  literal_entry *next_lit;
  label_ref *next_ref;
  
  freed_count = 0;
  cur_lit = table->head;
  while (cur_lit != (literal_entry *)0x0) {
    next_lit = cur_lit->next;
    cur_ref = cur_lit->labels;
    while (cur_ref != (label_ref *)0x0) {
      next_ref = cur_ref->next;
      pool_free(cur_ref,8);
      cur_ref = next_ref;
    }
    pool_free(cur_lit,0x10);
    freed_count = freed_count + 1;
    cur_lit = next_lit;
  }
  for (bucket_no = 0; bucket_no < 0x7f; bucket_no = bucket_no + 1) {
    table->buckets[bucket_no] = (literal_entry *)0x0;
  }
  if (table->count != freed_count) {
    report_message_at_source_line(0,0,0x12f2,(char *)0x0);
  }
  table->head = (literal_entry *)0x0;
  table->tail = (literal_entry *)0x0;
  table->count = 0;
  return;
}
