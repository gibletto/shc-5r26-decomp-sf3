#include "decls.h"
#include "imports.h"

// entry: 0042d8fa
// name : find_pool_literal
// size : 183
// sig  : int find_pool_literal(literal_table * table, uint value, label_ref * labels)


int __cdecl find_pool_literal(literal_table *table,uint value,label_ref *labels)

{
  uint hash_value;
  int matched;
  label_ref *cur_ref;
  literal_entry *cur_lit;
  
  matched = 0;
  hash_value = value;
  for (cur_ref = labels; cur_ref != (label_ref *)0x0; cur_ref = cur_ref->next) {
    hash_value = hash_value + (int)cur_ref->labno1 + (int)cur_ref->labno2;
  }
  cur_lit = table->buckets[hash_value % 0x7f];
  while ((cur_lit != (literal_entry *)0x0 &&
         (matched = pool_literal_matches(cur_lit,value,labels), matched != 1))) {
    cur_lit = cur_lit->hash_next;
  }
  return matched;
}



