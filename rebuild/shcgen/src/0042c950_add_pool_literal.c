#include "decls.h"
#include "imports.h"

// entry: 0042c950
// name : add_pool_literal
// size : 216
// sig  : void add_pool_literal(literal_table * table, uint value, label_ref * labels)


int __cdecl add_pool_literal(literal_table *table,uint value,label_ref *labels)

{
  uint hash;
  literal_entry *new_entry;
  label_ref *ref_tail;
  label_ref *new_ref;
  literal_entry *chain;
  literal_entry *chain_next;
  label_ref *ref;
  
  hash = value;
  for (ref = labels; ref != (label_ref *)0x0; ref = ref->next) {
    hash = hash + (int)ref->labno1 + (int)ref->labno2;
  }
  new_entry = alloc_zeroed(0x10);
  new_entry->value = value;
  if (labels != (label_ref *)0x0) {
    ref_tail = alloc_zeroed(8);
    ref_tail->labno1 = labels->labno1;
    ref_tail->labno2 = labels->labno2;
    new_entry->labels = ref_tail;
    for (ref = labels->next; ref != (label_ref *)0x0; ref = ref->next) {
      new_ref = alloc_zeroed(8);
      ref_tail->next = new_ref;
      ref_tail->next->labno1 = ref->labno1;
      ref_tail->next->labno2 = ref->labno2;
      ref_tail = ref_tail->next;
    }
  }
  chain = table->buckets[hash % 0x7f];
  if (chain == (literal_entry *)0x0) {
    table->buckets[hash % 0x7f] = new_entry;
  }
  else {
    chain_next = chain->hash_next;
    while (chain_next != (literal_entry *)0x0) {
      chain = chain->hash_next;
      chain_next = chain->hash_next;
    }
    chain->hash_next = new_entry;
  }
  if (table->head != (literal_entry *)0x0) {
    table->tail->next = new_entry;
    table->tail = new_entry;
    table->count = table->count + 1;
    return;
  }
  table->head = new_entry;
  table->tail = new_entry;
  table->count = table->count + 1;
  return;
}



