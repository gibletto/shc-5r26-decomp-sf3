#include "decls.h"
#include "imports.h"

// entry: 00418f30
// name : clear_pool_literal_table
// size : 137
// sig  : void clear_pool_literal_table(literal_table * table)


int __cdecl clear_pool_literal_table(literal_table *table)

{
  int i;
  int freed;
  literal_entry **bucket;
  literal_entry *entry;
  label_ref *lref;
  literal_entry *next_entry;
  label_ref *next_ref;
  
  freed = 0;
  entry = table->head;
  while (entry != (literal_entry *)0x0) {
    next_entry = entry->next;
    lref = entry->labels;
    while (lref != (label_ref *)0x0) {
      next_ref = lref->next;
      pool_free(lref,8);
      lref = next_ref;
    }
    freed = freed + 1;
    pool_free(entry,0x10);
    entry = next_entry;
  }
  bucket = table->buckets;
  for (i = 0x7f; i != 0; i = i + -1) {
    *bucket = (literal_entry *)0x0;
    bucket = bucket + 1;
  }
  if (table->count != freed) {
    report_compiler_message(0,0,0x12f2,(char *)0x0);
  }
  table->head = (literal_entry *)0x0;
  table->tail = (literal_entry *)0x0;
  table->count = 0;
  return;
}



