#include "decls.h"
#include "imports.h"

// entry: 0042dc08
// name : add_pool_literal
// size : 403
// sig  : void __cdecl add_pool_literal(literal_table *table,uint value,label_ref *labels)


int __cdecl add_pool_literal(literal_table *table,uint value,label_ref *labels)

{
  literal_entry *new_lit;
  label_ref *new_ref;
  uint hash_value;
  literal_entry *bucket_lit;
  label_ref *copy_ref;
  label_ref *src_ref;
  
  hash_value = value;
  for (src_ref = labels; src_ref != (label_ref *)0x0; src_ref = src_ref->next) {
    hash_value = hash_value + (int)src_ref->labno1 + (int)src_ref->labno2;
  }
  new_lit = pool_alloc(0x10);
  new_lit->value = value;
  if (labels != (label_ref *)0x0) {
    copy_ref = pool_alloc(8);
    copy_ref->labno1 = labels->labno1;
    copy_ref->labno2 = labels->labno2;
    new_lit->labels = copy_ref;
    for (src_ref = labels->next; src_ref != (label_ref *)0x0; src_ref = src_ref->next) {
      new_ref = pool_alloc(8);
      copy_ref->next = new_ref;
      copy_ref->next->labno1 = src_ref->labno1;
      copy_ref->next->labno2 = src_ref->labno2;
      copy_ref = copy_ref->next;
    }
  }
  bucket_lit = table->buckets[hash_value % 0x7f];
  if (bucket_lit == (literal_entry *)0x0) {
    table->buckets[hash_value % 0x7f] = new_lit;
  }
  else {
    for (; bucket_lit->hash_next != (literal_entry *)0x0; bucket_lit = bucket_lit->hash_next) {
    }
    bucket_lit->hash_next = new_lit;
  }
  if (table->head == (literal_entry *)0x0) {
    table->head = new_lit;
    table->tail = new_lit;
  }
  else {
    table->tail->next = new_lit;
    table->tail = new_lit;
  }
  table->count = table->count + 1;
  return;
}
