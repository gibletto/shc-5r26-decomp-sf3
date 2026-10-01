#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_string_pool_blocks
#define g_string_pool_blocks (*(int * *)(g_sd + 0x128dc))
#undef g_string_pool_end
#define g_string_pool_end (*(char * *)(g_sd + 0xfb18))
#undef g_string_pool_pos
#define g_string_pool_pos (*(char * *)(g_sd + 0x13144))


// entry: 0040156c
// name : free_debug_symbol_table
// size : 233
// sig  : void free_debug_symbol_table(void)


int __cdecl free_debug_symbol_table(void)

{
  short bucket;
  debug_symbol *dsym;
  undefined4 *pool_block;
  undefined4 *next_block;
  debug_symbol *next_sym;
  
  for (bucket = 0; bucket < 0x7f; bucket = bucket + 1) {
    dsym = g_debug_symbol_hash[bucket];
    while (dsym != (debug_symbol *)0x0) {
      if (dsym->type_ext != (debug_type_ext *)0x0) {
        pool_free(dsym->type_ext,8);
      }
      next_sym = dsym->next;
      pool_free(dsym,0x20);
      dsym = next_sym;
    }
    g_debug_symbol_hash[bucket] = (debug_symbol *)0x0;
  }
  pool_block = g_string_pool_blocks;
  while (pool_block != (undefined4 *)0x0) {
    next_block = (undefined4 *)*pool_block;
    pool_free(pool_block,0x104);
    pool_block = next_block;
  }
  g_string_pool_blocks = (undefined4 *)0x0;
  g_string_pool_pos = (char *)0x0;
  g_string_pool_end = (char *)0x0;
  return;
}
