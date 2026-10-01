#include "decls.h"
#include "imports.h"

// entry: 00401655
// name : free_debug_location_table
// size : 119
// sig  : void free_debug_location_table(void)


int __cdecl free_debug_location_table(void)

{
  short bucket;
  debug_location *dloc;
  debug_location *next_loc;
  
  for (bucket = 0; bucket < 0x7f; bucket = bucket + 1) {
    dloc = g_debug_location_hash[bucket];
    while (dloc != (debug_location *)0x0) {
      next_loc = dloc->next;
      pool_free(dloc,0xc);
      dloc = next_loc;
    }
    g_debug_location_hash[bucket] = (debug_location *)0x0;
  }
  return;
}
