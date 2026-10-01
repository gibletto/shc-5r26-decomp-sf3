#include "decls.h"
#include "imports.h"

// entry: 004282e6
// name : find_literal_pool_index
// size : 133
// sig  : int find_literal_pool_index(literal_table * table, int value, label_ref * refs)


int __cdecl find_literal_pool_index(literal_table *table,int value,label_ref *refs)

{
  int matches;
  int pool_index;
  literal_entry *lit_entry;
  
  pool_index = 1;
  lit_entry = table->head;
  while ((lit_entry != (literal_entry *)0x0 &&
         (matches = pool_literal_matches(lit_entry,value,refs), matches != 1))) {
    pool_index = pool_index + 1;
    lit_entry = lit_entry->next;
  }
  if (lit_entry == (literal_entry *)0x0) {
    report_message_at_source_line(0,0,0x134c,(char *)0x0);
  }
  return pool_index;
}



