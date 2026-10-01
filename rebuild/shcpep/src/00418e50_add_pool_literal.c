#include "decls.h"
#include "imports.h"

// entry: 00418e50
// name : add_pool_literal
// size : 216
// sig  : void add_pool_literal(literal_table * table, uint value, label_ref * labels)


int __cdecl add_pool_literal(literal_table *table,uint value,label_ref *labels)

{
  uint hash;
  literal_entry *entry;
  label_ref *copy;
  label_ref *new_ref;
  literal_entry *bucket_entry;
  literal_entry *next_entry;
  label_ref *src;
  
  hash = value;
  for (src = labels; src != (label_ref *)0x0; src = src->next) {
    hash = hash + (int)src->labno1 + (int)src->labno2;
  }
  entry = alloc_zeroed(0x10);
  entry->value = value;
  if (labels != (label_ref *)0x0) {
    copy = alloc_zeroed(8);
    copy->labno1 = labels->labno1;
    copy->labno2 = labels->labno2;
    entry->labels = copy;
    for (src = labels->next; src != (label_ref *)0x0; src = src->next) {
      new_ref = alloc_zeroed(8);
      copy->next = new_ref;
      copy->next->labno1 = src->labno1;
      copy->next->labno2 = src->labno2;
      copy = copy->next;
    }
  }
  bucket_entry = table->buckets[hash % 0x7f];
  if (bucket_entry == (literal_entry *)0x0) {
    table->buckets[hash % 0x7f] = entry;
  }
  else {
    next_entry = bucket_entry->hash_next;
    while (next_entry != (literal_entry *)0x0) {
      bucket_entry = bucket_entry->hash_next;
      next_entry = bucket_entry->hash_next;
    }
    bucket_entry->hash_next = entry;
  }
  if (table->head != (literal_entry *)0x0) {
    table->tail->next = entry;
    table->tail = entry;
    table->count = table->count + 1;
    return;
  }
  table->head = entry;
  table->tail = entry;
  table->count = table->count + 1;
  return;
}



