#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00423780
// name : add_to_gen_use_sets
// size : 136
// sig  : void add_to_gen_use_sets(uint * block_set, short number, il_node * node, short words, uint * leaf_set)


int __cdecl add_to_gen_use_sets(uint *block_set,short number,il_node *node,short words,uint *leaf_set)

{
  uint bit;
  
  if (words == 8) {
    g_def_nodes[number] = node;
  }
  bit = 1 << (0x1f - ((byte)number & 0x1f) & 0x1f);
  block_set[number >> 5] = block_set[number >> 5] | bit;
  leaf_set[number >> 5] = leaf_set[number >> 5] | bit;
  if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 0x10) != 0) {
    if (words == 8) {
      dump_bitset(leaf_set,8,s_leaf_table_gen_00435c30);
      return;
    }
    if (words == 0x10) {
      dump_bitset(leaf_set,0x10,s_leaf_table_use_00435c20);
    }
  }
  return;
}



