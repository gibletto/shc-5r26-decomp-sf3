#include "decls.h"
#include "imports.h"

// entry: 0041fc40
// name : add_inline_map_entry
// size : 158
// sig  : void add_inline_map_entry(int map, short old_number, short new_number)


int __cdecl add_inline_map_entry(int map,short old_number,short new_number)

{
  inline_map_entry *new_ent;
  inline_map_entry *prev_item;
  inline_map_entry *next;
  
  new_ent = pool_alloc(8);
  if (new_ent == (inline_map_entry *)0x0) {
    abort_function_optimization();
  }
  new_ent->old_number = old_number;
  new_ent->new_number = new_number;
  new_ent->next = (inline_map_entry *)0x0;
  if (map == 1) {
    prev_item = (inline_map_entry *)(g_inline_symbol_map + old_number % 0x14);
  }
  else if (map == 2) {
    prev_item = (inline_map_entry *)(g_inline_block_map + old_number % 0x14);
  }
  else {
    fatal_error(0x109b);
  }
  if (prev_item->next == (inline_map_entry *)0x0) {
    prev_item->next = new_ent;
    return;
  }
  next = prev_item->next->next;
  while (next != (inline_map_entry *)0x0) {
    prev_item = prev_item->next;
    next = prev_item->next->next;
  }
  prev_item->next->next = new_ent;
  return;
}



