#include "decls.h"
#include "imports.h"

// entry: 0041fbc0
// name : find_inline_map_entry
// size : 119
// sig  : inline_map_entry * __cdecl find_inline_map_entry(int map,short old_number)


inline_map_entry * __cdecl find_inline_map_entry(int map,short old_number)

{
  inline_map_entry *ent;
  
  if (map == 1) {
    ent = g_inline_symbol_map[old_number % 0x14];
  }
  else if (map == 2) {
    ent = g_inline_block_map[old_number % 0x14];
  }
  else {
    fatal_error(0x109b);
  }
  for (; (ent != (inline_map_entry *)0x0 && (ent->old_number != old_number)); ent = ent->next) {
  }
  return ent;
}
