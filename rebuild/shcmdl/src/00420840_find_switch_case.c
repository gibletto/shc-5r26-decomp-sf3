#include "decls.h"
#include "imports.h"

// entry: 00420840
// name : find_switch_case
// size : 45
// sig  : switch_case * __cdecl find_switch_case(switch_table *table,short label)


switch_case * __cdecl find_switch_case(switch_table *table,short label)

{
  switch_case *sw_case;
  int i;
  
  i = 0;
  sw_case = table->cases;
  if (0 < table->count) {
    do {
      if (sw_case->label == label) {
        return sw_case;
      }
      i = i + 1;
      sw_case = sw_case + 1;
    } while (i < table->count);
  }
  return sw_case;
}
