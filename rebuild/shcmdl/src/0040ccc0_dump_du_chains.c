#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 0040ccc0
// name : dump_du_chains
// size : 47
// sig  : void dump_du_chains(void)


int __cdecl dump_du_chains(void)

{
  bblock *blk;
  node_list *item;
  
  for (blk = g_f_chain; blk != (bblock *)0x0; blk = blk->f_next) {
    for (item = blk->ilnode; item != (node_list *)0x0; item = item->next) {
      dump_du_chains_in_tree(item->node);
    }
  }
  return;
}



