#include "decls.h"
#include "imports.h"

// entry: 0041fce0
// name : clear_inline_maps
// size : 99
// sig  : void clear_inline_maps(void)


int __cdecl clear_inline_maps(void)

{
  inline_map_entry **bucket;
  inline_map_entry *ent;
  inline_map_entry *next;
  
  bucket = g_inline_symbol_map;
  do {
    ent = *bucket;
    while (ent != (inline_map_entry *)0x0) {
      next = ent->next;
      pool_free(ent,8);
      ent = next;
    }
    *bucket = (inline_map_entry *)0x0;
    bucket = bucket + 1;
  } while (bucket < &DAT_0043ff20);
  bucket = g_inline_block_map;
  do {
    ent = *bucket;
    while (ent != (inline_map_entry *)0x0) {
      next = ent->next;
      pool_free(ent,8);
      ent = next;
    }
    *bucket = (inline_map_entry *)0x0;
    bucket = bucket + 1;
  } while (bucket < &DAT_0043feb0);
  return;
}



