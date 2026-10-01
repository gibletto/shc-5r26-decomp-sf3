#include "decls.h"
#include "imports.h"

// entry: 00418cb0
// name : find_pool_literal
// size : 93
// sig  : int find_pool_literal(literal_table * table, uint value, label_ref * labels)


int __cdecl find_pool_literal(literal_table *table,uint value,label_ref *labels)

{
  literal_entry *entry;
  uint hash;
  int found;
  label_ref *lref;
  
  found = 0;
  hash = value;
  for (lref = labels; lref != (label_ref *)0x0; lref = lref->next) {
    hash = hash + (int)lref->labno1 + (int)lref->labno2;
  }
  entry = table->buckets[hash % 0x7f];
  while ((entry != (literal_entry *)0x0 &&
         (found = pool_literal_matches(entry,value,labels), found != 1))) {
    entry = entry->hash_next;
  }
  return found;
}



