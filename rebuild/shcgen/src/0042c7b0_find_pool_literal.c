#include "decls.h"
#include "imports.h"

// entry: 0042c7b0
// name : find_pool_literal
// size : 93
// sig  : int find_pool_literal(literal_table * table, uint value, label_ref * labels)


int __cdecl find_pool_literal(literal_table *table,uint value,label_ref *labels)

{
  literal_entry *entry;
  uint hash;
  int found;
  label_ref *ref;
  
  found = 0;
  hash = value;
  for (ref = labels; ref != (label_ref *)0x0; ref = ref->next) {
    hash = hash + (int)ref->labno1 + (int)ref->labno2;
  }
  entry = table->buckets[hash % 0x7f];
  while ((entry != (literal_entry *)0x0 &&
         (found = pool_literal_matches(entry,value,labels), found != 1))) {
    entry = entry->hash_next;
  }
  return found;
}



